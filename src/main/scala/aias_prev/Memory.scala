package aias_prev

import chisel3._
import chisel3.util.experimental.loadMemoryFromFile

class Memory extends Module {
  val io = IO(new Bundle {
    val raddr = Input(UInt(5.W))
    val rdata = Output(UInt(32.W))
    
    val wen   = Input(Bool())
    val waddr = Input(UInt(5.W))
    val wdata = Input(UInt(32.W))
  })
  val memory = SyncReadMem(32, UInt(32.W))
  loadMemoryFromFile(memory, "./src/main/resource/value.txt")

  io.rdata := memory(io.raddr)

  when(io.wen){memory(io.waddr) := io.wdata}
}