.data
A:
.byte 0 1 2 3 4 5

B:
.byte 0 1 2 3 4 5

C:
.byte 0 0 0 0 0 0 0 0 0



.text
## A -> matrix size MxK (input)
## B -> matrix size KxN (input)
## C -> matrix size MxN (output result)

mat_mul_asm:
prologue:
addi sp,sp,-24
sw s0,0(sp)
sw s1,4(sp)
sw s2,8(sp)
sw s3,12(sp)
sw s4,16(sp)
sw s5,20(sp)
sw ra,24(sp)

## testing parameter//
## s0 -> base address of A
## s1 -> base address of B
## s2 -> base address of C
la s0,A
la s1,B
la s2,C

## s3 -> dimM
## s4 -> dimK
## s5 -> dimN
li s3,3
li s4,2
li s5,3

## parameter initialize
## t0 -> i
## t1 -> j
## t2 -> k
li t0,0
li t1,0
li t2,0

## dimM for loop
dimM:
bge t0,s3,epilogue
li t1,0
jal dimN
addi t0,t0,1
j dimM

## dimN for loop
dimN:
bge t1,s5,return
addi sp,sp,-4
sw ra,0(sp)
li t2,0
jal dimK
lw ra,0(sp)
addi sp,sp,4
addi t1,t1,1
j dimN

## dimK for loop
dimK:
bge t2,s4,return
addi sp,sp,-4
sw ra,0(sp)
jal mult
lw ra,0(sp)
addi sp,sp,4
addi t2,t2,1
j dimK

mult:
mul t3,t0,s4    ## i*dimK     ->(for A matrix)
add t3,t3,t2    ## i*dimK + k ->(get offset)
add t3,s0,t3    ## base address of A + offset
lb t3,0(t3)     ## get data

mul t4,t2,s5    ## k*dimN     ->(for B matrix)
add t4,t4,t1    ## k*dimN + j ->(get offset)
add t4,s1,t4    ## base address of B + offset
lb t4,0(t4)     ## get data

mul t5,t3,t4    ## A[i][k] * B[k][j]

mul t6,t0,s5    ## i*dimN     ->(for C matrix)
add t6,t6,t1    ## i*dimN + j ->(get offset)
add t6,s2,t6    ## base address of C + offset
lb t3,0(t6)     ## original data in C + offset
add t5,t5,t3    ## C[i][j] + A[i][k] * B[k][j]
sb t5,0(t6)     ## store data
ret

return:
ret

epilogue:
lw s0,0(sp)
lw s1,4(sp)
lw s2,8(sp)
sw s3,12(sp)
sw s4,16(sp)
sw s5,20(sp)
lw ra,24(sp)
addi sp,sp,24
hcf              ## Terminate