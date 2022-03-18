package aias_lab5.Hw4

import chisel3._
import chisel3.util._

class top extends Module {
    val io = IO(new Bundle{
        val pc_out = Output(UInt(32.W))
        val alu_out = Output(UInt(32.W))
        val rf_wdata_out = Output(UInt(32.W))
    })

    val pc = Module(new PC())
    val im = Module(new InstMem())
    val dc = Module(new Decoder())
    val rf = Module(new RegFile(2))
    val alu = Module(new ALU())
    
    //PC
    pc.io.jmptaken := false.B
    pc.io.brtaken := false.B
    pc.io.offset := 0.U
    
    //Insruction Memory
    im.io.raddr := pc.io.pc
    
    //Decoder
    dc.io.inst := im.io.rdata
    
    //RegFile
    rf.io.raddr(0) := dc.io.rs1
    rf.io.raddr(1) := 0.U
    rf.io.wdata := alu.io.out
    
    //Dont change in this Lab=========
    rf.io.waddr := 0.U
    rf.io.wen := false.B
    //================================


    //ALU
    val rdata_or_zero = WireDefault(0.U(32.W))
    alu.io.src1 := rf.io.rdata(0)
    alu.io.src2 := dc.io.imm.asUInt
    alu.io.funct3 := dc.io.funct3
    alu.io.opcode := dc.io.opcode
    
    //Data Memory
    
    //Branch Comparator
    
    
    //Check Ports
    io.pc_out := pc.io.pc
    io.alu_out := alu.io.out 
    io.rf_wdata_out := rf.io.wdata
}