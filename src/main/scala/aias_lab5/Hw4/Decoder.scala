package aias_lab5.Hw4

import chisel3._
import chisel3.util._

object opcode_map {
    val LOAD      = "b0000011".U
    val STORE     = "b0100011".U
    val BRANCH    = "b1100011".U
    val JALR      = "b1100001".U
    val JAL       = "b1100000".U
    val OP_IMM    = "b0010011".U
    val OP        = "b0110011".U
    val AUIPC     = "b0010111".U
    val LUI       = "b0110111".U
}

import opcode_map._

class Decoder extends Module{
    val io = IO(new Bundle{
        val inst = Input(UInt(32.W))

        //Please fill in the blanks by yourself
        val funct3 = Output(UInt(3.W))
        val funct7 = Output(UInt(7.W))
        val rs1 = Output(UInt(5.W))
        val rs2 = Output(UInt(5.W))
        //Please fill in the blanks by yourself
        val rd = Output(UInt(5.W))
        val opcode = Output(UInt(7.W))
        val imm = Output(SInt(32.W))
        
        val ctrl_RegWEn = Output(Bool()) //for Reg write back
        val ctrl_ASel = Output(Bool()) //for alu src1
        val ctrl_BSel = Output(Bool()) //for alu src2
        val ctrl_Br = Output(Bool()) //for branch inst.
        val ctrl_Jmp = Output(Bool()) //for jump inst.
        val ctrl_Lui = Output(Bool()) //for lui inst.
        val ctrl_MemRW = Output(Bool()) //for L/S inst
        val ctrl_WBSel = Output(UInt(2.W))
    })

    //Please fill in the blanks by yourself
    io.funct3 := io.inst(14,12)
    io.funct7 := io.inst(31,25)
    io.rs1 := io.inst(19,15)
    io.rs2 := io.inst(24,20)
    //Please fill in the blanks by yourself
    io.rd := io.inst(11,7)
    io.opcode := io.inst(6,0)

    
    //ImmGen
    io.imm := MuxLookup(io.opcode,0.S,Seq(
        //R-type
        OP->0.S,
        //Please fill in the blanks by yourself
        //I-type
        OP_IMM -> io.inst(31,20).asSInt,
        //Please fill in the blanks by yourself
        JALR ->io.inst(31,20).asSInt,
        //Please fill in the blanks by yourself
        LOAD ->io.inst(31,20).asSInt,
        //B-type
        //Please fill in the blanks by yourself
        BRANCH ->Cat(io.inst(31),io.inst(7),io.inst(30,25),io.inst(11,8),0.U(1.W)).asSInt,
        //S-type
        //Please fill in the blanks by yourself
        STORE ->Cat(io.inst(31,25),io.inst(11,7)).asSInt,
        //U-type
        //Please fill in the blanks by yourself
        LUI ->Cat(io.inst(31,12),0.U(12.W)).asSInt,
        //Please fill in the blanks by yourself
        AUIPC ->Cat(io.inst(31,12),0.U(12.W)).asSInt,
        //J-type
        //Please fill in the blanks by yourself
        JAL ->Cat(io.inst(31),io.inst(19,12),io.inst(20),io.inst(30,21),0.U(1.W)).asSInt
    ))

    //Controller
    io.ctrl_RegWEn := Mux(io.opcode===OP_IMM|io.opcode===OP|io.opcode===LOAD|io.opcode===JALR|io.opcode===JAL,true.B,false.B)
    io.ctrl_ASel := Mux(io.opcode===BRANCH|io.opcode===JAL,true.B,false.B)
    io.ctrl_BSel := Mux(io.opcode===OP_IMM|io.opcode===LOAD|io.opcode===STORE|io.opcode===BRANCH|io.opcode===JALR|io.opcode===JAL,true.B,false.B)
    io.ctrl_Br := Mux(io.opcode===BRANCH,true.B,false.B)
    io.ctrl_Jmp := Mux(io.opcode===JAL|io.opcode===JALR,true.B,false.B)
    io.ctrl_Lui := Mux(io.opcode===LUI,true.B,false.B)
    io.ctrl_MemRW := Mux(io.opcode===STORE,true.B,false.B) //write -> true,read -> false
    
    when(io.opcode===LOAD|io.opcode===STORE){
        io.ctrl_WBSel:=0.U
    }.elsewhen(io.opcode===JALR|io.opcode===JAL){
        io.ctrl_WBSel:=2.U
    }.otherwise{
        io.ctrl_WBSel:=1.U
    } //true: from alu , false: from dm , another source?
}