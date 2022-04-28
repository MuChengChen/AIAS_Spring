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
rori x7, x16, 16
hcf