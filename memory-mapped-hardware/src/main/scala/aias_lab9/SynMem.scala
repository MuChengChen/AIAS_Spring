package aias_lab9.SystolicArray

import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFile

class SyncMem extends Module {
  val io = IO(new Bundle {
    val width = 64
    val raddr = Input(UInt(addr_width.W))
    val rdata = Output(UInt(data_width.W))

    val wen   = Input(Bool())
    val waddr = Input(UInt(addr_width.W))
    val wdata = Input(UInt(data_width.W))
    val wstrb = Input(UInt((data_width >> 3).W))
  })

  val byte = 8

  val localMem = SyncReadMem(mem_size, UInt(byte.W))
  loadMemoryFromFile(localMem, "src/main/resource/SystolicArray/LocalMem.hex")

  when(io.wen) {
    mem.write(io.waddr, io.wdata)
  }
}
