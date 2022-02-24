package aias_prev

import chisel3.iotesters.{PeekPokeTester,Driver}

class Mux2_32bTest(dut:Mux2_32b) extends PeekPokeTester(dut) {
  
  var lst = List(true,false)
  val in1 = 87
  val in2 = 78
  
  for(select <- lst){
    poke(dut.io.sel,select)
    poke(dut.io.in1,in1)
    poke(dut.io.in2,in2)
  
    if(select){
      assert(peek(dut.io.out)==in1)
    }else{
      assert(peek(dut.io.out)==in2)
    }
  }

  println("Congratulation, Mux2_32b test pass!!")
  
}

object Mux2_32bTest extends App{
  Driver.execute(args,()=>new Mux2_32b){
    c => new Mux2_32bTest(c)
  }
}
