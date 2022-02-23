package aias_prev

import chisel3._
import chisel3.util._
import chisel3.stage.{ChiselGeneratorAnnotation, ChiselStage}
import firrtl.options.TargetDirAnnotation

class Mux2_32b extends Module{
  val io = IO(new Bundle{
    val sel = Input(Bool())
    val in1 = Input(UInt(32.W))
    val in2 = Input(UInt(32.W))

    val out = Output(UInt(32.W))
  })
  
  //Method One
  // when(~io.sel){
  //   io.out := io.in1
  // }.otherwise{
  //   io.out := io.in2
  // }
  
  //Method Two
  // def myMux[T <: Data](sel:Bool,in1:T,in2:T):T={
  //   val x = WireDefault(in1)
  //   when(sel){x := in2} 
  //   x
  // }
  // io.out := myMux(io.sel,io.in1,io.in2) 

  //Method Three
  io.out := Mux(io.sel,io.in1,io.in2) 
}
//===========================================================================
// object Mux2_32b extends App{
//   (new chisel3.stage.ChiselStage).execute(
//     Array("-X","verilog"),
//     Seq(ChiselGeneratorAnnotation(()=>new Mux2_32b()),
//     TargetDirAnnotation("Verilog"))
//   )
// }