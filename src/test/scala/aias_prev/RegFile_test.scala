package aias_prev

import chisel3.iotesters._

class RegFileTests (regfile : RegFile) extends PeekPokeTester(regfile){

//   poke(regfile.io.raddr1,0)
//   poke(regfile.io.raddr2,5)
//   println("REG 0 = " + peek(regfile.io.rdata1).toString)
//   println("REG 5 = " + peek(regfile.io.rdata2).toString)
//   step(1)


//   poke(regfile.io.raddr1,10)
//   println("REG 10 = " + peek(regfile.io.rdata1).toString)
  val value = Array(54,32,11,76,123,543)

  for((v,i) <- value.zipWithIndex){
    poke(regfile.io.wen,1)
    poke(regfile.io.waddr,i*2)
    poke(regfile.io.wdata,v)
  step(1)
  }

  poke(regfile.io.raddr1,0)
  poke(regfile.io.raddr2,2)
  println("REG 0 = " + peek(regfile.io.rdata1).toString)
  println("REG 2 = " + peek(regfile.io.rdata2).toString)
  step(1)


}

//note:
//1.WAR when at the same time
//2.Initial value : 0.U in Men

object RegFileTests extends App {
  Driver(() => new RegFile()) {regfile =>
    new RegFileTests(regfile)
  }
}