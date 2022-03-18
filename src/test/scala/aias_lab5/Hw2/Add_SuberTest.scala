package aias_lab5.Hw2
import chisel3.iotesters.{PeekPokeTester,Driver}
import scala.math.pow

class Add_SuberTest (as : Add_Suber) extends PeekPokeTester(as){

  def _signed(i: Int, digits: Int = 4) : Int ={
	if(i.toBinaryString.length()==digits){
	//   str = String.format("%" + 32 + "s", i.toBinaryString).replace(' ', '1')
	Integer.parseInt(i.toBinaryString,2) - pow(2,digits).toInt
	}else{
    //   str = String.format("%" + 32 + "s", i.toBinaryString).replace(' ', '0')
	Integer.parseInt(i.toBinaryString,2)
	}
  }

  var total = 0
  var num_correct = 0
  for(in1 <- -8 until 8){
    for(in2 <- -8 until 8){
	  for(op <- 0 to 1){
	    poke(as.io.in_1,in1)
		poke(as.io.in_2,in2)
		poke(as.io.op,op)
		val answer = if(op==0){in1+in2}else{in1-in2} 
		val output = _signed(peek(as.io.out).toInt)
		
		if(answer < -8 || answer > 7){
          expect(as.io.o_f,1)
		}else{
		  //dtype of peek() is BigInt
          if(answer!=output){
			  println("error!! output is :"+output+"the answer should be : "+answer)
		  }
		}
        step(1)
	  }
	}
  }
  println("Add_Suber test completed!!!")
}

//>>>test:runMain aias_lab1.FAtester -td generated/ -tbn verilator
object Add_SuberTest extends App{
  Driver.execute(args,() => new Add_Suber()){
	c => new Add_SuberTest(c)
  }
}
