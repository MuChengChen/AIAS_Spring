# initialize
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
