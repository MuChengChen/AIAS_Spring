package top

import aias_prev._

object Elaborate extends App {
  (
    new chisel3.stage.ChiselStage).emitVerilog(
      new Memory(),
      Array("-td","generated/Memory")
  )
}
