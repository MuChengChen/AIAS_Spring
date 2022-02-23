//In Happy/Mux2Top.scala
//最上層自訂的package name
package top

//import component 所在的package
import Happy._

//利用chisel3.stage.ChiselStage object 定義指定的module 的入口
//Array 可以設定一些sbt 執行時的參數
object Mux2Top extends App {
  (
    new chisel3.stage.ChiselStage).emitVerilog(
      new Mux2(),
      Array("-td","generated/Mux2")
  )
}