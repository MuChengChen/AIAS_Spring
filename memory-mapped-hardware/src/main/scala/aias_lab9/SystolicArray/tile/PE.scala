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
  val weightReg = RegInit(VecInit(Seq(0.U(bits.W), false.B)))

  // internal weight register (bits and valid)
  weightReg(0) := Mux(io.preload, io.weight.bits, weightReg(0))
  weightReg(1) := Mux(io.preload, io.weight.valid, weightReg(1))

  // output
  io.fwd_weight.bits  := weightReg(0)
  io.fwd_weight.valid := weightReg(1)

  io.fwd_input <> RegNext(io.input)

  io.fwd_ps.valid := RegNext(io.input.valid)
  io.fwd_ps.bits  := RegNext(io.ps + weightReg(0) * io.input.bits)
}

object PE extends App {
  (new chisel3.stage.ChiselStage).emitVerilog(
    new PE(8),
    Array("-td", "generated/PE")
  )
}
