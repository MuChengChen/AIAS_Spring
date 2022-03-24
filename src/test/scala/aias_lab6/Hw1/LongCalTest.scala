package aias_lab6.Hw1

import chisel3.iotesters.{Driver,PeekPokeTester}

class LongCalTest(dut:LongCal) extends PeekPokeTester(dut){

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
    
    "(-15)-15-(-15)+(-15)=".foreach{ x =>
        poke(dut.io.key_in,dict(x))
        step(1)
    }
    while(peek(dut.io.value.valid) == 0){
        step(1)
    }
    assert(peek(dut.io.value.bits).toInt==(-30))
    step(1)

    // "17-16+(-15)-14+13-12+(-11)=".foreach{ x =>
    //     poke(dut.io.key_in,dict(x))
    //     step(1)
    // }
    // while(peek(dut.io.value.valid) == 0){
    //     step(1)
    // }
    // expect(dut.io.value.bits,17-16+(-15)-14+13-12+(-11))
    // step(1)
}

object LongCalTest extends App{
    Driver.execute(args,()=>new LongCal){
        c:LongCal => new LongCalTest(c)
    }
}