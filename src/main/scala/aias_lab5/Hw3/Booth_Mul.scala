package aias_lab5.Hw3

import chisel3._
import chisel3.util._
import aias_lab5.Lab._
import scala.annotation.switch

//------------------Radix 4---------------------
class Encoder(width:Int) extends Module{
  val io=IO(new Bundle{
    val e1=Input(SInt((2*width).W))
    val e2=Input(UInt(3.W))
    val transfer=Output(SInt((2*width).W))
  })
  io.transfer:=MuxLookup(io.e2,0.S,Seq(
    1.U->io.e1,
    2.U->io.e1,
    3.U->(io.e1<<1),
    4.U->((~io.e1.asUInt+1.U).asSInt<<1),
    5.U->(~io.e1.asUInt+1.U).asSInt,
    6.U->(~io.e1.asUInt+1.U).asSInt
  ))
}
class Booth_Mul(width:Int) extends Module {
  
  val io = IO(new Bundle{
    val in1 = Input(SInt(width.W))      //Multiplicand 
    val in2 = Input(UInt(width.W))      //Multiplier   
    val out = Output(SInt((2*width).W)) //product
  })
  //please implement your code below
  val B=Cat(io.in2,0.U(1.W))

  //partial product

  val Encoder_Array=Array.fill(width/2)(Module(new Encoder(width)).io)
  //val Bin=Wire(Vec(width/2,UInt(3.W)))
  val transfer_result=Wire(Vec(width/2,SInt((2*width).W)))
  
  for(i<-1 to width by 2){
    Encoder_Array(i/2).e2:=B(i+1,i-1)
    Encoder_Array(i/2).e1:=io.in1.asSInt
    //:=Bin
    //Sign_extend , Shift
    transfer_result(i/2):=Encoder_Array(i/2).transfer<<(i-1)
  }
  //operation
  val adder=Array.fill((width/2)-1)(Module(new RCAdder(2*width)).io)
  val adder_out=Wire(Vec((width/2)-1,UInt((2*width).W)))

  for(i<-0 to (width/4)-1 by 1){
    adder(i).In1:=transfer_result(i*2).asUInt
    adder(i).In2:=transfer_result(i*2+1).asUInt
    adder(i).Cin:=0.U
    adder_out(i):=adder(i).Sum
  }

  var adder_count=0
  for(i<-(width/4) to (width/2)-2 by 1){
    adder(i).In1:=adder_out(adder_count)
    adder_count+=1
    adder(i).In2:=adder_out(adder_count)
    adder_count+=1
    adder(i).Cin:=0.U
    adder_out(i):=adder(i).Sum
  }

  io.out := adder_out((width/2)-2).asSInt
}

