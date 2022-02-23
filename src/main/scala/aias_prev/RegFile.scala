package aias_prev
import chisel3._


class RegFileIO extends Bundle {
  val raddr1 = Input(UInt(5.W))
  val raddr2 = Input(UInt(5.W))
  val rdata1 = Output(UInt(32.W))
  val rdata2 = Output(UInt(32.W))
  
  val wen    = Input(Bool())
  val waddr  = Input(UInt(5.W))
  val wdata  = Input(UInt(32.W))
}

class RegFile extends Module {
  val io = IO(new RegFileIO)
  val regs = RegInit(VecInit(Seq.fill(32)(0.U(32.W))))

  //val regs = Mem(32, UInt(32.W)) //How about Vec?
  //val regs = RegInit(VecInit(Seq.fill(31)(0.U(32.W)) ++ Seq("h80000000".U(32.W))))
  
  //Wiring
  io.rdata1 := regs(io.raddr1)
  io.rdata2 := regs(io.raddr2)

  when(io.wen) {regs(io.waddr) := io.wdata}
  regs(0) := 0.U
  
  
  //printf : print during simulation
            //$t0~$s7
  /*
  for(i <- 8 until 24){ 
	printf("reg(%d) is %d\n",i.U,regs(i))
  }
  */
  
}