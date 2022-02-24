package aias_prev

import chisel3.iotesters.{Driver,PeekPokeTester}

class MemoryTest (dut:Memory) extends PeekPokeTester(dut){
  step(10)
}

object MemoryTest extends App{
    Driver.execute(args,()=>new Memory){
        c => new MemoryTest(c)
    }
}