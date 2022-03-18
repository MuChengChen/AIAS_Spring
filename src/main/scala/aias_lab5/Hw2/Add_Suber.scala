package aias_lab5.Hw2

import chisel3._
import chisel3.util._
import aias_lab5.Lab._

class Add_Suber extends Module{
  val io = IO(new Bundle{
  val in_1 = Input(UInt(4.W))
	val in_2 = Input(UInt(4.W))
	val op = Input(Bool()) // 0:ADD 1:SUB
	val out = Output(UInt(4.W))
	val o_f = Output(Bool())
  })

  //please implement your code below
  
  io.out := 0.U
  io.o_f := false.B
}
