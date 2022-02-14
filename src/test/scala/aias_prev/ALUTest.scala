package aias_lab5.Hw4

import chisel3._
import chisel3.iotesters.{Driver,PeekPokeTester}
import ALU_funct3._,ALU_funct7._

object ALU_funct3{
  val ADD_SUB = "b000".U
  val SLL     = "b001".U
  val SLT     = "b010".U
  val SLTU    = "b011".U
  val XOR     = "b100".U
  val SRL_SRA = "b101".U
  val OR      = "b110".U
  val AND     = "b111".U
}

object ALU_funct7{
  val SUB_SRA = "b0100000".U
}

class ALUTest(dut:ALU) extends PeekPokeTester(dut){
  poke(dut.io.src1,37)
  poke(dut.io.src2,-9)
  poke(dut.io.funct3,ADD_SUB)
  poke(dut.io.funct7,SUB_SRA)
  println(peek(dut.io.ALUout).toString)
  step(1)

  poke(dut.io.src1,1)
  poke(dut.io.src2,32)
  poke(dut.io.funct3,SLL)
  poke(dut.io.funct7,0)
  println(peek(dut.io.ALUout).toString)
  step(1)

  poke(dut.io.src1,-8)
  poke(dut.io.src2,-9)
  poke(dut.io.funct3,SLTU)
  poke(dut.io.funct7,0)
  println(peek(dut.io.ALUout).toString)
  step(1)
}

object ALUTest extends App{
    Driver.execute(args,()=>new ALU){
        dut:ALU => new ALUTest(dut)
    }
}