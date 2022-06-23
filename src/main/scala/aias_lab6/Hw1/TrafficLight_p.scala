package aias_lab6.Hw1

import chisel3._
import chisel3.util._

class TrafficLight_p(Ytime:Int, Gtime:Int, Ptime:Int) extends Module{
  val io = IO(new Bundle{
    val P_button = Input(Bool())
    val H_traffic = Output(UInt(2.W))
    val V_traffic = Output(UInt(2.W))
    val P_traffic = Output(UInt(2.W))
    val timer     = Output(UInt(5.W)) 
    val display   = Output(UInt(7.W)) 
  })

  //please implement your code below...
  io.H_traffic := 0.U
  io.V_traffic := 0.U
  io.P_traffic := 0.U
  io.timer := 0.U

  val Off = 0.U
  val Red = 1.U
  val Yellow = 2.U
  val Green = 3.U
  
  val sIdle::sHGVR::sHYVR::sHRVG::sHRVY::sPG::Nil=Enum(6)
  
  val state=RegInit(sIdle)

  val state_remember=RegInit(0.U(4.W))

  //val cntMode=WireDefault(0.U(2.W))
  val cntReg=RegInit(0.U(4.W))
  val cntDone=Wire(Bool())
  
  cntDone:=cntReg===0.U

  when(!cntDone){
    /*when(cntMode===3.U){
      cntReg:=(Ptime-1).U
    }.elsewhen(cntMode===1.U){
      cntReg:=(Ytime-1).U
    }.elsewhen(cntMode===2.U){
      cntReg:=(Gtime-1).U
    }
  }.otherwise{*/
      cntReg:=cntReg-1.U
  }
  
  switch(state){
    is(sIdle){
      state:=sHGVR
      cntReg:=(Gtime-1).U
    }
    is(sHGVR){
      when(cntDone){
        state:=sHYVR
        cntReg:=(Ytime-1).U
      }
    }
    is(sHYVR){
      when(cntDone){
        state:=sHRVG
        cntReg:=(Gtime-1).U
      }
    }
    is(sHRVG){
      when(cntDone){
        state:=sHRVY
        cntReg:=(Ytime-1).U
      }
    }
    is(sHRVY){
      when(cntDone){
        state:=sPG
        cntReg:=(Ptime-1).U
      }
    }
    is(sPG){
      when(cntDone){
        when(state_remember=/=0.U){
          switch(state_remember){
              is(sHGVR){
                state:=sHGVR
                cntReg:=(Gtime-1).U
              }
              is(sHYVR){
                state:=sHYVR
                cntReg:=(Ytime-1).U
              }
              is(sHRVG){
                state:=sHRVG
                cntReg:=(Gtime-1).U
              }
              is(sHRVY){
                state:=sHRVY
                cntReg:=(Ytime-1).U
              }
          }
          state_remember:=0.U
        }.otherwise{
          state:=sHGVR
          cntReg:=(Gtime-1).U
        }
      }
    }
  }

  //cntMode:=0.U
  io.H_traffic := Off
  io.V_traffic := Off
  io.P_traffic := Off

  switch(state){
    is(sHGVR){
      //cntMode := 2.U
      io.H_traffic := Green
      io.V_traffic := Red
      io.P_traffic := Red
    }
    is(sHYVR){
      //cntMode := 1.U
      io.H_traffic := Yellow
      io.V_traffic := Red
      io.P_traffic := Red
    }
    is(sHRVG){
      //cntMode := 2.U
      io.H_traffic := Red
      io.V_traffic := Green
      io.P_traffic := Red
    }
    is(sHRVY){
      //cntMode := 1.U
      io.H_traffic := Red
      io.V_traffic := Yellow
      io.P_traffic := Red
    }
    is(sPG){
      //cntMode := 3.U
      io.H_traffic := Red
      io.V_traffic := Red
      io.P_traffic := Green
    }
  }

  when(io.P_button && state=/=sPG){
    state_remember:=state
    state:=sPG
    cntReg:=(Ptime-1).U
  }

  io.timer := cntReg
  val ss = Module(new SevenSeg())
  ss.io.num := cntReg
  io.display := ss.io.display

}