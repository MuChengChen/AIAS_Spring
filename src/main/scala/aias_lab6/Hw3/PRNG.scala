package aias_lab6.Hw3

import chisel3._
import chisel3.util._
class PRNG(seed:Int) extends Module{
    val io = IO(new Bundle{
        val gen = Input(Bool())
        val puzzle = Output(Vec(4,UInt(4.W)))
        val ready = Output(Bool())
    })
    val sNone::sGen::sTens::sSecond::sThird::sForth::sReady::Nil=Enum(7)
    val state=RegInit(sNone)

    
    val prepare_puzzle=RegInit(VecInit(Seq.fill(4)(0.U(4.W))))
    io.puzzle :=VecInit(Seq.fill(4)(0.U(4.W)))
    io.ready:=false.B

   

    val lfsr=RegInit(UInt(16.W),seed.asUInt)
    
    val bit=RegInit(0.U(16.W))

    bit:=((lfsr)^((lfsr)>>2.U)^((lfsr)>>3.U)^((lfsr)>>5.U))<<15
    lfsr:=bit|((lfsr)>>1.U)

    switch(state){
        is(sNone){
            when(io.gen){
                state:=sGen
            }
        }
        is(sGen){
            when(prepare_puzzle(0)=/=0.U || prepare_puzzle(1)=/=0.U || prepare_puzzle(2)=/=0.U || prepare_puzzle(3)=/=0.U){
                state:=sTens
            }
        }
        is(sTens){
            when(prepare_puzzle(0)<10.U && prepare_puzzle(1)<10.U && prepare_puzzle(2)<10.U && prepare_puzzle(3)<10.U){
                state:=sSecond
            }
        }
        is(sSecond){
            state:=sThird
        }
        is(sThird){
            when(prepare_puzzle(2)=/=prepare_puzzle(0) && prepare_puzzle(2)=/=prepare_puzzle(1) ){
                state:=sForth
            }
        }
        is(sForth){
            when(prepare_puzzle(3)=/=prepare_puzzle(0) && prepare_puzzle(3)=/=prepare_puzzle(1) && prepare_puzzle(3)=/=prepare_puzzle(2)){
                state:=sReady
            }
        }
        is(sReady){
            state:=sNone
        }
    }

    when(state===sGen){
        
        
        
        prepare_puzzle(0):=lfsr(3,0)
        prepare_puzzle(1):=lfsr(7,4)
        prepare_puzzle(2):=lfsr(11,8)
        prepare_puzzle(3):=lfsr(15,12)

        
    } 

    when(state===sTens){
        for(i<-0 to 3){
            when(prepare_puzzle(i)>=10.U){
                switch(prepare_puzzle(i)){
                    is(10.U){
                        prepare_puzzle(i):=0.U
                    }
                    is(11.U){
                        prepare_puzzle(i):=1.U
                    }
                    is(12.U){
                        prepare_puzzle(i):=2.U
                    }
                    is(13.U){
                        prepare_puzzle(i):=3.U
                    }
                    is(14.U){
                        prepare_puzzle(i):=4.U
                    }
                    is(15.U){
                        prepare_puzzle(i):=5.U
                    }
                }
            }
        }
    }

    when(state===sSecond){
        when(prepare_puzzle(1)===prepare_puzzle(0)){
            when(prepare_puzzle(0)=/=9.U){
               prepare_puzzle(1):=prepare_puzzle(0)+1.U 
            }.otherwise{
               prepare_puzzle(1):=0.U 
            }
            
        }
    }

    when(state===sThird){
        when(prepare_puzzle(2)===prepare_puzzle(0) ){
            when(prepare_puzzle(0)=/=9.U){
               prepare_puzzle(2):=prepare_puzzle(0)+1.U 
            }.otherwise{
               prepare_puzzle(2):=0.U 
            }
            
        }.elsewhen(prepare_puzzle(2)===prepare_puzzle(1)){
            when(prepare_puzzle(1)=/=9.U){
               prepare_puzzle(2):=prepare_puzzle(1)+1.U 
            }.otherwise{
               prepare_puzzle(2):=0.U 
            }
        }
    }

    when(state===sForth){
        when(prepare_puzzle(3)===prepare_puzzle(0) ){
            when(prepare_puzzle(0)=/=9.U){
               prepare_puzzle(3):=prepare_puzzle(0)+1.U 
            }.otherwise{
               prepare_puzzle(3):=0.U 
            }
            
        }.elsewhen(prepare_puzzle(3)===prepare_puzzle(1)){
            when(prepare_puzzle(1)=/=9.U){
               prepare_puzzle(3):=prepare_puzzle(1)+1.U 
            }.otherwise{
               prepare_puzzle(3):=0.U 
            }
            
        }.elsewhen(prepare_puzzle(3)===prepare_puzzle(2)){
            when(prepare_puzzle(2)=/=9.U){
               prepare_puzzle(3):=prepare_puzzle(2)+1.U 
            }.otherwise{
               prepare_puzzle(3):=0.U 
            }
        
        }
    }

    when(state===sReady){
        io.puzzle(0):=prepare_puzzle(0)
        io.puzzle(1):=prepare_puzzle(1)
        io.puzzle(2):=prepare_puzzle(2)
        io.puzzle(3):=prepare_puzzle(3)

        prepare_puzzle(0):=0.U 
        prepare_puzzle(1):=0.U 
        prepare_puzzle(2):=0.U 
        prepare_puzzle(3):=0.U

        io.ready:=true.B
    }

    
    
    

}
