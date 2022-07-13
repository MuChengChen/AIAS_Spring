// See LICENSE.txt for license details.
package aias_lab6.Hw2

import chisel3._
import chisel3.util._

class Stack(val depth: Int) extends Module {
  val io = IO(new Bundle {
    val push    = Input(Bool())
    val pop     = Input(Bool())
    val en      = Input(Bool())
    val clean   = Input(Bool())
    val empty   = Output(Bool())
    val onlyone = Output(Bool())
    val dataIn  = Input(UInt(300.W))
    val dataOut = Output(UInt(300.W))
    val topdata = Output(UInt(300.W))
    val seconddata = Output(UInt(300.W))
  })

  val stack_mem = Mem(depth, UInt(300.W))
  val sp        = RegInit(0.U(log2Ceil(depth+1).W))
  val out       = RegInit(0.U(200.W))
  //為什麼要多設io.en
  when (io.en) {
    when(io.push && (sp < depth.asUInt)) {
      stack_mem(sp) := io.dataIn
      out := io.dataIn//這裡有預先訂好的out,因此out := stack_mem(sp-1.U)是移到下個topdata而不是pop這個out
      sp := sp + 1.U
    } .elsewhen(io.pop && (sp > 0.U)) {
      when(sp > 1.U){
        out := stack_mem(sp-2.U)
      }
      sp := sp - 1.U
    }.elsewhen (io.clean) {
      out := 0.U
      sp  := 0.U
    }
  }

  io.dataOut := out
  io.empty := (sp === 0.U)
  io.onlyone := (sp === 1.U)
  io.topdata:=stack_mem(sp-1.U)
  io.seconddata:=stack_mem(sp-2.U)
}
