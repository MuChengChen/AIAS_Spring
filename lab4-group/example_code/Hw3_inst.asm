#這個應該會被指令$ ./obj/emulator example_code/Hw3_inst.asm 轉換成inst.asm

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


/*---KAI----------*/
# initialize
addi x16, x0, 0xfe
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
add x16, x16, x16
addi x16, x16, 0x55
add x16, x16, x16  #x16 = 0xfeaa





sext.b x1, x16      #x16 = 0xfeaa---->x1=0xffffffaa
sext.h x2, x16      #x16 = 0xfeaa---->x2=0xfffffeaa
bseti x3, x16, 31   #x16 = 0xfeaa---->x3=0x8000feaa
bclri x4, x3, 31    #x3  = 0x8000feaa---->x4=0xfeaa
binvi x5, x16, 31   #x16 = 0xfeaa---->x5=0x8000feaa
bexti x6, x16, 31   #x16 = 0xfeaa---->x6=0
rori  x7, x23, 16   #x16 = 0xfeaa---->x7=0xfeaa0000
hcf
/*---KAI----------*/


