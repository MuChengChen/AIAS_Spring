package aias_prev

import chisel3._
import chisel3.util.experimental.loadMemoryFromFile
import firrtl.annotations.MemoryLoadFileType

class Memory extends Module {
  val io = IO(new Bundle {
    val raddr = Input(UInt(8.W))
    val rdata = Output(UInt(32.W))
    
    val wen   = Input(Bool())
    val waddr = Input(UInt(8.W))
    val wdata = Input(UInt(32.W))
  })
  //size : 1KB
  val memory = SyncReadMem(256, UInt(32.W))
  loadMemoryFromFile(memory, "./src/main/resource/value.txt",MemoryLoadFileType.Hex) //Binary or Hex

  io.rdata := memory.read(io.raddr)

  when(io.wen){memory.write(io.waddr,io.wdata)}
}