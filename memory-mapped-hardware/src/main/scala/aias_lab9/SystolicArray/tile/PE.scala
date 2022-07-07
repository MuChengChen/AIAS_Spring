package aias_lab9.SystolicArray

import chisel3._
import chisel3.util._

class PE(val bits: Int = 8) extends Module {
  val io = IO(new Bundle {
    // input propagation (fwd: forwarded)
    val input     = Input(Valid(UInt(bits.W)))
    val fwd_input = Output(Valid(UInt(bits.W)))

    // weight propagation
    val weight     = Input(Valid(UInt(bits.W)))
    val fwd_weight = Output(Valid(UInt(bits.W)))

    val preload = Input(Bool())

    // partial sum propagation (ps is short for partial sum)
    val ps     = Input(UInt((bits * 2).W))
    val fwd_ps = Output(Valid(UInt((bits * 2).W)))
  })

  // weightReg includes 2 parts: bits and valid
  val weight_wire = Wire(Valid(UInt(bits.W)))
  weight_wire.bits  := 0.U     // initialize
  weight_wire.valid := false.B // initialize
  val weightReg = RegInit(weight_wire)

  // internal weight register (bits and valid)
  weightReg.bits  := Mux(io.preload, io.weight.bits, weightReg.bits)
  weightReg.valid := Mux(io.preload, io.weight.valid, weightReg.valid)

  // output
  io.fwd_weight.bits  := weightReg.bits
  io.fwd_weight.valid := weightReg.valid

  io.fwd_input <> RegNext(io.input)

  io.fwd_ps.valid := RegNext(io.input.valid)
  io.fwd_ps.bits  := RegNext(io.ps + weightReg.bits * io.input.bits)
}

object PE extends App {
  (new chisel3.stage.ChiselStage).emitVerilog(
    new PE(8),
    Array("-td", "generated/PE")
  )
}
