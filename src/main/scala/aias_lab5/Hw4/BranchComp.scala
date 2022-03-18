package aias_lab5.Hw4

import chisel3._
import chisel3.util._

object condition{
  val EQ = "b000".U
  val NE = "b001".U
  val LT = "b100".U
  val GE = "b101".U
  val LTU = "b110".U
  val GEU = "b111".U
}

import condition._

class BranchComp extends Module{
    val io = IO(new Bundle{
        val en = Input(Bool())
        val funct3 = Input(UInt(3.W))
        val src1 = Input(UInt(32.W))
        val src2 = Input(UInt(32.W))

        val brtaken = Output(Bool()) //for pc.io.brtaken
    })

    val eq = WireDefault(false.B)
    val lt = WireDefault(false.B)

    when(io.funct3 === LTU || io.funct3 === GEU){
      when(io.src1 < io.src2) { lt := true.B }
    }.otherwise{
      when(io.src1.asSInt === io.src2.asSInt) { eq := true.B }
      when(io.src1.asSInt < io.src2.asSInt) { lt := true.B }
    }
    
    io.brtaken := false.B
    
    when(io.en){
      when(io.funct3 === EQ &&  eq){io.brtaken := true.B}
      when(io.funct3 === NE && !eq){io.brtaken := true.B}
      when((io.funct3 === LT || io.funct3 === LTU) &&  lt){io.brtaken := true.B}
      when((io.funct3 === GE || io.funct3 === GEU) && !lt){io.brtaken := true.B}
    }
    


}