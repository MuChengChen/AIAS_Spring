# initialize
addi x16, x0, 0xfec
addi x17, x0, 0x472
addi x18, x0, 0xab7
addi x19, x0, 0xda2
addi x20, x0, 0x561
addi x21, x0, 0x146
addi x22, x0, 0x531
addi x23, x0, 0x456
addi x24, x0, 0x11
addi x25, x0, 0x98
addi x26, x0, 0xa3
addi x27, x0, 0x10
addi x28, x0, 0x55
addi x29, x0, 0xffe
addi x30, x0, 0x4
addi x31, x0, 0xff1

clz x1, x30
ctz x2, x30
cpop x3, x23
andn x4, x16, x17
orn x5, x16, x17
xnor x6, x16, x17
min x7, x31, x25
hcf
