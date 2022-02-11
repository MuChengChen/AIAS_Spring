## Lab3-3 - example_1_sum.S

    .text                    # code section 
    .global sum_asm          # declar the sum_asm function as a  global function
    .type sum_asm, @function # define sum_asm as a function 
sum_asm:
prologue :
    li s0,1                  # s0 -> int i
    mv s1,a0                 # s1 -> int n
    mv s2,zero               # s2 -> int temp
loop_start :
    bgt s0,s1,loop_end
    add s2,s2,s0 
    addi s0,s0,1 
    j loop_start
loop_end :
    mv a0,s2

epilogue :
    jr ra

    .size sum_asm, .-sum_asm