//In ./src/test/scala/Happy/Mux2Test.scala

package Happy //盡量和Module同package，可以省去程式碼編寫路徑的麻煩。
import chisel3.iotesters.{PeekPokeTester,Driver}

class Mux2Test(c: Mux2) extends PeekPokeTester(c) {
  val i0 = 0
  val i1 = 1

  for (s <- 0 until 2) {
    //格式：poke(port,value)
    //注意到，雖然在Module內部，port的dtype是chisel的dtype(UInt、SInt、Bool...)
    //但在tester這裡，value用scala有的Int dtype(32 bits)即可
    poke(c.io.sel, s)
    poke(c.io.in1, i1)
    poke(c.io.in0, i0)
    step(1) //對Comb Circuit而言，可有可無

    //第一種測試方法
    //格式：expect(port,value)
    expect(c.io.out, if (s == 1) i1 else i0)

    //第二種測試方法
    //match-case是scala特有的語法
    //peek(port)會回傳output port得到的值，dtype為BigInt
    //要把它印出來可以這樣：println(peek(c.io.out).toString)
    s match {
        case 0 => if (peek(c.io.out)!=i0) println("Error!!!!") else println("pass!!")
        case 1 => if (peek(c.io.out)!=i1) println("Error!!!!") else println("pass!!")
    }
  }
}

object Mux2Test extends App{
  Driver.execute(args,()=>new Mux2){
    c:Mux2 => new Mux2Test(c)
  }
}