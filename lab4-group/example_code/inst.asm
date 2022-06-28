addi x13, x0, -34
addi x14, x0, -33
max x15, x13, x14
minu x5, x13, x14
maxu x6, x13, x14
min x16, x13, x14
addi x2, x0, 0x1e4
addi x3, x0, 0x22d
bset x4, x3, x2
addi x7, x0, 0x1e2
bclr x8, x3, x7
binv x9, x3, x7
bext x10, x3, x2
ror x11, x3, x2
rol x12, x3, x2
addi x9, x0, 0xff
addi x10, x0, 1
addi x11, x0, -1
rev8 x3, x9
sh1add x5, x10, x0
sh2add x6, x10, x0
sh3add x7, x10, x0
orc_d x4, x11
zext_h x8, x11
hcf