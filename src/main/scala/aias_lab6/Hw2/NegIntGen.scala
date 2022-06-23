package aias_lab6.Hw2

import chisel3._
import chisel3.util._

class NegIntGen extends Module{
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
    val src1 = RegInit(0.U(32.W))

    val sIdle::sSrc1::sOp::sEqual::Nil=Enum(4)
    
    
    val left_brackets_flag=RegInit(0.U(1.W))
    val negative_sign=RegInit(0.U(1.W))

    val state=RegInit(sIdle)

    switch(state){
        is(sIdle){
            when(operator){
                state:=sOp
            }.elsewhen(num){
                state:=sSrc1
            }
        }
        is(sSrc1){
            when(equal){
                state:=sEqual
            }.elsewhen(operator){
                state:=sOp
            }
        }
        is(sOp){
            when(num){
                state:=sSrc1
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
            src1:=((src1<<3.U)+(src1<<1.U)-in_buffer1)
            
        }.otherwise{
        src1:=(src1<<3.U)+(src1<<1.U)+in_buffer1
        }
    }
    
    when(state===sOp){
        when(in_buffer1===13.U){
            left_brackets_flag:=1.U
        }.elsewhen(in_buffer1===11.U){
            negative_sign:=1.U
        }.elsewhen(in_buffer1===14.U){
            left_brackets_flag:=0.U
            negative_sign:=0.U
        }
    }

    when(state===sEqual){
        src1:=0.U
        //op:=0.U
    }


    io.value.valid := Mux(state===sEqual,true.B,false.B)
    io.value.bits := Mux(left_brackets_flag===1.U && negative_sign===1.U,src1,src1)
}