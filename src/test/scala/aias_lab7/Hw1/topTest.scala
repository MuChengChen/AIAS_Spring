package aias_lab7.Hw1

import scala.io.Source
import chisel3.iotesters.{PeekPokeTester,Driver}

class topTest(dut:top) extends PeekPokeTester(dut){

    implicit def bigint2boolean(b:BigInt):Boolean = if (b>0) true else false

    val filename = "./src/main/resource/inst.asm"
    val lines = Source.fromFile(filename).getLines.toList

    while(!peek(dut.io.hcf_out)){
        var current_pc = peek(dut.io.pc_out).toInt
        println("Inst:"+lines(current_pc>>2))
        println("PC:" + peek(dut.io.pc_out).toString)
        println("ALU out:" + peek(dut.io.alu_out).toInt.toString)
        println("WBdata:" + peek(dut.io.rf_wdata_out).toInt.toString)
        println("Br taken:" + peek(dut.io.brtaken_out).toString)
        println("Jmp taken:" + peek(dut.io.jmptaken_out).toString)
        println("==============================")
        step(1)
    }
    step(1)
    println("Inst:Hcf")
    println("This is the end of the program!!")
    println("==============================")
}

object topTest extends App{
    Driver.execute(args,()=>new top){
        c:top => new topTest(c)
    }
}