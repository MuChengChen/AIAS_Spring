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

    /*-----Oscar---*/

    is(rev8){
        val mask=Wire(UInt(32.W))
        val mask2=Wire(UInt(32.W))
        val mask3=Wire(UInt(32.W))
        val mask4=Wire(UInt(32.W))

        mask:="h000000ff".U
        mask2:="h0000ff00".U
        mask3:="h00ff0000".U
        mask4:="hff000000".U

        val w1=Wire(UInt(32.W))
        val w2=Wire(UInt(32.W))
        val w3=Wire(UInt(32.W))
        val w4=Wire(UInt(32.W))

        w1:=(mask & io.src1)<<24.U
        w2:=(mask2 & io.src1)<<8.U
        w3:=(mask3 & io.src1)>>8.U
        w4:=(mask4 & io.src1)>>24.U

        io.out:=(w1|w2|w3|w4)
    }
    is(orc_d){
        val mask=Wire(UInt(32.W))
        val mask2=Wire(UInt(32.W))
        val mask3=Wire(UInt(32.W))
        val mask4=Wire(UInt(32.W))

        //mask:="h000000ff".U
        //mask2:="h0000ff00".U
        //mask3:="h00ff0000".U
       // mask4:="hff000000".U

        val w1=Wire(UInt(32.W))
        val w2=Wire(UInt(32.W))
        val w3=Wire(UInt(32.W))
        val w4=Wire(UInt(32.W))

        mask:="h000000ff".U & io.src1
        mask2:=("h0000ff00".U & io.src1)>>8.U
        mask3:=("h00ff0000".U & io.src1)>>16.U
        mask4:=("hff000000".U & io.src1)>>24.U

        w1:=Mux(mask===0.U,0.U,0xff.U)
        w2:=Mux(mask2===0.U,0.U,0xff.U<<8.U)
        w3:=Mux(mask3===0.U,0.U,0xff.U<<16.U)
        w4:=Mux(mask4===0.U,0.U,0xff.U<<24.U)

        io.out:=(w4|w3|w2|w1)

    }
    is(zext_h){
        io.out := Cat(0.U,io.src1(15,0))
    }
    is(sh1add){
        io.out := io.src2+(io.src1<<1.U)
    }
    is(sh2add){
        io.out := io.src2+(io.src1<<2.U)
    }
    is(sh3add){
        io.out := io.src2+(io.src1<<3.U)
    }
    /*-----Oscar---*/

}
}

