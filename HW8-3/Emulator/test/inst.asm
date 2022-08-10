lui x12, 0x00000008
addi x12, x12, 0x00000000
lui x13, 0x00000008
addi x13, x13, 0x00000008
vle8_v v0, 0(a3)
lui x19, 0x00000000
addi x19, x19, 0x00000003
lui x08, 0x00000000
addi x08, x08, 0x00000005
lui x09, 0x00000000
addi x09, x09, 0x00000002
mul s2, s0, s1
div s4, s2, s3
lui x22, 0x00000000
addi x22, x22, 0x00000058
vle8_v v4, 0(a2)
lui x11, 0x00000000
addi x11, x11, 0x00000005
vmul_vx v3, v4, a1
vmul_vv v5, v4, v3
addi a2, a2, 8
vse8_v v3, 0(a2)
addi a2, a2, -8
lui x10, 0x00000000
addi x10, x10, 0x00000003
vadd_vv v6, v0, v4
hcf