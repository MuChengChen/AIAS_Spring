package aias_lab6.Hw1

import chisel3.iotesters.{Driver,PeekPokeTester}

class NegIntGenTest(dut:NegIntGen) extends PeekPokeTester(dut){

    val dict = Map(
      '0' -> 0,
      '1' -> 1,
      '2' -> 2,
      '3' -> 3,
      '4' -> 4,
      '5' -> 5,
      '6' -> 6,
      '7' -> 7,
      '8' -> 8,
      '9' -> 9,
      '+' -> 10,
      '-' -> 11,
      '*' -> 12,
      '(' -> 13,
      ')' -> 14,
      '=' -> 15
    )
    
    "(-1234)=".foreach{ x =>
        poke(dut.io.key_in,dict(x))
        step(1)
    }
    assert(peek(dut.io.value.bits).toInt==(-1234))
    step(1)

    Seq('(','-','5','4','2','1',')','=').foreach{ x =>
        poke(dut.io.key_in,dict(x))
        step(1)
    }
    assert(peek(dut.io.value.bits).toInt==(-5421))
    step(1)

    "5487=".foreach{ x =>
        poke(dut.io.key_in,dict(x))
        step(1)
    }
    expect(dut.io.value.bits,5487)
    step(1)
}

object NegIntGenTest extends App{
    Driver.execute(args,()=>new NegIntGen){
        c:NegIntGen => new NegIntGenTest(c)
    }
}