circuit NegIntGen :
  module NegIntGen :
    input clock : Clock
    input reset : UInt<1>
    output io : { flip key_in : UInt<4>, value : { valid : UInt<1>, bits : UInt<32>}}

    wire operator : UInt<1>
    operator <= UInt<1>("h0")
    node _T = geq(io.key_in, UInt<4>("ha")) @[NegIntGen.scala 14:25]
    node _T_1 = leq(io.key_in, UInt<4>("he")) @[NegIntGen.scala 14:44]
    node _T_2 = and(_T, _T_1) @[NegIntGen.scala 14:32]
    operator <= _T_2 @[NegIntGen.scala 14:14]
    wire num : UInt<1>
    num <= UInt<1>("h0")
    node _T_3 = lt(io.key_in, UInt<4>("ha")) @[NegIntGen.scala 17:21]
    num <= _T_3 @[NegIntGen.scala 17:9]
    wire equal : UInt<1>
    equal <= UInt<1>("h0")
    node _T_4 = eq(io.key_in, UInt<4>("hf")) @[NegIntGen.scala 20:23]
    equal <= _T_4 @[NegIntGen.scala 20:11]
    reg in_buffer1 : UInt, clock with :
      reset => (UInt<1>("h0"), in_buffer1) @[NegIntGen.scala 22:29]
    in_buffer1 <= io.key_in @[NegIntGen.scala 22:29]
    reg src1 : UInt<32>, clock with :
      reset => (reset, UInt<32>("h0")) @[NegIntGen.scala 23:23]
    reg left_brackets_flag : UInt<1>, clock with :
      reset => (reset, UInt<1>("h0")) @[NegIntGen.scala 28:35]
    reg negative_sign : UInt<1>, clock with :
      reset => (reset, UInt<1>("h0")) @[NegIntGen.scala 29:30]
    reg state : UInt<2>, clock with :
      reset => (reset, UInt<2>("h0")) @[NegIntGen.scala 31:22]
    node _T_5 = eq(UInt<2>("h0"), state) @[Conditional.scala 37:30]
    when _T_5 : @[Conditional.scala 40:58]
      when operator : @[NegIntGen.scala 35:27]
        state <= UInt<2>("h2") @[NegIntGen.scala 36:22]
      else :
        when num : @[NegIntGen.scala 37:28]
          state <= UInt<2>("h1") @[NegIntGen.scala 38:22]
    else :
      node _T_6 = eq(UInt<2>("h1"), state) @[Conditional.scala 37:30]
      when _T_6 : @[Conditional.scala 39:67]
        when equal : @[NegIntGen.scala 42:24]
          state <= UInt<2>("h3") @[NegIntGen.scala 43:22]
      else :
        node _T_7 = eq(UInt<2>("h2"), state) @[Conditional.scala 37:30]
        when _T_7 : @[Conditional.scala 39:67]
          when num : @[NegIntGen.scala 47:22]
            state <= UInt<2>("h1") @[NegIntGen.scala 48:22]
          else :
            when equal : @[NegIntGen.scala 49:30]
              state <= UInt<2>("h3") @[NegIntGen.scala 50:22]
        else :
          node _T_8 = eq(UInt<2>("h3"), state) @[Conditional.scala 37:30]
          when _T_8 : @[Conditional.scala 39:67]
            state <= UInt<2>("h0") @[NegIntGen.scala 54:17]
    node _T_9 = eq(state, UInt<2>("h1")) @[NegIntGen.scala 58:15]
    when _T_9 : @[NegIntGen.scala 58:24]
      node _T_10 = eq(left_brackets_flag, UInt<1>("h1")) @[NegIntGen.scala 59:32]
      node _T_11 = eq(negative_sign, UInt<1>("h1")) @[NegIntGen.scala 59:55]
      node _T_12 = and(_T_10, _T_11) @[NegIntGen.scala 59:39]
      when _T_12 : @[NegIntGen.scala 59:63]
        node _T_13 = dshl(src1, UInt<2>("h3")) @[NegIntGen.scala 60:25]
        node _T_14 = dshl(src1, UInt<1>("h1")) @[NegIntGen.scala 60:37]
        node _T_15 = add(_T_13, _T_14) @[NegIntGen.scala 60:31]
        node _T_16 = tail(_T_15, 1) @[NegIntGen.scala 60:31]
        node _T_17 = sub(_T_16, in_buffer1) @[NegIntGen.scala 60:43]
        node _T_18 = tail(_T_17, 1) @[NegIntGen.scala 60:43]
        src1 <= _T_18 @[NegIntGen.scala 60:17]
      else :
        node _T_19 = dshl(src1, UInt<2>("h3")) @[NegIntGen.scala 63:20]
        node _T_20 = dshl(src1, UInt<1>("h1")) @[NegIntGen.scala 63:32]
        node _T_21 = add(_T_19, _T_20) @[NegIntGen.scala 63:26]
        node _T_22 = tail(_T_21, 1) @[NegIntGen.scala 63:26]
        node _T_23 = add(_T_22, in_buffer1) @[NegIntGen.scala 63:38]
        node _T_24 = tail(_T_23, 1) @[NegIntGen.scala 63:38]
        src1 <= _T_24 @[NegIntGen.scala 63:13]
    node _T_25 = eq(state, UInt<2>("h2")) @[NegIntGen.scala 67:15]
    when _T_25 : @[NegIntGen.scala 67:22]
      node _T_26 = eq(in_buffer1, UInt<4>("hd")) @[NegIntGen.scala 68:24]
      when _T_26 : @[NegIntGen.scala 68:32]
        left_brackets_flag <= UInt<1>("h1") @[NegIntGen.scala 69:31]
      else :
        node _T_27 = eq(in_buffer1, UInt<4>("hb")) @[NegIntGen.scala 70:30]
        when _T_27 : @[NegIntGen.scala 70:38]
          negative_sign <= UInt<1>("h1") @[NegIntGen.scala 71:26]
        else :
          node _T_28 = eq(in_buffer1, UInt<4>("he")) @[NegIntGen.scala 72:30]
          when _T_28 : @[NegIntGen.scala 72:38]
            left_brackets_flag <= UInt<1>("h0") @[NegIntGen.scala 73:31]
            negative_sign <= UInt<1>("h0") @[NegIntGen.scala 74:26]
    node _T_29 = eq(state, UInt<2>("h3")) @[NegIntGen.scala 78:15]
    when _T_29 : @[NegIntGen.scala 78:25]
      src1 <= UInt<1>("h0") @[NegIntGen.scala 79:13]
    node _T_30 = eq(state, UInt<2>("h3")) @[NegIntGen.scala 84:32]
    node _T_31 = mux(_T_30, UInt<1>("h1"), UInt<1>("h0")) @[NegIntGen.scala 84:26]
    io.value.valid <= _T_31 @[NegIntGen.scala 84:20]
    node _T_32 = eq(left_brackets_flag, UInt<1>("h1")) @[NegIntGen.scala 85:44]
    node _T_33 = eq(negative_sign, UInt<1>("h1")) @[NegIntGen.scala 85:67]
    node _T_34 = and(_T_32, _T_33) @[NegIntGen.scala 85:51]
    node _T_35 = mux(_T_34, src1, src1) @[NegIntGen.scala 85:25]
    io.value.bits <= _T_35 @[NegIntGen.scala 85:19]

