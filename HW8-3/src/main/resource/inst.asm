lui x02, 0x00000010
addi x02, x02, 0x00000000
lui x08, 0x00000008
addi x08, x08, 0x00000008
lui x09, 0x00000008
addi x09, x09, 0x00000088
lui x18, 0x00000008
addi x18, x18, 0x000000b8
lui x19, 0x00000000
addi x19, x19, 0x00000008
lui x20, 0x00000000
addi x20, x20, 0x00000003
lui x21, 0x00000000
addi x21, x21, 0x00000006
lui x22, 0x00000000
addi x22, x22, 0x00000002
lui x25, 0x00000008
addi x25, x25, 0x00000000
lui x05, 0x00000000
addi x05, x05, 0x00000000
lui x06, 0x00000000
addi x06, x06, 0x00000000
lui x07, 0x00000000
addi x07, x07, 0x00000000
bge t0, s6, end
lui x06, 0x00000000
addi x06, x06, 0x00000000
jal rows
addi t0, t0, 1
j x0, channel
bge t1, s5, return
addi sp, sp, -4
sw ra, 0(sp)
lui x07, 0x00000000
addi x07, x07, 0x00000000
jal columns
lw ra, 0(sp)
addi sp, sp, 4
addi t1, t1, 1
j x0, rows
bge t2, s5, return
addi sp, sp, -4
sw ra, 0(sp)
jal calculate
lw ra, 0(sp)
addi sp, sp, 4
addi t2, t2, 1
j x0, columns
mul a0, t0, s3
mul a0, a0, s3
mul a1, t1, s3
add a0, a0, a1
add a0, a0, t2
add a0, a0, s0
vle8_v v0, 0(a0)
addi a0, a0, 8
vle8_v v3, 0(a0)
addi a0, a0, 8
vle8_v v4, 0(a0)
mul a1, t0, s4
mul a1, a1, s3
add a1, a1, s1
vle8_v v5, 0(a1)
addi a1, a1, 8
vle8_v v6, 0(a1)
addi a1, a1, 8
vle8_v v7, 0(a1)
vmul_vv v0, v0, v5
vmul_vv v3, v3, v6
vmul_vv v4, v4, v7
vadd_vv v0, v0, v3
vadd_vv v0, v0, v4
vse8_v v0, 0(s9)
lb a0, 0(s9)
lb a1, 1(s9)
add a0, a0, a1
lb a1, 2(s9)
add a0, a0, a1
mul a2, t1, s5
add a2, a2, t2
add a2, a2, s2
lb a3, 0(a2)
add a3, a3, a0
sb a3, 0(a2)
jalr x0, x1, x0
jalr x0, x1, x0
vle8_v v20, 0(s2)
addi s2, s2, 6
vle8_v v21, 0(s2)
addi s2, s2, 6
vle8_v v22, 0(s2)
addi s2, s2, 6
vle8_v v23, 0(s2)
addi s2, s2, 6
vle8_v v24, 0(s2)
addi s2, s2, 6
vle8_v v25, 0(s2)
hcf