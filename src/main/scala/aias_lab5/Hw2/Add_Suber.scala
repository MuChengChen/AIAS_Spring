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
  val FA_Array=Array.fill(4)(Module(new FullAdder()).io)
  val in_2_twos=Wire(UInt(4.W)) //B
  val carry=Wire(Vec(5,UInt(1.W)))
  val sum=Wire(Vec(4,UInt(1.W)))

  
  when(io.op === true.B){
    carry(0):=true.B
    in_2_twos:=(~io.in_2)
  }.otherwise{
    carry(0):=false.B
    in_2_twos:=io.in_2
  }


  for(i<-0 until 4){
    FA_Array(i).A:=io.in_1(i)
    FA_Array(i).B:=in_2_twos(i)
    FA_Array(i).Cin:=carry(i)
    carry(i+1):=FA_Array(i).Cout
    sum(i):=FA_Array(i).Sum
  }

  io.out := sum.asUInt
  io.o_f := (carry(3)^carry(4))|((io.in_2===8.U)&io.op===true.B) 
}
