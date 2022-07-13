package aias_lab9.SystolicArray

import chisel3._
import chisel3.util._

/** input/output buffer for systolic array
  * @param size
  *   the size of rows or cols of systolic array
  * @param bits
  *   the width of each element in input/output vector
  */
class _buffer(size: Int, bits: Int) extends Module {
  val io = IO(new Bundle {
    val input  = Input(Vec(size, Valid(UInt(bits.W))))
    val output = Output(Vec(size, Valid(UInt(bits.W))))
  })

  val taps = Seq.range(0, size).map { length =>
    // ++ -> union operation of two sequences
    val tap_bits = Seq(io.input(length).bits) ++ Seq.fill(length)(RegInit(0.U(bits.W)))

    tap_bits.zip(tap_bits.tail).foreach { case (front, back) =>
      back := front
    }

    io.output(length).bits := tap_bits.last

    val tap_valid = Seq(io.input(length).valid) ++ Seq.fill(length)(RegInit(false.B))

    tap_valid.zip(tap_valid.tail).foreach { case (front, back) =>
      back := front
    }

    io.output(length).valid := tap_valid.last
  }
}

object bufferTop extends App {
  (new chisel3.stage.ChiselStage).emitVerilog(
    new _buffer(4, 8),
    Array("-td", "./generated/buffer")
  )
}
