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
#addi x16, x0, 254
#add x16, x16, x16
#add x16, x16, x16
#add x16, x16, x16
#add x16, x16, x16
#add x16, x16, x16
#add x16, x16, x16
#add x16, x16, x16
#addi x16, x16, 85
#add x16, x16, x16

#sext.b x1, x16    
#sext.h x2, x16    
#bseti x3, x16, 31 
##bclri x4, x3, 31  
#binvi x5, x16, 31 
#bexti x6, x16, 15
#rori  x7, x16, 16 

addi x13, x0, -34
addi x14, x0, -33


max x15, x13, x14
minu x5, x13, x14
maxu x6, x13, x14
min x16, x13, x14

addi x2, x0, 0x1E4
addi x3, x0, 0x22D
bset x4, x3, x2

addi x7, x0, 0x1E2
bclr x8 x3, x7
binv x9, x3, x7

bext x10, x3, x2

ror x11, x3, x2
rol x12, x3, x2

addi x9 x0 0xff
addi x10 x0 1
addi x11 x0 -1
rev8 x3 x9
sh1add x5 x10 x0
sh2add x6 x10 x0
sh3add x7 x10 x0
orc_d x4 x11
zext_h x8 x11

hcf



