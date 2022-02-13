package aias_prev

import chisel3.iotesters.{Driver,PeekPokeTester}

class MemoryTest (dut:Memory) extends PeekPokeTester(dut){
  poke(dut.io.wen,true)
  poke(dut.io.waddr,6)
  poke(dut.io.wdata,8787)
  poke(dut.io.raddr,4)
  step(1)

  poke(dut.io.wen,false)
  poke(dut.io.waddr,6)
  poke(dut.io.wdata,8787)
  poke(dut.io.raddr,6)
  step(2)
}

object MemoryTest extends App{
    Driver.execute(args,()=>new Memory){
        c => new MemoryTest(c)
    }
}