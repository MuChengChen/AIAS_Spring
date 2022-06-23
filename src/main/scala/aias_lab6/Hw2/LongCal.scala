package aias_lab6.Hw2

import chisel3._
import chisel3.util._

class LongCal extends Module{
    val io = IO(new Bundle{
        val key_in = Input(UInt(4.W))
        val value = Output(Valid(UInt(32.W)))
    })

    //please implement your code below
    val operator=WireDefault(false.B)
    operator :=io.key_in>=10.U && io.key_in<=14.U

    val num=WireDefault(false.B)
    num := io.key_in<10.U

    val equal=WireDefault(false.B)
    equal := io.key_in===15.U

    val in_buffer1 = RegNext(io.key_in)
    //val in_buffer2 = RegNext(in_buffer1)
    val src1 = RegInit(0.U(32.W))
    val op = RegInit(0.U(2.W))
    val src2 = RegInit(0.U(32.W))

    val sIdle::sSrc1::sOp::sSrc2::sEqual::Nil=Enum(5)
    val add=1.U
    val sub=2.U
    
    
    val left_brackets_flag=RegInit(0.U(1.W))
    val negative_sign=RegInit(0.U(1.W))
    val src1_flag=RegInit(0.U(1.W))

    val state=RegInit(sIdle)

    switch(state){
        is(sIdle){
            when(operator){
                state:=sOp
            }.elsewhen(num){
                state:=sSrc1
                src1_flag:=1.U
            }
        }
        is(sSrc1){
            when(operator){
                state:=sOp
            }.elsewhen(equal){
                state:=sEqual
            }
        }
        is(sOp){
            when(num && src1_flag===1.U){
                state:=sSrc2
            }.elsewhen(num && src1_flag===0.U){
                state:=sSrc1
                src1_flag:=1.U
            }.elsewhen(equal){
                state:=sEqual
            }
        }
        is(sSrc2){
            when(operator){
                state:=sOp
            }.elsewhen(equal){
                state:=sEqual
            }
        }
        is(sEqual){
           state:=sIdle
        }
    }

    when(state===sSrc1){
        when(left_brackets_flag===1.U && negative_sign===1.U ){
            src1:=((src1<<3.U)+(src1<<1.U))-in_buffer1
            
        }.otherwise{
            src1:=(src1<<3.U)+(src1<<1.U)+in_buffer1
        }
    }
    when(state===sSrc2){
        when(left_brackets_flag===1.U && negative_sign===1.U ){
            src2:=((src2<<3.U)+(src2<<1.U))-in_buffer1
        }.otherwise{
            src2:=(src2<<3.U)+(src2<<1.U)+in_buffer1
        }
    }
    when(state===sOp){
        when(left_brackets_flag=/=1.U  && in_buffer1=/=13.U){
            when(op=/=0.U){
                src1:= MuxLookup(op,0.U,Seq(
                    add->(src1+src2),
                    sub->(src1-src2)
                ))
                src2:=0.U    
            }
            when(in_buffer1===10.U || in_buffer1===11.U){
                op:=in_buffer1-9.U
            }
        }.elsewhen(in_buffer1===13.U){
            left_brackets_flag:=1.U
        }.elsewhen(in_buffer1===11.U && left_brackets_flag===1.U){
            negative_sign:=1.U
        }
        
        
        
    }
    when(io.key_in===14.U){
        left_brackets_flag:=0.U
        negative_sign:=0.U
    }
    when(state===sEqual){
        src1:=0.U
        src2:=0.U
        op:=0.U
    }

    
    io.value.valid := Mux(state===sEqual,true.B,false.B)
    io.value.bits :=src1
    when(io.key_in===15.U){
        when(in_buffer1=/=14.U){
            when(op=/=0.U){
                io.value.bits := MuxLookup(op,0.U,Seq(
                add->(src1+src2),
                sub->(src1-src2)
                ))
            } 
        }
        src1_flag:=0.U
    }
}