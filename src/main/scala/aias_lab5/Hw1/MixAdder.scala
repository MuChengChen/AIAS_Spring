package aias_lab5.Hw1

import chisel3._
import aias_lab5.Lab._

class MixAdder (n:Int) extends Module{
  val io = IO(new Bundle{
      val Cin = Input(UInt(1.W))
      val in1 = Input(UInt((4*n).W))
      val in2 = Input(UInt((4*n).W))
      val Sum = Output(UInt((4*n).W))
      val Cout = Output(UInt(1.W))
  })
  //please implement your code below
  io.Sum := 0.U
  io.Cout := 0.U
}