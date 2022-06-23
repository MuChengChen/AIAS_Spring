package aias_lab5.Hw4

import chisel3._
import chisel3.util._
import chisel3.util.experimental.loadMemoryFromFile


object wide {
  val Byte = 0.U
  val Half = 1.U
  val Word = 2.U
  val UByte = 4.U
  val UHalf = 5.U
}

import wide._

class DataMem extends Module {
  val io = IO(new Bundle {
    val funct3 = Input(UInt(32.W))
    val raddr = Input(UInt(10.W))
    val rdata = Output(SInt(32.W))
    
    val wen   = Input(Bool())
    val waddr = Input(UInt(10.W))
    val wdata = Input(UInt(32.W))
  })

  val memory = Mem(32, UInt(8.W))
  loadMemoryFromFile(memory, "./src/main/resource/DataMem.txt")

  io.rdata := 0.S

  val wa = WireDefault(0.U(10.W)) //address
  val wd = WireDefault(0.U(32.W)) //data

  wa := MuxLookup(io.funct3,0.U(10.W),Seq(
    Byte -> io.waddr,
    Half -> ((io.waddr>>1)<<1), // needs to be changed
    Word -> ((io.waddr>>2)<<2), // needs to be changed
  ))

  wd := MuxLookup(io.funct3,0.U,Seq(
    Byte -> io.wdata, // needs to be changed
    Half -> io.wdata, // needs to be changed
    Word -> io.wdata,
  ))

  val rdataU=0.U(32.W)

  when(io.wen){ //STORE
    when(io.funct3===Byte){
      memory(wa) := wd(7,0)
    }.elsewhen(io.funct3===Half){
      //Please fill in the blanks by yourself
      memory(wa) := wd(7,0)
      memory(wa+1.U):=wd(15,8)
    }.elsewhen(io.funct3===Word){
      //Please fill in the blanks by yourself
      memory(wa) := wd(7,0)
      memory(wa+1.U) := wd(15,8)
      memory(wa+2.U) := wd(23,16)
      memory(wa+3.U) := wd(31,24)
    }
  }.otherwise{ //LOAD
    switch(io.funct3){
      is(Byte){io.rdata := memory(io.raddr).asSInt}
      is(Half){io.rdata := Cat(memory(io.raddr+1.U),memory(io.raddr)).asSInt}
      is(Word){io.rdata := Cat(memory(io.raddr+3.U),memory(io.raddr+2.U),memory(io.raddr+1.U),memory(io.raddr)).asSInt}
      is(UByte){io.rdata := (rdataU+memory(io.raddr)).asSInt}
      is(UHalf){io.rdata := (rdataU+Cat(memory(io.raddr+1.U),memory(io.raddr))).asSInt}
    }
  }
}