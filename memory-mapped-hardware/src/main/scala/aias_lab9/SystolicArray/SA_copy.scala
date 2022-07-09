package aias_lab9.SystolicArray

import chisel3._
import chisel3.util._

import scala.io.Source

import aias_lab9.AXILite._

/*
  SA module
  includes a tile and input/output buffers
  also the control logic of systolic array
 */

class SA(rows: Int, cols: Int, addr_width: Int, data_width: Int, reg_width: Int) extends Module {
  val io = IO(new Bundle {
    // connect to Memory_Mapped
    val mmio = Flipped(new MMIO(reg_width))

    // for access localmem when SA still be a slave
    val raddr = Output(UInt(addr_width.W))
    val rdata = Input(UInt(data_width.W))
    val wen   = Output(Bool())
    val waddr = Output(UInt(addr_width.W))
    val wdata = Output(UInt(data_width.W))
    val wstrb = Output(UInt((data_width >> 3).W))

    // for making localMem print the value
    val finish = Output(Bool())
  })

  // constant declaration
  val byte    = 8
  val mat_buf = 0x000000 // 0 because the localMem is still local for SA
  // information from MMIO_Regfile
  val mat_a_rows = io.mmio.MATA_SIZE(11, 0) + 1.U
  val mat_a_cols = io.mmio.MATA_SIZE(27, 16) + 1.U
  val mat_b_rows = io.mmio.MATB_SIZE(11, 0) + 1.U
  val mat_b_cols = io.mmio.MATB_SIZE(27, 16) + 1.U
  val mat_c_rows = io.mmio.MATC_SIZE(11, 0) + 1.U
  val mat_c_cols = io.mmio.MATC_SIZE(27, 16) + 1.U

  // base address wires (for read/write internal mem)
  val a_base_addr = WireDefault(io.mmio.MATA_MEM_ADDR)
  val b_base_addr = WireDefault(io.mmio.MATB_MEM_ADDR)
  val c_base_addr = WireDefault(io.mmio.MATC_MEM_ADDR)

  // other wires
  val word_writeData = WireDefault(0.U(32.W))

  // module declaration
  val tile          = Module(new tile(rows, cols, byte)) // single tile in our SA design
  val input_buffer  = Module(new buffer(rows, byte))
  val output_buffer = Module(new buffer(cols, byte))

  // state declaration
  val sIdle :: sReady :: sPreload :: sPropagate :: sCheck :: sFinish :: Nil = Enum(6)
  // state register
  val stateReg = RegInit(sIdle)

  // declare counters
  val weight_cnt = RegInit(0.U(3.W))
  val input_cnt  = RegInit(0.U(3.W))
  val output_cnt = RegInit(0.U(3.W))

  // wiring io.rdata <---> tile.io.weight and tile.io.preload
  tile.io.preload := stateReg === sPreload
  List.range(0, cols).map { index =>
    tile.io.weight(index).bits  := io.rdata(byte * (cols - index) - 1, byte * (cols - index - 1))
    tile.io.weight(index).valid := stateReg === sPreload
  }

  // wiring io.rdata <---> input_buffer.io.input
  List.range(0, rows).map { index =>
    input_buffer.io.input(index).bits  := io.rdata(byte * (index + 1) - 1, byte * index)
    input_buffer.io.input(index).valid := (stateReg === sPropagate) && (input_cnt < 4.U)
  }

  // wiring input_buffer.io.output <---> tile.io.input
  tile.io.input <> input_buffer.io.output

  // wiring tile.io.output <---> output_buffer.io.input (notice the order of wiring)
  List.range(0, cols).map { index =>
    output_buffer.io.input(cols - 1 - index) <> tile.io.output(index)
  }

  // assign io.raddr and io.waddr
  io.raddr := Mux(
    stateReg === sPreload, // sPreload or sPropagate
    b_base_addr + (weight_cnt << 2),
    a_base_addr + (input_cnt << 2)
  )
  io.waddr := c_base_addr + (output_cnt << 2)

  // assign word_writeData and io.wdata, io.wstrb and io.wen
  word_writeData := List
    .range(0, cols)
    .map { index => output_buffer.io.output(index).bits << byte * (cols - 1 - index) }
    .reduce(_ + _)
  io.wdata := Cat(0.U(32.W), word_writeData)
  io.wstrb := "b00001111".U
  io.wen   := output_buffer.io.output(0).valid

  // assign io.finish
  io.finish := stateReg === sFinish

  // assign io.mmio output signals
  io.mmio.ENABLE_IN := !(stateReg === sFinish)
  io.mmio.STATUS_IN := stateReg === sFinish
  io.mmio.WEN       := stateReg === sFinish

  // next state logic
  switch(stateReg) {
    is(sIdle) {
      stateReg := sReady
    }
    is(sReady) {
      stateReg := Mux(io.mmio.ENABLE_OUT, sPreload, sReady)
    }
    is(sPreload) {
      when(io.mmio.ENABLE_OUT) {
        stateReg := Mux(weight_cnt === (rows - 1).U, sPropagate, sPreload)
      }.otherwise {
        stateReg := sReady
        // reset counter
        weight_cnt := 0.U
      }
    }
    is(sPropagate) {
      when(io.mmio.ENABLE_OUT) {
        stateReg := Mux(input_cnt === (rows + cols - 2).U, sCheck, sPropagate)
      }.otherwise {
        stateReg := sReady
        // reset counters
        weight_cnt := 0.U
        input_cnt  := 0.U
      }
    }
    is(sCheck) {
      stateReg := Mux(output_cnt === 3.U, sFinish, sCheck)
    }
    is(sFinish) {
      stateReg := sReady
    }
  }

  // FSM output decoder
  switch(stateReg) {
    is(sPreload) {
      weight_cnt := weight_cnt + 1.U
    }
    is(sPropagate) {
      input_cnt := input_cnt + 1.U
    }
    is(sCheck) {
      output_cnt := output_cnt + Mux(output_buffer.io.output(0).valid, 1.U, 0.U)
    }
    is(sFinish) {
      // reset counters
      weight_cnt := 0.U
      input_cnt  := 0.U
      output_cnt := 0.U
    }
  }
}

object SA extends App {
  (new chisel3.stage.ChiselStage).emitVerilog(
    new SA(4, 4, 32, 64, 32), // rows, cols, addr_width, data_width, reg_width
    Array("-td", "./generated/SA")
  )
}
