## 組員名單

王凱弘
陳玟樺
謝獻霆
宋方瑜
陳慕丞

## 指令認領名單
| RV32 | RV64     | Mnemonic                  | Instruction       | Zba      | Zbb | Zbc | Zbs |Owner|
| ---- | -------- | ------------------------- | ----------------- | -------- | --- | --- | --- |---|
|      | &#10003; | add.uw _rd_, _rs1_, _rs2_ | [insns-add_uw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/add_uw.adoc) | &#10003; |     |     |     |  |
|&#10003;|&#10003;|andn _rd_, _rs1_, _rs2_|[insns-andn](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/andn.adoc)||&#10003;|| | 謝獻霆|
|&#10003;|&#10003;|clmul _rd_, _rs1_, _rs2_|[insns-clmul](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/clmul.adoc)|||&#10003;| | 謝獻霆|
|&#10003;|&#10003;|clmulh _rd_, _rs1_, _rs2_|[insns-clmulh](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/clmulh.adoc)|||&#10003;|| 謝獻霆|
|&#10003;|&#10003;|clmulr _rd_, _rs1_, _rs2_|[insns-clmulr](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/clmulr.adoc)|||&#10003;|| 謝獻霆|
|&#10003;|&#10003;|clz _rd_, _rs_|[insns-clz](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/clz.adoc)||&#10003;|||謝獻霆
||&#10003;|clzw _rd_, _rs_|[insns-clzw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/clzw.adoc)||&#10003;| | | |
|&#10003;|&#10003;|cpop _rd_, _rs_|[insns-cpop](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/cpop.adoc)||&#10003;|| | 謝獻霆|
||&#10003;|cpopw _rd_, _rs_|[insns-cpopw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/cpopw.adoc)||&#10003;|| ||
|&#10003;|&#10003;|ctz _rd_, _rs_|[insns-ctz](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/ctz.adoc)||&#10003;|| |謝獻霆 |
||&#10003;|ctzw _rd_, _rs_|[insns-ctzw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/ctzw.adoc)||&#10003;||||
|&#10003;|&#10003;|max _rd_, _rs1_, _rs2_|[insns-max](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/max.adoc)||&#10003;|| | |
|&#10003;|&#10003;|maxu _rd_, _rs1_, _rs2_|[insns-maxu](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/maxu.adoc)||&#10003;|| | |
|&#10003;|&#10003;|min _rd_, _rs1_, _rs2_|[insns-min](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/min.adoc)||&#10003;|| | |
|&#10003;|&#10003;|minu _rd_, _rs1_, _rs2_|[insns-minu](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/minu.adoc)||&#10003;|| | |
|&#10003;|&#10003;|orc.b _rd_, _rs1_, _rs2_|[insns-orc_b](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/orc.adoc)||&#10003;|| | |
|&#10003;|&#10003;|orn _rd_, _rs1_, _rs2_|[insns-orn](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/orn.adoc)||&#10003;|| | |
|&#10003;|&#10003;|rev8 _rd_, _rs_|[insns-rev8](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/rev8.adoc)||&#10003;|| | |
|&#10003;|&#10003;|rol _rd_, _rs1_, _rs2_|[insns-rol](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/rol.adoc)||&#10003;|| | |
||&#10003;|rolw _rd_, _rs1_, _rs2_|[insns-rolw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/orlw.adoc)||&#10003;|| | |
|&#10003;|&#10003;|ror _rd_, _rs1_, _rs2_|[insns-ror](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/ror.adoc)||&#10003;|| | |
|&#10003;|&#10003;|rori _rd_, _rs1_, _shamt_|[insns-rori](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/rori.adoc)||&#10003;|| | |
||&#10003;|roriw _rd_, _rs1_, _shamt_|[insns-roriw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/roriw.adoc)||&#10003;|| | |
||&#10003;|rorw _rd_, _rs1_, _rs2_|[insns-rorw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/rorw.adoc)||&#10003;|| | |
|&#10003;|&#10003;|bclr _rd_, _rs1_, _rs2_|[insns-bclr](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bclr.adoc)||||&#10003;| | |
|&#10003;|&#10003;|bclri _rd_, _rs1_, _imm_|[insns-bclri](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bclri.adoc)||||&#10003;| | |
|&#10003;|&#10003;|bext _rd_, _rs1_, _rs2_|[insns-bext](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bext.adoc)||||&#10003;| | |
|&#10003;|&#10003;|bexti _rd_, _rs1_, _imm_|[insns-bexti](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bexti.adoc)||||&#10003;| | |
|&#10003;|&#10003;|binv _rd_, _rs1_, _rs2_|[insns-binv](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/binv.adoc)||||&#10003;| | |
|&#10003;|&#10003;|binvi _rd_, _rs1_, _imm_|[insns-binvi](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/binvi.adoc)||||&#10003;| | |
|&#10003;|&#10003;|bset _rd_, _rs1_, _rs2_|[insns-bset](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bset.adoc)||||&#10003;| | |
|&#10003;|&#10003;|bseti _rd_, _rs1_, _imm_|[insns-bseti](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/bseti.adoc)||||&#10003;| | |
|&#10003;|&#10003;|sext.b _rd_, _rs_|[insns-sext_b](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sext_b.adoc)||&#10003;|| | |
|&#10003;|&#10003;|sext.h _rd_, _rs_|[insns-sext_h](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sext_h.adoc)||&#10003;|| | |
|&#10003;|&#10003;|sh1add _rd_, _rs1_, _rs2_|[insns-sh1add](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh1add.adoc)|&#10003;||| | |
||&#10003;|sh1add.uw _rd_, _rs1_, _rs2_|[insns-sh1add_uw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh1add_uw.adoc)|&#10003;||| | |
|&#10003;|&#10003;|sh2add _rd_, _rs1_, _rs2_|[insns-sh2add](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh2add.adoc)|&#10003;||||
||&#10003;|sh2add.uw _rd_, _rs1_, _rs2_|[insns-sh2add_uw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh2add_uw.adoc)|&#10003;||| ||
|&#10003;|&#10003;|sh3add _rd_, _rs2_, _rs2_|[insns-sh3add](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh3add.adoc)|&#10003;||| | |
||&#10003;|sh3add.uw _rd_, _rs1_, _rs2_|[nsns-sh3add_uw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/sh3add_uw.adoc)|&#10003;||| ||
||&#10003;|slli.uw _rd_, _rs1_, _imm_|[insns-slli_uw](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/slli_uw.adoc)|&#10003;||| ||
|&#10003;|&#10003;|xnor _rd_, _rs1_, _rs2_|[insns-xnor](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/xnor.adoc)||&#10003;|| | |
|&#10003;|&#10003;|zext.h _rd_, _rs_|[insns-zext_h](https://github.com/riscv/riscv-bitmanip/blob/main/bitmanip/insns/zext.adoc)||&#10003;|| |