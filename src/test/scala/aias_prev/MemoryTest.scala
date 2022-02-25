package aias_prev

import chisel3.iotesters.{Driver,PeekPokeTester}

class MemoryTest (dut:Memory) extends PeekPokeTester(dut){
  //  test the initial values in the memory
  //  read ports test
  for(i <- 0 until 256){
    poke(dut.io.raddr,i)
    step(1)
    expect(dut.io.rdata,(i+1))
  }
  
  //wen test
  poke(dut.io.wen,false)
  poke(dut.io.waddr,20)
  poke(dut.io.wdata,9487)
  step(1)

  poke(dut.io.raddr,20)
  step(1)

  expect(dut.io.rdata,21)
  poke(dut.io.wen,true)
  poke(dut.io.waddr,20)
  poke(dut.io.wdata,9487)
  step(1)

  poke(dut.io.raddr,20)
  expect(dut.io.rdata,9487)

  // //Read-Write test
  // for(i <- 1 until 32){
  //   poke(dut.io.wen,true)
  //   poke(dut.io.waddr,i)
  //   poke(dut.io.wdata,(32-i))
  //   step(1)

  //   poke(dut.io.raddr,i)
  //   println("Reg "+i+" = "+peek(dut.io.rdata).toString)
  // }

  println("Congratulation, Memory test pass!!")
}

object MemoryTest extends App{
    Driver.execute(args,()=>new Memory){
        c => new MemoryTest(c)
    }
}