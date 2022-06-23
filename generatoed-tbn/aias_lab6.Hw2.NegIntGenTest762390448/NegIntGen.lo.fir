circuit NegIntGen :
  module NegIntGen :
    input clock : Clock
    input reset : UInt<1>
    input io_key_in : UInt<4>
    output io_value_valid : UInt<1>
    output io_value_bits : UInt<32>

    node _T = geq(io_key_in, UInt<4>("ha")) @[NegIntGen.scala 14:25]
    node _T_1 = leq(io_key_in, UInt<4>("he")) @[NegIntGen.scala 14:44]
    node _T_2 = and(_T, _T_1) @[NegIntGen.scala 14:32]
    node _T_3 = lt(io_key_in, UInt<4>("ha")) @[NegIntGen.scala 17:21]
    node _T_4 = eq(io_key_in, UInt<4>("hf")) @[NegIntGen.scala 20:23]
    reg in_buffer1 : UInt<4>, clock with :
      reset => (UInt<1>("h0"), in_buffer1) @[NegIntGen.scala 22:29]
    reg src1 : UInt<32>, clock with :
      reset => (UInt<1>("h0"), src1) @[NegIntGen.scala 23:23]
    reg left_brackets_flag : UInt<1>, clock with :
      reset => (UInt<1>("h0"), left_brackets_flag) @[NegIntGen.scala 28:35]
    reg negative_sign : UInt<1>, clock with :
      reset => (UInt<1>("h0"), negative_sign) @[NegIntGen.scala 29:30]
    reg state : UInt<2>, clock with :
      reset => (UInt<1>("h0"), state) @[NegIntGen.scala 31:22]
    node _T_5 = eq(UInt<2>("h0"), state) @[Conditional.scala 37:30]
    node num = _T_3
    node _GEN_0 = mux(num, UInt<2>("h1"), state) @[NegIntGen.scala 37:28 NegIntGen.scala 38:22 NegIntGen.scala 31:22]
    node operator = _T_2
    node _GEN_1 = mux(operator, UInt<2>("h2"), _GEN_0) @[NegIntGen.scala 35:27 NegIntGen.scala 36:22]
    node _T_6 = eq(UInt<2>("h1"), state) @[Conditional.scala 37:30]
    node equal = _T_4
    node _GEN_2 = mux(equal, UInt<2>("h3"), state) @[NegIntGen.scala 42:24 NegIntGen.scala 43:22 NegIntGen.scala 31:22]
    node _T_7 = eq(UInt<2>("h2"), state) @[Conditional.scala 37:30]
    node _GEN_3 = mux(num, UInt<2>("h1"), _GEN_2) @[NegIntGen.scala 47:22 NegIntGen.scala 48:22]
    node _T_8 = eq(UInt<2>("h3"), state) @[Conditional.scala 37:30]
    node _GEN_4 = mux(_T_8, UInt<2>("h0"), state) @[Conditional.scala 39:67 NegIntGen.scala 54:17 NegIntGen.scala 31:22]
    node _GEN_5 = mux(_T_7, _GEN_3, _GEN_4) @[Conditional.scala 39:67]
    node _GEN_6 = mux(_T_6, _GEN_2, _GEN_5) @[Conditional.scala 39:67]
    node _GEN_7 = mux(_T_5, _GEN_1, _GEN_6) @[Conditional.scala 40:58]
    node _T_9 = eq(state, UInt<2>("h1")) @[NegIntGen.scala 58:15]
    node _T_10 = eq(left_brackets_flag, UInt<1>("h1")) @[NegIntGen.scala 59:32]
    node _T_11 = eq(negative_sign, UInt<1>("h1")) @[NegIntGen.scala 59:55]
    node _T_12 = and(_T_10, _T_11) @[NegIntGen.scala 59:39]
    node _T_13 = dshl(src1, UInt<2>("h3")) @[NegIntGen.scala 60:25]
    node _T_14 = dshl(src1, UInt<1>("h1")) @[NegIntGen.scala 60:37]
    node _T_15 = add(_T_13, _T_14) @[NegIntGen.scala 60:31]
    node _T_16 = tail(_T_15, 1) @[NegIntGen.scala 60:31]
    node _T_17 = sub(_T_16, in_buffer1) @[NegIntGen.scala 60:43]
    node _T_18 = tail(_T_17, 1) @[NegIntGen.scala 60:43]
    node _T_19 = dshl(src1, UInt<2>("h3")) @[NegIntGen.scala 63:20]
    node _T_20 = dshl(src1, UInt<1>("h1")) @[NegIntGen.scala 63:32]
    node _T_21 = add(_T_19, _T_20) @[NegIntGen.scala 63:26]
    node _T_22 = tail(_T_21, 1) @[NegIntGen.scala 63:26]
    node _T_23 = add(_T_22, in_buffer1) @[NegIntGen.scala 63:38]
    node _T_24 = tail(_T_23, 1) @[NegIntGen.scala 63:38]
    node _GEN_8 = mux(_T_12, _T_18, _T_24) @[NegIntGen.scala 59:63 NegIntGen.scala 60:17 NegIntGen.scala 63:13]
    node _GEN_9 = mux(_T_9, _GEN_8, src1) @[NegIntGen.scala 58:24 NegIntGen.scala 23:23]
    node _T_25 = eq(state, UInt<2>("h2")) @[NegIntGen.scala 67:15]
    node _T_26 = eq(in_buffer1, UInt<4>("hd")) @[NegIntGen.scala 68:24]
    node _T_27 = eq(in_buffer1, UInt<4>("hb")) @[NegIntGen.scala 70:30]
    node _T_28 = eq(in_buffer1, UInt<4>("he")) @[NegIntGen.scala 72:30]
    node _GEN_10 = mux(_T_28, UInt<1>("h0"), left_brackets_flag) @[NegIntGen.scala 72:38 NegIntGen.scala 73:31 NegIntGen.scala 28:35]
    node _GEN_11 = mux(_T_28, UInt<1>("h0"), negative_sign) @[NegIntGen.scala 72:38 NegIntGen.scala 74:26 NegIntGen.scala 29:30]
    node _GEN_12 = mux(_T_27, UInt<1>("h1"), _GEN_11) @[NegIntGen.scala 70:38 NegIntGen.scala 71:26]
    node _GEN_13 = mux(_T_27, left_brackets_flag, _GEN_10) @[NegIntGen.scala 70:38 NegIntGen.scala 28:35]
    node _GEN_14 = mux(_T_26, UInt<1>("h1"), _GEN_13) @[NegIntGen.scala 68:32 NegIntGen.scala 69:31]
    node _GEN_15 = mux(_T_26, negative_sign, _GEN_12) @[NegIntGen.scala 68:32 NegIntGen.scala 29:30]
    node _GEN_16 = mux(_T_25, _GEN_14, left_brackets_flag) @[NegIntGen.scala 67:22 NegIntGen.scala 28:35]
    node _GEN_17 = mux(_T_25, _GEN_15, negative_sign) @[NegIntGen.scala 67:22 NegIntGen.scala 29:30]
    node _T_29 = eq(state, UInt<2>("h3")) @[NegIntGen.scala 78:15]
    node _GEN_18 = mux(_T_29, UInt<1>("h0"), _GEN_9) @[NegIntGen.scala 78:25 NegIntGen.scala 79:13]
    node _T_30 = eq(state, UInt<2>("h3")) @[NegIntGen.scala 84:32]
    node _T_31 = mux(_T_30, UInt<1>("h1"), UInt<1>("h0")) @[NegIntGen.scala 84:26]
    node _T_32 = eq(left_brackets_flag, UInt<1>("h1")) @[NegIntGen.scala 85:44]
    node _T_33 = eq(negative_sign, UInt<1>("h1")) @[NegIntGen.scala 85:67]
    node _T_34 = and(_T_32, _T_33) @[NegIntGen.scala 85:51]
    node _T_35 = mux(_T_34, src1, src1) @[NegIntGen.scala 85:25]
    io_value_valid <= _T_31 @[NegIntGen.scala 84:20]
    io_value_bits <= _T_35 @[NegIntGen.scala 85:19]
    in_buffer1 <= io_key_in @[NegIntGen.scala 22:29]
    src1 <= mux(reset, UInt<32>("h0"), bits(_GEN_18, 31, 0)) @[NegIntGen.scala 23:23 NegIntGen.scala 23:23]
    left_brackets_flag <= mux(reset, UInt<1>("h0"), _GEN_16) @[NegIntGen.scala 28:35 NegIntGen.scala 28:35]
    negative_sign <= mux(reset, UInt<1>("h0"), _GEN_17) @[NegIntGen.scala 29:30 NegIntGen.scala 29:30]
    state <= mux(reset, UInt<2>("h0"), _GEN_7) @[NegIntGen.scala 31:22 NegIntGen.scala 31:22]
