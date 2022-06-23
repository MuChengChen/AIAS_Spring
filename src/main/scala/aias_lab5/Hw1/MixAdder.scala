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
  val CLAdder_Array=Array.fill(n)(Module(new CLAdder()).io)
  val carry=Wire(Vec(n+1,UInt(1.W)))
  val sum=Wire(Vec(4*n,Bool()))

  carry(0):=io.Cin

  for(i<-0 until n){
    CLAdder_Array(i).in1:=io.in1(4 * (i + 1) - 1, 4 * i)
    CLAdder_Array(i).in2:=io.in2(4 * (i + 1) - 1, 4 * i)
    CLAdder_Array(i).Cin:=carry(i)
    carry(i+1):=CLAdder_Array(i).Cout
    for (n<-0 until 4){
      sum(4*i+n):=CLAdder_Array(i).Sum(n)
    }
    
  }

  io.Sum := sum.asUInt
  io.Cout := carry(n)
}