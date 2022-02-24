package aias_prev

import chisel3._
import chisel3.iotesters.{Driver,PeekPokeTester}
import ALU_funct3._,ALU_funct7._

class ALUTest(dut:ALU) extends PeekPokeTester(dut){
  
  //ADD
  poke(dut.io.src1,37)
  poke(dut.io.src2,-9)
  poke(dut.io.funct3,ADD_SUB)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,(37-9))
  step(1)

  //SUB
  poke(dut.io.src1,37)
  poke(dut.io.src2,-9)
  poke(dut.io.funct3,ADD_SUB)
  poke(dut.io.funct7,SUB_SRA)
  expect(dut.io.ALUout,(37+9))
  step(1)
  
  //SLL
  poke(dut.io.src1,16)
  poke(dut.io.src2,4)
  poke(dut.io.funct3,SLL)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,256)
  step(1)
  
  //SLT
  poke(dut.io.src1,-8)
  poke(dut.io.src2,-5)
  poke(dut.io.funct3,SLT)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,1)
  step(1)

  //SLTU
  poke(dut.io.src1,-8)
  poke(dut.io.src2,-5)
  poke(dut.io.funct3,SLTU)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,1)
  step(1)

  //XOR
  poke(dut.io.src1,0x55)
  poke(dut.io.src2,0xAA)
  poke(dut.io.funct3,XOR)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,(1<<8)-1)
  step(1)

  //SRL
  poke(dut.io.src1,84)
  poke(dut.io.src2,3)
  poke(dut.io.funct3,SRL_SRA)
  poke(dut.io.funct7,0)
  expect(dut.io.ALUout,84/8)
  step(1)

  //SRA
  poke(dut.io.src1,0x80000000)
  poke(dut.io.src2,1)
  poke(dut.io.funct3,SRL_SRA)
  poke(dut.io.funct7,SUB_SRA)
  assert(peek((dut.io.ALUout)).toInt==0xC0000000)
  step(1)

  println("Congratulation, ALU test pass!!")
}

object ALUTest extends App{
    Driver.execute(args,()=>new ALU){
        dut:ALU => new ALUTest(dut)
    }
}