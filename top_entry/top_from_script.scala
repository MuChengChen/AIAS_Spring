package top

import Happy._

object Elaborate extends App {
  (
    new chisel3.stage.ChiselStage).emitVerilog(
      new Mux2(),
      Array("-td","generated/Mux2")
  )
}
