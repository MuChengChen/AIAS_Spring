package Hello

import org.scalatest.{FlatSpec, Matchers}

class HelloMsgTest extends FlatSpec with Matchers {
  "HelloMsg" should "say Hello to the user" in {
    assert(HelloMsg.msg == "Hello, Welcome to playlab chisel template!!!")
	println(HelloMsg.msg)
  }
}