#這個應該會被指令$ ./obj/emulator example_code/Hw3_inst.asm 轉換成inst.asm
#記得後面不能加註解喔，不能會有syntax error出現

# initialize
#addi x16, x0, 0xfec
#addi x17, x0, 0x472
#addi x18, x0, 0xab7
#addi x19, x0, 0xda2
#addi x20, x0, 0x561
#addi x21, x0, 0x146
#addi x22, x0, 0x531
#addi x23, x0, 0x456
#addi x24, x0, 0x11
#addi x25, x0, 0x98
#addi x26, x0, 0xa3
#addi x27, x0, 0x10
#addi x28, x0, 0x55
#addi x29, x0, 0xffe
#addi x30, x0, 0x4
#addi x31, x0, 0xff1
#
#clz x1, x30
#cpop x2, x23
#xnor x3, x16, x17
#min x4, x31, x25

#maxu x5, x19, x30
#sext.b x6, x21 
#bseti x7, x29, 0x0
#bclr x8, x31, x30
#binv x9, x16, x24
#bexti x10, x21, 0x2
#rol x11, x16, x30
#rori x12, x23, 0xc
#sh2add x13, x17, x18
#rev8 x14, x25
#orc.b x15, x25

#hcf

# initialize
addi x16, x0, 254
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
addi x16, x16, 85
add x16, x16, x16

sext.b x1, x16    
sext.h x2, x16    
bseti x3, x16, 31 
bclri x4, x3, 31  
binvi x5, x16, 31 
bexti x6, x16, 15
rori  x7, x16, 16 
hcf



