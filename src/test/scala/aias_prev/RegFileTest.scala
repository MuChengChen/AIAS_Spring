package aias_prev

import chisel3.iotesters._

class RegFileTest (rf : RegFile) extends PeekPokeTester(rf){

  //  test the initial values in the regs
  //  read ports test
  for(i <- 0 until 16){
    poke(rf.io.raddr(0),2*i)
    poke(rf.io.raddr(1),(2*i+1))
    expect(rf.io.rdata(0),2*i)
    expect(rf.io.rdata(1),(2*i+1))
    step(1)
  }
  
  //wen test
  poke(rf.io.wen,false)
  poke(rf.io.waddr,20)
  poke(rf.io.wdata,9487)
  step(1)

  poke(rf.io.raddr(0),20)
  expect(rf.io.rdata(0),20)
  poke(rf.io.wen,true)
  poke(rf.io.waddr,20)
  poke(rf.io.wdata,9487)
  step(1)

  poke(rf.io.raddr(0),20)
  expect(rf.io.rdata(0),9487)

  //Reg zero test
  poke(rf.io.wen,true)
  poke(rf.io.waddr,0)
  poke(rf.io.wdata,1234)
  step(1)
  poke(rf.io.raddr(0),0)
  assert(peek(rf.io.rdata(0))==0)

  //Read-Write test
  for(i <- 1 until 32){
    poke(rf.io.wen,true)
    poke(rf.io.waddr,i)
    poke(rf.io.wdata,(32-i))
    step(1)

    poke(rf.io.raddr(1),i)
    println("Reg "+i+" = "+peek(rf.io.rdata(1)).toString)
  }

  println("Congratulation, RegFile test pass!!")
}

object RegFileTest extends App {
  Driver.execute(args,() => new RegFile(2)) {c =>
    new RegFileTest(c)
  }
}