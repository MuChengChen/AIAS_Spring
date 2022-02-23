// In ./src/main/scala/Happy/Mux2.scala
package Happy  //declare Module所屬的package，最好和存放的資料夾同名

import chisel3._
import chisel3.util._
import chisel3.stage.ChiselStage

//撰寫Module，記得要extends Moudle
class Mux2 extends Module {
  //IO port的宣告，格式: val io = IO(new Bundle{...})
  val io = IO(new Bundle {
    //在Bundle內宣告IO port，格式: val 變數名稱 = Input/Output(dtype(長度))
    val sel = Input(UInt(1.W))
    val in0 = Input(UInt(1.W))
    val in1 = Input(UInt(1.W))
    val out = Output(UInt(1.W))
  })
  //電路的行為描述
  io.out := (io.sel & io.in1) | (~io.sel & io.in0)
}