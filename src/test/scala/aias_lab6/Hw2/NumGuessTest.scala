// package aias_lab6.Hw2

// import chisel3._
// import chisel3.util._
// import chisel3.testers.{TesterDriver,BasicTester}
// import chisel3.iotesters.{Driver,PeekPokeTester}

// class NumGuessTest(dut:NumGuess) extends PeekPokeTester(dut) {
    
//     implicit def bigint2boolean(b:BigInt):Boolean = if (b>0) true else false
    
//     // def guess_Generator (guess:Seq[Int]):UInt={
//     //     var guess_int = 0
//     //     for (i <- guess){guess_int = (guess_int << 4) + i}
//     //     guess_int.U
//     // }

//     // val m = List(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)

//     // val guess = List(1,2,3,4)

//     // def permutation(lst: List[Int]): List[List[Int]] = lst match {
//     //     case List(ele) => List(List(ele))
//     //     case list => for {
//     //         i <- List.range(0, list.length)
//     //         p <- permutation(list.slice(0, i) ++ list.slice(i + 1, list.length))
//     //     } yield list(i) :: p
//     // }

//     // val guess_list = permutation(guess)
//     // var cnt = 0


//     // for(i <- 0 until 1000){
//     //     var guess_int = guess_list(cnt).reduceLeft(4*_+_)

//     //     poke(dut.io.guess, guess_int)
//     //     while(!peek(dut.io.valid)){step(1)}
        
//     //     println("Input : " + guess_list(cnt))
//     //     println("A = "+peek(dut.io.A))
//     //     println("B = "+peek(dut.io.B))

//     //     if(peek(dut.io.A) != 4){
//     //         cnt = cnt + 1
//     //     }

//     //     step(1)
//     // }

//     while(!peek(dut.io.valid)){step(1)}
    
    
// }

// object NumGuessTest extends App{
//     Driver.execute(args,()=>new NumGuess){
//         dut:NumGuess => new NumGuessTest(dut)
//     }
// }

// // class NumGuessTest extends BasicTester{
// //     val dut = Module(new NumGuess())
// //     val ready = Wire(Bool())
// //     val valid = Wire(Bool())
// //     val A = Wire(UInt(2.W))
// //     val B = Wire(UInt(2.W))

// //     ready := dut.io.ready
// //     valid := dut.io.valid
// //     A := dut.io.A
// //     B := dut.io.B
    
// //     val m = Seq(1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)

// //     def guess_Generator (guess:Seq[Int]):UInt={
// //         var guess_int = 0
// //         for (i <- guess){guess_int = (guess_int << 4) + i}
// //         guess_int.U
// //     }

// //     dut.io.guess := guess_Generator(Seq(1,2,3,4))

// //     when(dut.io.valid){
// //         when(A=/=0.U){
// //             println("Happy")
// //         }.otherwise{
// //             println("Holloween")
// //         }
// //         stop
// //     }
    
// // }

// // object NumGuessTest extends App{
// //     TesterDriver.execute(()=>new NumGuessTest)
// // }