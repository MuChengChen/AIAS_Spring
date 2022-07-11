package aias_lab9.SystolicArray

import chisel3._
import chisel3.iotesters.{Driver, PeekPokeTester}

class LocalMemTest(dut: LocalMem) extends PeekPokeTester(dut) {
  /*
    IO ports of LocalMem
      val raddr = Input(UInt(addr_width.W))
      val rdata = Output(UInt(data_width.W))

      val wen   = Input(Bool())
      val waddr = Input(UInt(addr_width.W))
      val wdata = Input(UInt(data_width.W))
      val wstrb = Input(UInt((data_width >> 3).W))
   */
}

object LocalMemTest extends App {
  Driver.execute(args = Array("-tbn", "verilator"), () => new LocalMem(0x8000, 32, 64)) { c: LocalMem =>
    new LocalMemTest(c)
  }
}
