package aias_lab5.Hw4

import chisel3._
import chisel3.iotesters.{Driver,PeekPokeTester}

import condition._

class BranchCompTest(dut:BranchComp) extends PeekPokeTester(dut){
    
    def u_int (in:Int):BigInt = {
        val tmp: BigInt = in & 0x00000000ffffffff
        tmp
    }

    for(i <- 0 until 20){
        var src1 = rnd.nextInt(1<<30) << 1 
        var src2 = rnd.nextInt(1<<30) << 1 

        for (en <- Seq(true,false)){
            poke(dut.io.en,en)
            poke(dut.io.src1,src1)
            poke(dut.io.src2,src2)
            //======================

            if(en == false){
                expect(dut.io.brtaken,false)
                step(1)
            }else{
                poke(dut.io.funct3, EQ.litValue())
                expect(dut.io.brtaken,if(src1==src2) true else false)
                step(1)

                poke(dut.io.funct3, NE.litValue())
                expect(dut.io.brtaken,if(src1!=src2) true else false)
                step(1)

                poke(dut.io.funct3, LT.litValue())
                expect(dut.io.brtaken,if(src1<src2) true else false)
                step(1)

                poke(dut.io.funct3, GE.litValue())
                expect(dut.io.brtaken,if(src1>=src2) true else false)
                step(1)

                poke(dut.io.funct3, LTU.litValue())
                expect(dut.io.brtaken,if(src1<src2) true else false)
                step(1)

                poke(dut.io.funct3, GEU.litValue())
                expect(dut.io.brtaken,if(src1>=src2) true else false)
                step(1)
            }
        }
    }
}

object BranchCompTest extends App{
    
    Driver.execute(args,()=>new BranchComp()){
        c:BranchComp => new BranchCompTest(c)
    }
}