package aias_lab8.Single_Cycle.Controller

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

    // Edit for Vector Extension
    val VOP       = "b1010111".U
    val VLOAD     = "b0000111".U
    val VSTORE    = "b0100111".U

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
  val MUL  = 9.U
  val DIV  = 10.U
}

object ALU_funct7{
  val SUB_SRA = "b0100000".U
}


//**************************************************
//**                                              **
//**                                              **
//**      Modification of Vector Extension        **
//**                                              **
//**                                              **
//**************************************************
object vector_ALU_op{
    val VADD_VV = 0.U
    val VMUL_VV = 1.U
    val VMUL_VX = 4.U
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
    val V = 6.U
}


import opcode_map._,condition._,ALU_op._,vector_ALU_op._,ALU_funct7._,inst_type._

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
        val MemRW = Output(UInt(3.W))
        val WBSel = Output(UInt(2.W))

        //new
        val Lui = Output(Bool())
        val Hcf = Output(Bool())

        // Edit for Vector Extension
        val vector_ALUSel = Output(UInt(4.W))
        val vector_ASel = Output(Bool())
        val vector_BSel = Output(Bool())
        val vector_WBSel = Output(UInt(2.W))
        val vector_RegWEn = Output(Bool())
    })
    
    val opcode = Wire(UInt(7.W))
    opcode := io.Inst(6,0)

    val funct3 = Wire(UInt(3.W))
    funct3 := io.Inst(14,12)

    val funct7 = Wire(UInt(7.W))
    funct7 := io.Inst(31,25)

    // Edit for Vector Extension
    val funct6 = Wire(UInt(6.W))
    funct6 := io.Inst(31,26)

    //Control signal
    io.RegWEn := Mux(opcode===STORE||opcode===BRANCH||opcode===HCF||opcode===VOP||opcode===VLOAD||opcode===VSTORE,false.B,true.B)
    io.ASel := Mux(opcode===BRANCH||opcode===JAL,true.B,false.B)
    io.BSel := Mux(opcode===OP,false.B,true.B)
    io.BrUn := Mux(funct3===LTU||funct3===GEU,true.B,false.B)
    io.MemRW :=  MuxLookup(opcode,1.U,Seq(
                                STORE->0.U,
                                LOAD->1.U,
                                VSTORE->2.U,
                                VLOAD->3.U
    ))

    io.ImmSel := MuxLookup(opcode,0.U,Seq(
                                LOAD->I,
                                STORE->S,
                                BRANCH->B,
                                JAL->J,
                                JALR->I,
                                OP->R,
                                OP_IMM->I,
                                AUIPC->U,
                                LUI->U,
                                VLOAD->V,
                                VSTORE->V
    ))

    io.ALUSel := Mux(opcode===OP||opcode===OP_IMM,funct3,ADD)
    when(funct3===ADD && (opcode===OP||opcode===OP_IMM) && funct7(0)=/=1.U){
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
    }.elsewhen(funct7(0)===1.U && opcode===OP){
      when(funct3===0.U){
        io.ALUSel:=MUL
      }.elsewhen(funct3===4.U){
        io.ALUSel:=DIV
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


    //**************************************************
    //**                                              **
    //**                                              **
    //**      Modification of Vector Extension        **
    //**                                              **
    //**                                              **
    //**************************************************
    io.vector_ALUSel := 5.U
    when(opcode===VOP){
      when(funct6==="b000000".U){
        io.vector_ALUSel :=VADD_VV
      }.elsewhen(funct6==="b100101".U){
        when(funct3==="b000".U){
          io.vector_ALUSel :=VMUL_VV
        }.elsewhen(funct3==="b100".U){
          io.vector_ALUSel :=VMUL_VX
        }
      }
    }
    io.vector_ASel   := Mux(opcode===VOP && funct3<3.U,true.B,false.B)
    io.vector_BSel   := Mux(opcode===VOP ,true.B,false.B)
    io.vector_RegWEn := Mux(opcode===VOP || opcode===VLOAD,true.B,false.B)
    io.vector_WBSel  := Mux(opcode===VOP ,0.U,1.U)
}