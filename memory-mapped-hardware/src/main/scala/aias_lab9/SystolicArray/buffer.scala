package aias_lab9.SystolicArray

import chisel3._
import chisel3.util._

/** input/output buffer for systolic array
  * @param size
  *   the size of rows or cols of systolic array
  * @param bits
  *   the width of each element in input/output vector
  */
class buffer(size: Int, bits: Int) extends Module {
  val io = IO(new Bundle {
    val input  = Input(Vec(size, Valid(UInt(bits.W))))
    val output = Output(Vec(size, Valid(UInt(bits.W))))
  })
  io.output(0) <> io.input(0) // first row or col do not need extra buffer reg
  for (idx <- 1 until size) {
    // wire for reg initialization
    val initial_wire = Wire(Valid(UInt(bits.W)))
    initial_wire.bits  := DontCare
    initial_wire.valid := DontCare
    // register array declaration
    val reg_array = Array.fill(idx)(RegInit(initial_wire))

    reg_array.head <> io.input(idx)
    for (i <- 1 until idx) {
      reg_array(i).bits  := reg_array(i - 1).bits
      reg_array(i).valid := reg_array(i - 1).valid
    }
    io.output(idx) <> reg_array.last
  }
}

object bufferTop extends App {
  (new chisel3.stage.ChiselStage).emitVerilog(
    new buffer(4, 8),
    Array("-td", "./generated/buffer")
  )
}
