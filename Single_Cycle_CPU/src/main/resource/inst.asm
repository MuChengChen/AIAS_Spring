addi t0, zero, 0
lui x06, 0x00000008
addi x06, x06, 0x0000003c
lw t1, 0(t1)
addi t1, t1, -1
add s10, t1, zero
addi a5, zero, -1
lui x18, 0x00000008
addi x18, x18, 0x00000040
lw s2, 0(s2)
lui x08, 0x00000008
addi x08, x08, 0x00000010
jal ra, binary_search
blt a5, x0, fail
j x0, exit
add a2, t0, t1
srli a2, a2, 1
blt s10, a2, fail
blt a2, x0, fail
add t2, a2, zero
slli t2, t2, 2
add t2, t2, s0
lw t2, 0(t2)
beq t2, s2, find
beq t0, t1, fail
blt s2, t2, less
addi t0, a2, 1
j x0, binary_search
addi t1, a2, -1
j x0, binary_search
jalr x0, x1, x0
addi a5, zero, -1
lui x11, 0x00000008
addi x11, x11, 0x00000008
lui x10, 0x00000000
addi x10, x10, 0x00000004
addi a1, s2
lui x10, 0x00000000
addi x10, x10, 0x00000001
lui x11, 0x00000008
addi x11, x11, 0x0000000c
lui x10, 0x00000000
addi x10, x10, 0x00000004
j x0, exit
add a5, a2, zero
lui x11, 0x00000008
addi x11, x11, 0x00000000
lui x10, 0x00000000
addi x10, x10, 0x00000004
addi a1, s2
lui x10, 0x00000000
addi x10, x10, 0x00000001
lui x11, 0x00000008
addi x11, x11, 0x00000004
lui x10, 0x00000000
addi x10, x10, 0x00000004
addi a1, a5
lui x10, 0x00000000
addi x10, x10, 0x00000001
j x0, exit
hcf