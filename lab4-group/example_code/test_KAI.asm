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
add x16, x16, x16 #x16 = 0xfeaa

sext.b x1, x16      #x16 = 0xfeaa---->x1=0xffffffaa
sext.h x2, x16      #x16 = 0xfeaa---->x2=0xfffffeaa
bseti x3, x16, 31   #x16 = 0xfeaa---->x3=0x8000feaa
bclri x4, x3, 31    #x3  = 0x8000feaa---->x4=0xfeaa
binvi x5, x16, 31   #x16 = 0xfeaa---->x5=0x8000feaa
bexti x6, x16, 15   #x16 = 0xfeaa---->x6=1
rori  x7, x16, 16   #x16 = 0xfeaa---->x7=0xfeaa0000
hcf