## fibonacci.S
## put input n in register x10 (a0)  
## put output fibonacci(n) in register x11 (a1)
## use Venus to test correctness

.text
main:
## write assembly code here.
## call fibonacci function and get return value.
    li		a0,16
    jal	        fibonacci ##jump to fibonacci function
    j		exit
fibonacci:
## fibonacci function
    li		t0,1
    ble	        a0,t0,return ##if a0<=1,jump to return
    addi	sp,sp,-12
    sw	        ra,8(sp)
    sw	        a0,4(sp)
    addi	a0,a0,-1 ##a0-1
    jal		fibonacci ##jump to fibonacci(recursive)
    sw		a0,0(sp) ##save a0
    lw		a0,4(sp) ##load the previous a0
    addi	a0,a0,-2 ##a0-2
    jal		fibonacci ##jump to fibonacci
    lw		t0,0(sp) ##load previous value of a0
    add		a0,a0,t0 
    lw		ra,8(sp)
    addi	sp,sp,12
    add		a1,a0,x0
    jr		ra
return:
    add		a1,a0,x0
    jr		ra
exit:
    li		a0,1
    ecall
