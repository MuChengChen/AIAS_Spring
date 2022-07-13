package aias_lab6.Hw2

import chisel3._
import chisel3.util._

class CpxCal extends Module{
    val io = IO(new Bundle{
        val key_in = Input(UInt(4.W))
        val value = Output(Valid(UInt(300.W)))
    })

    //please implement your code below
    io.value.valid := false.B
    io.value.bits := 0.U

    val Num=Module(new NegIntGen)
    Num.io.key_in:=16.U

    val store_operator_reverse=Module(new Stack(1000))//store,operator,reverse stream stack
    store_operator_reverse.io.en:=false.B
    store_operator_reverse.io.clean:=false.B
    store_operator_reverse.io.pop:=false.B
    store_operator_reverse.io.push:=false.B
    store_operator_reverse.io.dataIn:=0.U
    val store_reverse=Module(new Stack(1000))//reverse store stack
    store_reverse.io.en:=false.B
    store_reverse.io.clean:=false.B
    store_reverse.io.pop:=false.B
    store_reverse.io.push:=false.B
    store_reverse.io.dataIn:=0.U
    val stream_result=Module(new Stack(1000))//stream,result stack
    stream_result.io.en:=false.B
    stream_result.io.clean:=false.B
    stream_result.io.pop:=false.B
    stream_result.io.push:=false.B
    stream_result.io.dataIn:=0.U

    val in_buffer1=RegNext(io.key_in)

    val sIdle::sStore::sStoreReverse::sNum::sOp::sBrackets::sEqual::sReverse::sCal::sOut::Nil=Enum(10)
    val state=RegInit(sIdle)

    val neg_flag=RegInit(0.U(1.W))
    val right_bracket_flag=RegInit(0.U(1.W))
    val calculate_flag=RegInit(0.U(2.W))

    val cal_sign=RegInit(0.U(4.W))
    val src1=RegInit(0.U(300.W))
    val src2=RegInit(0.U(300.W))

    switch(state){
        is(sIdle){
            when(io.key_in>=0.U && io.key_in<=15.U){
                state:=sStore
            }
        }
        is(sStore){
            when(io.key_in===15.U){
                state:=sStoreReverse
            }
        }
        is(sStoreReverse){
            when(store_operator_reverse.io.empty){
                store_operator_reverse.io.en:=true.B
                store_operator_reverse.io.clean:=true.B
                when(store_reverse.io.topdata<10.U){
                    state:=sNum
                }.elsewhen(store_reverse.io.topdata===5010.U || store_reverse.io.topdata===5011.U || store_reverse.io.topdata===5012.U){
                    state:=sOp
                }.elsewhen(store_reverse.io.topdata===5013.U || store_reverse.io.topdata===5014.U){
                    state:=sBrackets
                }
            }
        }
        is(sNum){
            when(Num.io.value.valid){
                when(store_reverse.io.topdata===5010.U || store_reverse.io.topdata===5011.U || store_reverse.io.topdata===5012.U){
                    state:=sOp
                }.elsewhen(store_reverse.io.topdata===5013.U || store_reverse.io.topdata===5014.U){
                    state:=sBrackets
                }.elsewhen(store_reverse.io.empty){
                    state:=sEqual
                    store_reverse.io.en:=true.B
                    store_reverse.io.clean:=true.B
                }
            }
        }
        is(sOp){
            when(store_reverse.io.topdata<10.U){
                state:=sNum
            }.elsewhen(store_reverse.io.topdata===5013.U || store_reverse.io.topdata===5014.U){
                state:=sBrackets
            }.elsewhen(store_reverse.io.empty){
                state:=sEqual
                store_reverse.io.en:=true.B
                store_reverse.io.clean:=true.B
            }

        }
        is(sBrackets){
            when(store_reverse.io.topdata<10.U && neg_flag===0.U && right_bracket_flag===0.U && !store_reverse.io.empty){
                state:=sNum
            }.elsewhen((store_reverse.io.topdata===5010.U || store_reverse.io.topdata===5011.U || store_reverse.io.topdata===5012.U) && neg_flag===0.U && right_bracket_flag===0.U && !store_reverse.io.empty){
                state:=sOp
            }.elsewhen(store_reverse.io.empty && neg_flag===0.U && right_bracket_flag===0.U){
                state:=sEqual
                store_reverse.io.en:=true.B
                store_reverse.io.clean:=true.B
            }
        }
        is(sEqual){
            when(store_operator_reverse.io.empty){
                state:=sReverse
                store_operator_reverse.io.en:=true.B
                store_operator_reverse.io.clean:=true.B
            }
        }
        is(sReverse){
            when(stream_result.io.empty){
                state:=sCal
                stream_result.io.en:=true.B
                stream_result.io.clean:=true.B
            }
        }
        is(sCal){
            when(store_operator_reverse.io.empty && calculate_flag===0.U && src1===0.U && src2===0.U && cal_sign===0.U){
                state:=sOut
            }
        }
        is(sOut){
            state:=sIdle
        }
    }

    when(state===sIdle){
        store_reverse.io.en:=true.B
        store_reverse.io.clean:=true.B

        store_operator_reverse.io.en:=true.B
        store_operator_reverse.io.clean:=true.B

        stream_result.io.en:=true.B
        stream_result.io.clean:=true.B
    }

    when(state===sStore){
        store_operator_reverse.io.en:=true.B
        store_operator_reverse.io.push:=true.B
        when(in_buffer1>=10.U){
            store_operator_reverse.io.dataIn:=in_buffer1+5000.U
        }.otherwise{
            store_operator_reverse.io.dataIn:=in_buffer1
        } 
    }

    when(state===sStoreReverse){
        when(!store_operator_reverse.io.empty){
            store_operator_reverse.io.en:=true.B
            store_reverse.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            store_reverse.io.push:=true.B
            store_reverse.io.dataIn:=store_operator_reverse.io.dataOut
        }
        
    }

    when(state===sNum){
        when(store_reverse.io.topdata<10.U && !store_reverse.io.empty){
            store_reverse.io.en:=true.B
            store_reverse.io.pop:=true.B
            Num.io.key_in:=store_reverse.io.dataOut
        }.elsewhen((store_reverse.io.topdata>=10.U || store_reverse.io.empty) && !Num.io.value.valid){
            Num.io.key_in:=15.U
        }.elsewhen(Num.io.value.valid){
            stream_result.io.en:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=Num.io.value.bits
        }
        
    }

    when(state===sOp){
        when((store_reverse.io.topdata===5010.U || store_reverse.io.topdata===5011.U) && store_operator_reverse.io.topdata=/=5013.U && !store_operator_reverse.io.empty){
            store_operator_reverse.io.en:=true.B
            stream_result.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=store_operator_reverse.io.dataOut
        }.elsewhen((store_reverse.io.topdata===5010.U || store_reverse.io.topdata===5011.U) && (store_operator_reverse.io.topdata===5013.U || store_operator_reverse.io.empty) ){
            store_operator_reverse.io.en:=true.B
            store_reverse.io.en:=true.B
            store_operator_reverse.io.push:=true.B
            store_reverse.io.pop:=true.B
            store_operator_reverse.io.dataIn:=store_reverse.io.dataOut
        }.elsewhen(store_reverse.io.topdata===5012.U && (store_operator_reverse.io.topdata=/=5012.U || store_operator_reverse.io.empty)){
            store_operator_reverse.io.en:=true.B
            store_reverse.io.en:=true.B
            store_operator_reverse.io.push:=true.B
            store_reverse.io.pop:=true.B
            store_operator_reverse.io.dataIn:=store_reverse.io.dataOut
        }.elsewhen(store_reverse.io.topdata===5012.U && store_operator_reverse.io.topdata===5012.U ){
            store_operator_reverse.io.en:=true.B
            stream_result.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=store_operator_reverse.io.dataOut
        }
    }

    when(state===sBrackets){
        when(store_reverse.io.topdata===5013.U && right_bracket_flag===0.U){
            when(store_reverse.io.seconddata===5011.U){
                neg_flag:=1.U
                store_reverse.io.en:=true.B
                store_reverse.io.pop:=true.B
                Num.io.key_in:=store_reverse.io.dataOut-5000.U
            }.otherwise{
                store_operator_reverse.io.en:=true.B
                store_reverse.io.en:=true.B
                store_operator_reverse.io.push:=true.B
                store_reverse.io.pop:=true.B
                store_operator_reverse.io.dataIn:=store_reverse.io.dataOut
            }
        }.elsewhen(store_reverse.io.topdata===5014.U && store_operator_reverse.io.topdata=/=5013.U && neg_flag===0.U && right_bracket_flag===0.U){
            store_operator_reverse.io.en:=true.B
            stream_result.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=store_operator_reverse.io.dataOut
        }.elsewhen(store_reverse.io.topdata===5014.U && store_operator_reverse.io.topdata===5013.U && neg_flag===0.U && right_bracket_flag===0.U){
            store_operator_reverse.io.en:=true.B
            store_reverse.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            store_reverse.io.pop:=true.B
        }.elsewhen(store_reverse.io.topdata<10.U  && neg_flag===1.U && right_bracket_flag===0.U){
            store_reverse.io.en:=true.B
            store_reverse.io.pop:=true.B
            Num.io.key_in:=store_reverse.io.dataOut
        }.elsewhen( store_reverse.io.topdata===5011.U && neg_flag===1.U && right_bracket_flag===0.U){
            store_reverse.io.en:=true.B
            store_reverse.io.pop:=true.B
            Num.io.key_in:=store_reverse.io.dataOut-5000.U
        }.elsewhen( store_reverse.io.topdata===5014.U && neg_flag===1.U && right_bracket_flag===0.U){
            right_bracket_flag:=1.U
            store_reverse.io.en:=true.B
            store_reverse.io.pop:=true.B
            Num.io.key_in:=store_reverse.io.dataOut-5000.U
        }.elsewhen(right_bracket_flag===1.U && !Num.io.value.valid){
            Num.io.key_in:=15.U
        }.elsewhen(Num.io.value.valid){
            right_bracket_flag:=0.U
            neg_flag:=0.U
            stream_result.io.en:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=Num.io.value.bits
        }
    }

    when(state===sEqual){
        when(!store_operator_reverse.io.empty){
            store_operator_reverse.io.en:=true.B
            stream_result.io.en:=true.B
            store_operator_reverse.io.pop:=true.B
            stream_result.io.push:=true.B
            stream_result.io.dataIn:=store_operator_reverse.io.dataOut
        }
    }

    when(state===sReverse){
        when(!stream_result.io.empty){
            store_operator_reverse.io.en:=true.B
            stream_result.io.en:=true.B
            store_operator_reverse.io.push:=true.B
            stream_result.io.pop:=true.B
            store_operator_reverse.io.dataIn:=stream_result.io.dataOut
        }
    }

    when(state===sCal){
        when(!store_operator_reverse.io.empty && calculate_flag===0.U){
            when(store_operator_reverse.io.topdata=/=5010.U && store_operator_reverse.io.topdata=/=5011.U && store_operator_reverse.io.topdata=/=5012.U ){
                store_operator_reverse.io.en:=true.B
                stream_result.io.en:=true.B
                store_operator_reverse.io.pop:=true.B
                stream_result.io.push:=true.B
                stream_result.io.dataIn:=store_operator_reverse.io.dataOut
            }.elsewhen(store_operator_reverse.io.topdata===5010.U || store_operator_reverse.io.topdata===5011.U || store_operator_reverse.io.topdata===5012.U){
                store_operator_reverse.io.en:=true.B
                store_operator_reverse.io.pop:=true.B
                cal_sign:=store_operator_reverse.io.dataOut-5000.U
                calculate_flag:=1.U              
            }
        }.elsewhen(calculate_flag===1.U){
            stream_result.io.en:=true.B
            stream_result.io.pop:=true.B
            src2:=stream_result.io.dataOut
            calculate_flag:=2.U
        }.elsewhen(calculate_flag===2.U){
            stream_result.io.en:=true.B
            stream_result.io.pop:=true.B
            src1:=stream_result.io.dataOut
            calculate_flag:=3.U
        }.elsewhen(calculate_flag===3.U){
            when(cal_sign===10.U){
                stream_result.io.en:=true.B
                stream_result.io.push:=true.B
                stream_result.io.dataIn:=src1+src2
            }.elsewhen(cal_sign===11.U){
                stream_result.io.en:=true.B
                stream_result.io.push:=true.B
                stream_result.io.dataIn:=src1-src2
            }.elsewhen(cal_sign===12.U){
                stream_result.io.en:=true.B
                stream_result.io.push:=true.B
                stream_result.io.dataIn:=src1*src2
            }
            src1:=0.U
            src2:=0.U
            cal_sign:=0.U
            calculate_flag:=0.U
        }
        
    }

    when(state===sOut){
        stream_result.io.en:=true.B
        stream_result.io.pop:=true.B
        io.value.bits := stream_result.io.dataOut
        io.value.valid := true.B
    }

    
}