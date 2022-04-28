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
  /*---wilson---*/
  val clz  = 14.U
  val ctz  = 15.U
  val cpop = 16.U
  val andn = 17.U
  val orn  = 18.U
  val xnor = 19.U
  val min  = 20.U
  /*---wilson---*/

  /*---KAI---*/
  val sext_b = 21.U
  val sext_h = 22.U
  val bseti  = 23.U
  val bclri  = 24.U
  val binvi  = 25.U
  val bexti  = 26.U
  val rori   = 27.U
  /*---KAI---*/



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

import opcode_map._,condition._,ALU_op._,inst_type._

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
        val ALUSel = Output(UInt(32.W))
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
    
    val rs2 = Wire(UInt(5.W))
    rs2 := io.Inst(24,20)

    val funct7 = Wire(UInt(7.W))
    funct7 := io.Inst(31,25)

    //Control signal
    io.ASel := Mux(opcode===BRANCH||opcode===JAL,true.B,false.B)
    io.BSel := Mux(opcode===OP,false.B,true.B)
    io.BrUn := Mux(funct3===LTU||funct3===GEU,true.B,false.B)
    io.MemRW := Mux(opcode===STORE,true.B,false.B)
    io.ImmSel := MuxLookup(opcode,0.U,Seq(
        LOAD->I,
        STORE->S,
        BRANCH->B,
        JALR->I,
        JAL->J,
        OP_IMM->I,
        OP->R,
        AUIPC->U,
        LUI->U,
    ))
    io.ALUSel := Mux(opcode===OP||opcode===OP_IMM,funct3,ADD)
    when(funct7(5)===1.U && (opcode===OP || opcode===OP_IMM)){
        when(funct3=== ADD && opcode===OP){
            io.ALUSel := SUB
        }.elsewhen(funct3===SRL) {io.ALUSel := SRA}
    }
    io.PCSel := Mux(opcode===JAL||opcode===JALR,true.B,false.B)
    when(opcode===BRANCH){
        switch(funct3){
            is(EQ) {io.PCSel := io.BrEq}
            is(NE) {io.PCSel := ~io.BrEq}
            is(LT) {io.PCSel := io.BrLT}
            is(GE) {io.PCSel := ~io.BrLT}
            is(LTU) {io.PCSel := io.BrLT}
            is(GEU) {io.PCSel := ~io.BrLT}
        }
    }
    io.WBSel := MuxLookup(opcode,1.U,Seq(
        LOAD->0.U,
        JALR->2.U,
        JAL->2.U,
        //OP_IMM->1.U,
        //OP->1.U,
        //AUIPC->1.U,
        //LUI->1.U,
    ))
    io.RegWEn := Mux(opcode===STORE||opcode===BRANCH||opcode===HCF,false.B,true.B)
    io.Hcf := opcode === HCF
    io.Lui := opcode === LUI

    /*--Extension--*/
    when(opcode===OP_IMM){
        /*-----wilson-----*/
        when(funct7==="h30".U && rs2===0.U && funct3===1.U){
            io.ALUSel := clz
        }.elsewhen(funct7==="h30".U && rs2==="h1".U && funct3===1.U){
            io.ALUSel := ctz
        }.elsewhen(funct7==="h30".U && rs2==="h2".U && funct3===1.U){
            io.ALUSel := cpop
        }
        /*-----wilson-----*/


        /*---KAI----------*/
        when(funct7==="h30".U && rs2==="h4".U && funct3===1.U){
            io.ALUSel := sext_b
        }.elsewhen(funct7==="h30".U && rs2==="h5".U && funct3===1.U){
            io.ALUSel := sext_h
        }
        
        //!以下無rs2，但有shamt
        .elsewhen(funct7==="h14".U && funct3===1.U){ //!shamt怎麼處理?    0x14  shamt  0x1--->bseti()
            io.ALUSel := bseti  
        }.elsewhen(funct7==="h24".U && funct3===1.U){ //!shamt怎麼處理?    0x24  shamt  0x1--->bclri
            io.ALUSel := bclri 
        }.elsewhen(funct7==="h34".U && funct3===1.U){ //!shamt怎麼處理?    0x34  shamt  0x1--->binvi 
            io.ALUSel := binvi  
        }.elsewhen(funct7==="h24".U && funct3==="h5".U){//!shamt怎麼處理?    0x24  shamt  0x5--->bexti
            io.ALUSel := bexti 
        }.elsewhen(funct7==="h30".U && funct3==="h5".U){//!shamt怎麼處理?    0x30  shamt  0x5--->rori
            io.ALUSel := rori
        } 
        /*---KAI-----------*/





    }
    when(opcode===OP){
        /*-----wilson-----*/
        when(funct7==="h20".U && funct3==="h7".U){
            io.ALUSel := andn
        }.elsewhen(funct7==="h20".U && funct3==="h6".U){
            io.ALUSel := orn
        }.elsewhen(funct7==="h20".U && funct3==="h4".U){
            io.ALUSel := xnor
        }.elsewhen(funct7==="h5".U && funct3==="h4".U){
            io.ALUSel := min
        }
        /*-----wilson-----*/


    }
}
