## Lab3-3 - example_2_sum.S

    .text                    # code section 
    .global sum_asm          # declar the sum_asm function as a  global function
    .type sum_asm, @function # define sum_asm as a function 
sum_asm:
prologue :
    addi sp,sp,-4
    sw   ra,0(sp)

funct_start :
    jal  formula

epilogue :
    lw   ra,0(sp)
    addi ra,ra,4
    jr   ra

formula :
    mv   s1,a0
    li   s2,1
    li   s3,2
    add  s2,s1,s2
    mul  s2,s1,s2
    div  s2,s2,s3
    mv   a0,s2
    jr   ra
    
    .size sum_asm, .-sum_asm