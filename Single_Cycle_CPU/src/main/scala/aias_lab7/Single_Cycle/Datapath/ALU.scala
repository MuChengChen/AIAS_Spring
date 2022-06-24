package aias_lab7.Single_Cycle.Datapath

import chisel3._
import chisel3.util._ 

import aias_lab7.Single_Cycle.Controller.opcode_map._

import aias_lab7.Single_Cycle.Controller.ALU_op._

class ALUIO extends Bundle{
  val src1    = Input(UInt(32.W))
  val src2    = Input(UInt(32.W))
  val ALUSel  = Input(UInt(32.W))
  val out  = Output(UInt(32.W))
}

class ALU extends Module{
  val io = IO(new ALUIO) 
  
  io.out := 0.U
  switch(io.ALUSel){
    is(ADD ){io.out := io.src1+io.src2}
    is(SLL ){io.out := io.src1 << io.src2(4,0)}
    is(SLT ){io.out := Mux(io.src1.asSInt<io.src2.asSInt,1.U,0.U)}
    is(SLTU){io.out := Mux(io.src1<io.src2              ,1.U,0.U)}
    is(XOR ){io.out := io.src1^io.src2}
    is(SRL ){io.out := io.src1 >> io.src2(4,0)}
    is(OR  ){io.out := io.src1|io.src2}
    is(AND ){io.out := io.src1&io.src2}
    is(SUB ){io.out := io.src1-io.src2}
    is(SRA ){io.out := (io.src1.asSInt >> io.src2(4,0)).asUInt}
    /*-----wilson-----*/
    is(clz ){
        for(i<-0 until 32){
            when(io.src1(31,31-i)===0.U){io.out := i.asUInt + 1.U}
        }
    } 
    is(ctz ){
        val tmp = io.src1 & (-io.src1)
        for(i<-0 until 32){
            when(tmp(i)===1.U){io.out := i.asUInt}
        }
    }
    is(cpop){
        val tmp = VecInit(Seq.fill(32)(0.U(32.W)))
        tmp := io.src1.asBools
        io.out := tmp.reduce(_+_)
    }
    is(andn){io.out := io.src1 & (~io.src2)}
    is(orn ){io.out := io.src1 | (~io.src2)}
    is(xnor){io.out := ~(io.src1 ^ io.src2)}
    is(min ){
        when(io.src1.asSInt <= io.src2.asSInt){
            io.out := io.src1
        }.otherwise{io.out := io.src2}
    }
    /*-----wilson-----*/


    /*---KAI----------*/
    is(sext_b){//Sign-extend byte: 把byte signed etension to 32-bit by R[rs](7)       X(rd) = EXTS(X(rs)[7..0]);
        val for_signed_ext = Wire(SInt(32.W))
        val temp = Wire(UInt(8.W))
        temp := Cat(io.src1(7,0))
        for_signed_ext := temp.asSInt //sign extension: 8bit signed to 32 bit就會自動做sign extension
        io.out := for_signed_ext.asUInt
    } 
    is(sext_h){// Sign-extend halfword: X(rd) = EXTS(X(rs)[15..0]);
        val for_signed_ext = Wire(SInt(32.W))
        val temp = Wire(UInt(16.W))
        temp := Cat(io.src1(15,0))
        for_signed_ext := temp.asSInt //sign extension: 16bit signed to 32 bit就會自動做sign extension
        io.out := for_signed_ext.asUInt        
    } 

    //!以下有shamt(而記住，I指令格式的指令會傳12-bit imm給ALU----12bit是 bit 20到bit 31)
    is(bseti ){//Single-Bit Set (Immediate): 12-bit imm取low-5-bit存入shamt，用這個shamt左移1，然後將此結果與rs做bitwise-or//todo
        val shamt = Wire(UInt(5.W))
        val shift_one = Wire(UInt(32.W))
        shamt := Cat(io.src2(4,0))//12取5
        shift_one := (1.U(32.W))<<shamt //1<<shamt
        io.out := io.src1 | shift_one  //X(rd) = X(rs1) | (1 << index)
    } 
    is(bclri){//Single-Bit Clear (Immediate)
        val shamt = Wire(UInt(5.W))
        val shift_one = WireDefault(0.U(32.W))
        shamt := Cat(io.src2(4,0))//12取5
        shift_one := (1.U)<<shamt //1<<shamt
        io.out := io.src1 & (~shift_one)  //X(rd) = X(rs1) & ~(1 << index)
    } 
    is(binvi){//Single-Bit Invert (Immediate)//todo
        val shamt = Wire(UInt(5.W))
        val shift_one = WireDefault(0.U(32.W))
        shamt := Cat(io.src2(4,0))//12取5
        shift_one := (1.U)<<shamt //1<<shamt
        io.out := io.src1 ^ shift_one  //X(rd) = X(rs1) ^ (1 << index)
    } 
    is(bexti){//Single-Bit Extract (Immediate)//todo
        val shamt = Wire(UInt(5.W))
        shamt := Cat(io.src2(4,0))//12取5
        io.out := (io.src1 >> shamt) & (1.U)  //X(rd) = (X(rs1) >> index) & 1;
    } 
    is(rori){//Rotate Right (Immediate)//todo
        val shamt = Wire(UInt(5.W))
        shamt := Cat(io.src2(4,0))//12取5
        io.out := (io.src1 >> shamt) | (io.src1 << (32.U-shamt)) //X(rd) = (X(rs1) >> shamt) | (X(rs1) << (xlen - shamt));
    } 
    /*---KAI----------*/
    /*-----Song-----*/


    is(max ){
        when(io.src1.asSInt <= io.src2.asSInt){
            io.out := io.src2
        }.otherwise{io.out := io.src1}
    }
    is(maxu ){
        when(io.src1.asUInt <= io.src2.asUInt){
            io.out := io.src2
        }.otherwise{io.out := io.src1}
    }
    is(minu ){
        when(io.src1.asUInt <= io.src2.asUInt){
            io.out := io.src1
        }.otherwise{io.out := io.src2}
    }
    is(bset){
        val index = Wire(UInt(5.W))
        val index_shift = Wire(UInt(32.W))
        index := Cat(io.src2(4,0))
        index_shift := (1.U(32.W)) << index
        io.out := io.src1 | index_shift  
    }
    is(bclr){
        val index = Wire(UInt(5.W))
        val index_shift = Wire(UInt(32.W))
        index := Cat(io.src2(4,0))
        index_shift := (1.U(32.W)) << index
        io.out := io.src1 &  ( ~index_shift)  
    }
    is(binv){
        val index = Wire(UInt(5.W))
        val index_shift = Wire(UInt(32.W))
        index := Cat(io.src2(4,0))
        index_shift := (1.U(32.W)) << index
        io.out := io.src1 ^ index_shift 
    }
    is(bext){
        val index = Wire(UInt(5.W))
        index := Cat(io.src2(4,0))
        io.out := (io.src1 >> index) & 1.U(1.W)
    }
    is(ror){
        val shamt = Wire(UInt(5.W))
        shamt := Cat(io.src2(4,0))
        io.out := (io.src1 >> shamt) | ( io.src1 << (32.U - shamt))
    }
    is(rol){
        val shamt = Wire(UInt(5.W))
        shamt := Cat(io.src2(4,0))
        io.out := (io.src1 << shamt) | ( io.src1 >> (32.U - shamt))
    }

    /*-----Song-----*/



}
}

