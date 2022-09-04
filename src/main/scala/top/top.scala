//In playlab-chisel-template/src/main/scala/top/top.scala (自行建立)
//最上層自訂的package name
package top

//import src code component 所在的package，因為你將在第13行引用它
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
