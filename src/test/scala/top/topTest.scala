package top

import Happy._

import chisel3.iotesters.Driver

object topTest extends App{
  Driver.execute(args,()=>new Mux2){
    c:Mux2 => new Mux2Test(c)
  }
}