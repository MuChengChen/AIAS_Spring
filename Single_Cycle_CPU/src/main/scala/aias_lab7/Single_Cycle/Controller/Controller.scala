package aias_lab7.Single_Cycle.Controller

import chisel3._
import chisel3.util._


object opcode_map {
    val LOAD      = "b0000011".U
    val STORE     = "b0100011".U
    val BRANCH    = "b1100011".U
    val JALR      = "b1100111".U
    val JAL       = "b1101111".U
    val OP_IMM    = "b0010011".U
    val OP        = "b0110011".U
    val AUIPC     = "b0010111".U
    val LUI       = "b0110111".U
    val HCF       = "b0001011".U
}

object ALU_op{
  val ADD  = 0.U
  val SLL  = 1.U
  val SLT  = 2.U
  val SLTU = 3.U
  val XOR  = 4.U
  val SRL  = 5.U
  val OR   = 6.U
  val AND  = 7.U
  val SUB  = 8.U
  val SRA  = 13.U
}

object ALU_funct7{
  val SUB_SRA = "b0100000".U
}

object condition{
  val EQ = "b000".U
  val NE = "b001".U
  val LT = "b100".U
  val GE = "b101".U
  val LTU = "b110".U
  val GEU = "b111".U
}

object inst_type{
    val R = 0.U
    val I = 1.U
    val S = 2.U
    val B = 3.U
    val J = 4.U
    val U = 5.U
}

import opcode_map._,condition._,ALU_op._,inst_type._,ALU_funct7._

class Controller extends Module {
    val io = IO(new Bundle{
        val Inst = Input(UInt(32.W))
        val BrEq = Input(Bool())
        val BrLT = Input(Bool())

        val PCSel = Output(Bool())
        val ImmSel = Output(UInt(3.W))
        val RegWEn = Output(Bool())
        val BrUn = Output(Bool())
        val BSel = Output(Bool())
        val ASel = Output(Bool())
        val ALUSel = Output(UInt(4.W))
        val MemRW = Output(Bool())
        val WBSel = Output(UInt(2.W))

        //new
        val Lui = Output(Bool())
        val Hcf = Output(Bool())
    })
    
    val opcode = Wire(UInt(7.W))
    opcode := io.Inst(6,0)

    val funct3 = Wire(UInt(3.W))
    funct3 := io.Inst(14,12)

    val funct7 = Wire(UInt(7.W))
    funct7 := io.Inst(31,25)

    //Control signal
    io.RegWEn := Mux(opcode===STORE||opcode===BRANCH||opcode===HCF,false.B,true.B)
    io.ASel := Mux(opcode===BRANCH||opcode===JAL,true.B,false.B)
    io.BSel := Mux(opcode===OP,false.B,true.B)
    io.BrUn := Mux(funct3===LTU||funct3===GEU,true.B,false.B)
    io.MemRW := Mux(opcode===STORE,true.B,false.B)

    io.ImmSel := MuxLookup(opcode,0.U,Seq(
                                LOAD->I,
                                STORE->S,
                                BRANCH->B,
                                JAL->J,
                                JALR->I,
                                OP->R,
                                OP_IMM->I,
                                AUIPC->U,
                                LUI->U
    ))

    io.ALUSel := Mux(opcode===OP||opcode===OP_IMM,funct3,ADD)
    when(funct3===ADD && (opcode===OP||opcode===OP_IMM)){
      when(funct7===SUB_SRA){
        io.ALUSel:=SUB
      }.otherwise{
        io.ALUSel:=ADD
      }
    }.elsewhen(funct3===SRL && (opcode===OP||opcode===OP_IMM)){
      when(funct7===SUB_SRA){
        io.ALUSel:=SRA
      }.otherwise{
        io.ALUSel:=SRL
      }
    }

    io.PCSel := Mux(opcode===JAL||opcode===JALR,true.B,false.B)
    when(opcode===BRANCH){
      switch(funct3){
        is(EQ){
          io.PCSel:= io.BrEq
        }
        is(NE){
          io.PCSel:= ~io.BrEq
        }
        is(LT){
          io.PCSel:= io.BrLT
        }
        is(GE){
          io.PCSel:= ~io.BrLT
        }
        is(LTU){
          io.PCSel:= io.BrLT
        }
        is(GEU){
          io.PCSel:= ~io.BrLT
        }
      }
    }

    //io.WBSel := 1.U
    io.Lui := opcode===LUI
    io.Hcf := opcode===HCF

    when(opcode===LOAD||opcode===STORE){
        io.WBSel:=0.U
    }.elsewhen(opcode===JALR||opcode===JAL){
        io.WBSel:=2.U
    }.otherwise{
        io.WBSel:=1.U
    }
}