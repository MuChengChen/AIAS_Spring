package aias_prev

import chisel3._
import chisel3.util._ 


object ALU_op{
  val ADD = 0.U
  val SUB = 1.U
  val AND = 2.U
  val OR = 3.U
  val XOR = 4.U
  val SLL = 5.U
  val SRL = 6.U
  val SRA = 7.U
}

import ALU_op._

class ALUIO extends Bundle{
  val src1    = Input(UInt(32.W))
  val src2    = Input(UInt(32.W))
  val shamt   = Input(UInt(5.W))
  val ALUCtrl = Input(UInt(4.W))
  val ALUout  = Output(UInt(32.W))
//   val ALUzero = Output(Bool())
}

class ALU extends Module{
  val io = IO(new ALUIO)
  
  io.ALUout := MuxLookup(io.ALUCtrl,0.U,Seq(
    ADD -> (io.src1 + io.src2)   ,
    SUB -> (io.src1 - io.src2)   ,
    AND -> (io.src1 & io.src2)   ,
    OR  -> (io.src1 | io.src2)   ,
    XOR -> (io.src1 ^ io.src2)   ,
    SLL -> (io.src1 << io.shamt) ,
    SRL -> (io.src1 >> io.shamt) ,
    SRA -> (io.src1.asSInt >> io.shamt).asUInt
  ))

//   io.ALUzero := false.B
//   when(io.ALUCtrl === SUB){
// 	io.ALUzero := Mux(io.src1 === io.src2 , true.B, false.B)
//   }
}