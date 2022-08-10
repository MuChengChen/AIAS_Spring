.data 
## input data size = 2x8x8 
input_data:
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7

.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7
.byte 0 1 2 3 4 5 6 7

## kernel size 2x3x3
kernel_data:
.byte 0 1 2 0 0 0 0 0
.byte 0 1 2 0 0 0 0 0
.byte 0 1 2 0 0 0 0 0

.byte 0 1 2 0 0 0 0 0
.byte 0 1 2 0 0 0 0 0
.byte 0 1 2 0 0 0 0 0

## output data size 1x6x6
output_data:
.byte 0 0 0 0 0 0
.byte 0 0 0 0 0 0
.byte 0 0 0 0 0 0
.byte 0 0 0 0 0 0
.byte 0 0 0 0 0 0
.byte 0 0 0 0 0 0

## buffer 1x1x8
buffer:
.byte 0 0 0 0 0 0 0 0

.text
main:
##
## Finish your homework here :))
## Make sure you use vector extension instruction
##
start:
li sp,0x10000

## s0 is base address of input_data
la s0,input_data

## s1 is base address of kernel_data
la s1,kernel_data

## s2 is base address of output_data
la s2,output_data

## s3 is INPUT_SIZE
li s3,8

## s4 is KERNEL_SIZE
li s4,3

## s5 is OUTPUT_SIZE
li s5,6

## s6 is channel
li s6,2

## s9 is buffer
la s9,buffer

## parameter initialize

## t0 is channel
li t0,0

## t1 is rows
li t1,0

## t2 is columns
li t2,0


## for(int c = 0; c < channel; ++c)
channel:
bge t0,s6,end
li t1,0
jal rows
addi t0,t0,1
j channel

## for (int i = 0; i < OUTPUT_SIZE; ++i)
rows:
bge t1,s5,return
addi sp,sp,-4
sw ra,0(sp)
li t2,0
jal columns
lw ra,0(sp)
addi sp,sp,4
addi t1,t1,1
j rows

## for (int j = 0; j < OUTPUT_SIZE; ++j)  
columns:
bge t2,s5,return
addi sp,sp,-4
sw ra,0(sp)
li t3,0
jal calculate
lw ra,0(sp)
addi sp,sp,4
addi t2,t2,1
j columns



calculate:
## input_data->(c * INPUT_SIZE * INPUT_SIZE) + (INPUT_SIZE * i ) + j ->(t0*s3*s3)+(s3*t1)+t2
mul a0,t0,s3
mul a0,a0,s3
mul a1,t1,s3
add a0,a0,a1
add a0,a0,t2

add a0,a0,s0
vle8_v v0,0(a0)
addi a0,a0,8
vle8_v v1,0(a0)
addi a0,a0,8
vle8_v v2,0(a0)

## kernel_data->(c * KERNEL_SIZE * KERNEL_SIZE)  ->(t0*s4*s4)
mul a1,t0,s4
mul a1,a1,s4

add a1,a1,s1
vle8_v v3,0(a1)
addi a1,a1,3
vle8_v v4,0(a1)
addi a1,a1,3
vle8_v v5,0(a1)

## vector arithmetic
vmul_vv v0,v0,v3
vmul_vv v1,v1,v4
vmul_vv v2,v2,v5

vadd_vv v0,v0,v1
vadd_vv v0,v0,v2

## store in buffer and accumulate
vse8_v v0,0(s9)
lb a0,0(s9)
lb a1,1(s9)
add a0,a0,a1
lb a1,2(s9)
add a0,a0,a1


## output_data->(i * OUTPUT_SIZE) + j ->(t1 * s5) + t2
mul a2,t1,s5
add a2,a2,t2

add a2,a2,s2
lb a3,0(a2)

add a3,a3,a0
sb a3,0(a2)
ret

return:
ret

end:
vle8_v v20 0(s2)
addi s2,s2,6
vle8_v v21 0(s2)
addi s2,s2,6
vle8_v v22 0(s2)
addi s2,s2,6
vle8_v v23 0(s2)
addi s2,s2,6
vle8_v v24 0(s2)
addi s2,s2,6
vle8_v v25 0(s2)
hcf