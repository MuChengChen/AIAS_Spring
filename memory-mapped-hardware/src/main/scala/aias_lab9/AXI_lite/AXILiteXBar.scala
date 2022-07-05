package aias_lab9.AXILite

import chisel3._
import chisel3.util._

class AXILiteXBar(
    val nMasters: Int,
    val mSlaves: Int,
    val addrWidth: Int,
    val dataWidth: Int,
    val addrMap: List[(UInt, UInt)]
) extends Module {
  val io = IO(new Bundle {
    val masters = Flipped(Vec(nMasters, new AXILiteMasterIF(addrWidth, dataWidth)))
    val slaves  = Flipped(Vec(mSlaves, new AXILiteSlaveIF(addrWidth, dataWidth)))
  })

  // * read channels
  val readBuses = List.fill(nMasters) {
    Module(new AXIReadBus(mSlaves, addrWidth, dataWidth, addrMap))
  }
  val readMuxes = List.fill(mSlaves) {
    Module(new AXISlaveReadMux(nMasters, addrWidth, dataWidth))
  }

  // * write channels
  val writeBuses = List.fill(nMasters) {
    Module(new AXIWriteBus(mSlaves, addrWidth, dataWidth, addrMap))
  }

  val writeMuxes = List.fill(mSlaves) {
    Module(new AXISlaveWriteMux(nMasters, addrWidth, dataWidth))
  }

  // wiring
  for (i <- 0 until nMasters) {
    readBuses(i).io.master.readAddr <> io.masters(i).readAddr
    io.masters(i).readData <> readBuses(i).io.master.readData
    writeBuses(i).io.master.writeAddr <> io.masters(i).writeAddr
    writeBuses(i).io.master.writeData <> io.masters(i).writeData
    io.masters(i).writeResp <> writeBuses(i).io.master.writeResp
  }

  // wiring
  for (i <- 0 until mSlaves) {
    io.slaves(i).readAddr <> readMuxes(i).io.out.readAddr
    readMuxes(i).io.out.readData <> io.slaves(i).readData
    io.slaves(i).writeAddr <> writeMuxes(i).io.out.writeAddr
    io.slaves(i).writeData <> writeMuxes(i).io.out.writeData
    writeMuxes(i).io.out.writeResp <> io.slaves(i).writeResp
  }

  // wiring
  for (m <- 0 until nMasters; s <- 0 until mSlaves) yield {
    readBuses(m).io.slave(s) <> readMuxes(s).io.ins(m)
  }

  // wiring
  for (m <- 0 until nMasters; s <- 0 until mSlaves) yield {
    writeBuses(m).io.slave(s) <> writeMuxes(s).io.ins(m)
  }
}
