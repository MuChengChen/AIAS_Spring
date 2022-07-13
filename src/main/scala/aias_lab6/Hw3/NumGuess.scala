package aias_lab6.Hw3

import chisel3._
import chisel3.util._

class NumGuess(seed:Int = 1) extends Module{
    require (seed > 0 , "Seed cannot be 0")
    
    val io  = IO(new Bundle{
        val gen = Input(Bool())
        val guess = Input(UInt(16.W))
        val puzzle = Output(Vec(4,UInt(4.W)))
        val ready  = Output(Bool())
        val g_valid  = Output(Bool())
        val A      = Output(UInt(3.W))
        val B      = Output(UInt(3.W))

        //don't care at Hw6-3-2 but should be considered at Bonus
        val s_valid = Input(Bool())
    })

    io.puzzle := VecInit(Seq.fill(4)(0.U(4.W)))
    io.ready  := false.B
    io.g_valid  := false.B
    io.A      := 0.U
    io.B      := 0.U

    val sNone::sGen::sTens::sSecond::sThird::sForth::sReady::sFirst_guess::sSecond_guess::sThird_guess::sForth_guess::sResult::sGuess_ready::Nil=Enum(13)
    val state=RegInit(sNone)

    
    val prepare_puzzle=RegInit(VecInit(Seq.fill(4)(0.U(4.W))))
    val g_A=RegInit(0.U(3.W))
    val g_B=RegInit(0.U(3.W))

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
            state:=sFirst_guess
        }
        is(sFirst_guess){
            state:=sSecond_guess
        }
        is(sSecond_guess){
            state:=sThird_guess
        }
        is(sThird_guess){
            state:=sForth_guess
        }
        is(sForth_guess){
            state:=sResult
        }
        is(sResult){
            state:=sGuess_ready
        }
        is(sGuess_ready){
            when(g_A===4.U){
                state:=sNone
                prepare_puzzle(0):=0.U
                prepare_puzzle(1):=0.U
                prepare_puzzle(2):=0.U
                prepare_puzzle(3):=0.U
            }.otherwise{
                state:=sFirst_guess
            }
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

        io.ready:=true.B
    }

    when(state===sFirst_guess){
        when(io.guess(3,0)===prepare_puzzle(0)){
            g_A:=g_A+1.U
        }.elsewhen(io.guess(3,0)===prepare_puzzle(1) || io.guess(3,0)===prepare_puzzle(2) || io.guess(3,0)===prepare_puzzle(3)){
            g_B:=g_B+1.U
        }
    }

    when(state===sSecond_guess){
        when(io.guess(7,4)===prepare_puzzle(1)){
            g_A:=g_A+1.U
        }.elsewhen(io.guess(7,4)===prepare_puzzle(0) || io.guess(7,4)===prepare_puzzle(2) || io.guess(7,4)===prepare_puzzle(3)){
            g_B:=g_B+1.U
        }
    }

    when(state===sThird_guess){
        when(io.guess(11,8)===prepare_puzzle(2)){
            g_A:=g_A+1.U
        }.elsewhen(io.guess(11,8)===prepare_puzzle(0) || io.guess(11,8)===prepare_puzzle(1) || io.guess(11,8)===prepare_puzzle(3)){
            g_B:=g_B+1.U
        }
    }

    when(state===sForth_guess){
        when(io.guess(15,12)===prepare_puzzle(3)){
            g_A:=g_A+1.U
        }.elsewhen(io.guess(15,12)===prepare_puzzle(0) || io.guess(15,12)===prepare_puzzle(1) || io.guess(15,12)===prepare_puzzle(2)){
            g_B:=g_B+1.U
        }
    }

    when(state===sResult){
        io.A:=g_A
        io.B:=g_B
        io.g_valid:=true.B
    }

    when(state===sGuess_ready){
        when(g_A=/=4.U){
           io.ready:=true.B  
        }.otherwise{
            io.ready:=false.B
        }
        io.A:=g_A
        g_A:=0.U
        g_B:=0.U
    }
    
}