package aias_lab5.Hw1

import chisel3.iotesters.{Driver,PeekPokeTester}

class MixAdderTest (dut:MixAdder) extends PeekPokeTester(dut){

    for (i <- 0 until 1000){
        val x = rnd.nextInt(1<<30)
        val y = rnd.nextInt(1<<30)

        poke(dut.io.in1,x)
        poke(dut.io.in2,y)
        expect(dut.io.Sum,x+y)
        step(1)
    }

    println("MixAdder test completed!!!!!")
}

object MixAdderTest extends App{
    Driver.execute(args,()=>new MixAdder(8)){
        c => new MixAdderTest(c)
    }
}