package aias_prev

import chisel3.iotesters.{PeekPokeTester,Driver}

class Mux2_32bTest(dut:Mux2_32b) extends PeekPokeTester(dut) {
  poke(dut.io.sel,true)
  poke(dut.io.in1,30)
  poke(dut.io.in2,60)
  println(peek(dut.io.out).toString)
}

object Mux2_32bTest extends App{
  Driver.execute(args,()=>new Mux2_32b){
    c => new Mux2_32bTest(c)
  }
}
