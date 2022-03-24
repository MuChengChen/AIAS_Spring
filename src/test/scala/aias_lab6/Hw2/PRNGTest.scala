// package aias_lab6.Hw2

// import chisel3._
// import chisel3.util._
// import chisel3.iotesters.{Driver,PeekPokeTester}

// class PRNGTest(dut:PRNG) extends PeekPokeTester(dut) {
    
//     implicit def bigint2boolean(b:BigInt):Boolean = if (b>0) true else false
//     poke(dut.io.gen,true)
//     step(1)
//     poke(dut.io.gen,false)
//     while(!peek(dut.io.ready)){step(1)}
//     step(1)

//     val out = Seq.range(0,4).map{x => peek(dut.io.puzzle(x))}
    
//     var check = out.map{x=>(1<<(x.toInt))}.reduce(_+_)
//     var count = 0

//     for(i <- 0 until 10){
//         count = count + (check & 0x1)
//         check = check >> 1
//     }

//     println("count = "+count.toString)
    

//     if(check != 4){
//         println("You pass the Hw6-2-1, Well done!!")
//     }else{
//         println("Oh no!! There must be something wrong in your PRNG...")
//     }
// }

// object PRNGTest extends App{
//     Driver.execute(args,()=>new PRNG(1)){
//         dut:PRNG => new PRNGTest(dut)
//     }
// }