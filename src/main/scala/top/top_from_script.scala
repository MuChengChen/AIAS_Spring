package top

import aias_prev._

object Elaborate extends App {
  (
    new chisel3.stage.ChiselStage).emitVerilog(
      new RegFile(2),
      Array("-td","generated/RegFile")
  )
}
