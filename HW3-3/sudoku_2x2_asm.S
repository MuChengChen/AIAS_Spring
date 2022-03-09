# sudoku_2x2_asm.S
   
    .text                           # code section 
    .global sudoku_2x2_asm          # declare the asm function as a global function
    .type sudoku_2x2_asm, @function # define sum_asm as a function 
sudoku_2x2_asm:
    	li	    t0,0
	li	    t1,1
before_end:
	beq	    t0,t1,ending
	addi	    sp,sp,-4
	sw	    ra,0(sp)
sudoku:
    	li	    a1,0 #index=0
	li	    a2,0 #stack counter
	j	    solve
	
solve:
    ## add your assembly code here
    	li	    t0,15 #for index>=16
    	bgt  	    a1,t0,return1 #if index>=16,jump to return1
    #li   	t0,0 #for *(test_asm_data+index)>0
    	add  	    t1,a0,a1 #test_asm_data+index
	lb	    t2,0(t1) #*(test_asm_data+index)
   	bgt  	    t2,x0,return2 #if *(test_asm_data+index)>0,jump to return2
	li	    t0,1 #for(i=1;;)
	j	    solve_loop1
solve_loop1:
	li	    t3,4 #for(;i<=4;)
	#lb      t2,0(t1) #*(test_asm_data+index)
	addi	    sp,sp,-9
	addi	    a2,a2,9
	sw	    a1,5(sp)
	sw	    t1,1(sp)
    	j	    loop1 #jump to loop1,for(i=1;i<=4;i++)
return2:
    	addi 	    a1,a1,1 #index add 1
    	j	    solve #jump to solve
loop1:
	sb	    t0,0(sp)
	sb	    t0,0(t1) #*(test_asm_data+index)=i
	rem         t4,a1,t3 #for(i=(index%4);;)
	li	    t5,15 #for(;i<=15;)
	jal	    loop2 #jump to loop2(check column),for(i=(index%4);i<=15;i+=4)
	div	    t4,a1,t3 #index/4
	mul	    t4,t4,t3 #for(i=4*(index/4);;)
	addi	    t5,t4,3 #for(;i<=4*(index/4)+3;)
	jal	    loop3 #jump to loop3(check row),for(i=4*(index/4);i<=4*(index/4)+3;i++)
	jal	    check3
	addi	    a1,a1,1 #index+1
	j	    solve #solve(test_asm_data,index+1)
loop2:
	beq	    t4,a1,loop2_1 #if(i==index),jump to loop2_1
	add	    t6,a0,t4 #test_asm_data+i
	lb	    t6,0(t6) #*(test_asm_data+i)
	beq	    t6,t0,loop2_return #if *(test_asm_data+i)==*(test_asm_data+index),jump to loop2_return
	addi	    t4,t4,4 #for(;;i+=4)
	ble	    t4,t5,loop2 #for(;i<=15;),loop again
	jr	    ra

loop2_1:
	addi        t4,t4,4 #for(;;i+=4)
	ble         t4,t5,loop2 #for(;i<=15;),loop again
	jr	    ra #if i>15,back to loop1,for(i=1;i<=4;i++)
loop2_return:
	addi	    t0,t0,1 #for(;;i++)
	bgt	    t0,t3,pre_cannot_set #if 1~4 cannot set the element,jump to cannot_set
	j	    loop1 #jump to loop1,for(i=1;i<=4;i++)
loop3:
	beq	    t4,a1,loop3_1 #if(i==index),jump to loop3_1
	add	    t6,a0,t4 #test_asm_data+i
	lb	    t6,0(t6) #*(test_asm_data+i)
	beq	    t0,t6,loop3_return #if *(test_asm_data+i)==*(test_asm_data+index),jump to loop3_return
	addi	    t4,t4,1 #for(;;i++)
	ble	    t4,t5,loop3 #for(;i<=4*(index/4)+3;),loop again
	jr	    ra
loop3_1:
	addi        t4,t4,1 #for(;;i++)
	ble         t4,t5,loop3 #for(;i<=4*(index/4)+3;),loop again
	jr	    ra #if i>4*(index/4)+3,back to loop1,for(i=1;i<=4;i++)
loop3_return:
	addi	    t0,t0,1 #for(;;i++)
	bgt         t0,t3,pre_cannot_set #if 1~4 cannot set the element,jump to cannot_set
	j	    loop1 #jump to loop1,for(i=1;i<=4;i++)
check3:
	li	    t4,8 #(index%8)


	#li	    t5,0 #(index%8==0)
	rem	    t6,a1,t4 #(index%8)
	beq	    t6,x0,ch_if1 #if index%8==0,jump to ch_if1

	li          t5,2 #(index%8==2)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if1 #if index%8==2,jump to ch_if1


	li          t5,1 #(index%8==1)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if2 #if index%8==1,jump to ch_if2

	li          t5,3 #(index%8==3)
	rem	    t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if2 #if index%8==3,jump to ch_if2


	li          t5,4 #(index%8==4)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if3 #if index%8==4,jump to ch_if3

	li          t5,6 #(index%8==6)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if3 #if index%8==6,jump to ch_if3

	
	li          t5,5 #(index%8==5)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if4 #if index%8==5,jump to ch_if4

	li          t5,7 #(index%8==7)
	rem         t6,a1,t4 #(index%8)
	beq         t6,t5,ch_if4 #if index%8==7,jump to ch_if4
	
ch_if1:
	addi        t6,t1,5 #(test_asm_data+index+5)
	lb          t6,0(t6) #*(test_asm_data+index+5)
	beq         t0,t6,check_return #if *(test_asm_data+index)==*(test_asm_data+index+5),jump to check_return
	jr	    ra
ch_if2:
	addi        t6,t1,3 #(test_asm_data+index+3)
	lb          t6,0(t6) #*(test_asm_data+index+3)
	beq         t0,t6,check_return #if *(test_asm_data+index)==*(test_asm_data+index+3),jump to check_return
	jr	    ra
ch_if3:
	addi        t6,t1,-3 #(test_asm_data+index-3)
	lb          t6,0(t6) #*(test_asm_data+index-3)
	beq         t0,t6,check_return #if *(test_asm_data+index)==*(test_asm_data+index+5),jump to check_return
	jr	    ra
ch_if4:
	addi        t6,t1,-5 #(test_asm_data+index-5)
	lb          t6,0(t6) #*(test_asm_data+index-5)
	beq         t0,t6,check_return #if *(test_asm_data+index)==*(test_asm_data+index+5),jump to check_return
	jr	    ra
check_return:
	addi	    t0,t0,1 #for(;;i++)
	bgt         t0,t3,pre_cannot_set #if 1~4 cannot set the element,jump to cannot_set
	j	    loop1 #jump to loop1,for(i=1;i<=4;i++)
pre_cannot_set:
    	sb          x0,0(t1)
    	j           cannot_set
cannot_set:
	addi	    sp,sp,9
	addi	    a2,a2,-9
	lw	    a1,5(sp) #load a1 from previous stack
	lw	    t1,1(sp) #load t1 from previous stack
	lb	    t0,0(sp) #load t0 from previous stack
	addi	    sp,sp,9
	addi	    a2,a2,-9
	beq         t0,t3,cannot_set_reset #if t0==4,skip this stack
	addi        t0,t0,1
	j	    solve_loop1 #jump to solve_loop1
cannot_set_reset:
	addi	    sp,sp,-9
	addi	    a2,a2,9
	j	    cannot_set
return1:
	add	    sp,sp,a2
	lw	    ra,0(sp)
	addi	    sp,sp,4
    	li	    t0,88
	li	    t1,88
	jr	    ra
ending:
	jr	    ra
    .size sudoku_2x2_asm, .-sudoku_2x2_asm
