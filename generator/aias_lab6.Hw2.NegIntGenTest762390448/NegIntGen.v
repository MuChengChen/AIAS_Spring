module NegIntGen(
  input         clock,
  input         reset,
  input  [3:0]  io_key_in,
  output        io_value_valid,
  output [31:0] io_value_bits
);
`ifdef RANDOMIZE_REG_INIT
  reg [31:0] _RAND_0;
  reg [31:0] _RAND_1;
  reg [31:0] _RAND_2;
  reg [31:0] _RAND_3;
  reg [31:0] _RAND_4;
`endif // RANDOMIZE_REG_INIT
  wire  operator = io_key_in >= 4'ha & io_key_in <= 4'he; // @[NegIntGen.scala 14:32]
  wire  num = io_key_in < 4'ha; // @[NegIntGen.scala 17:21]
  wire  equal = io_key_in == 4'hf; // @[NegIntGen.scala 20:23]
  reg [3:0] in_buffer1; // @[NegIntGen.scala 22:29]
  reg [31:0] src1; // @[NegIntGen.scala 23:23]
  reg  left_brackets_flag; // @[NegIntGen.scala 28:35]
  reg  negative_sign; // @[NegIntGen.scala 29:30]
  reg [1:0] state; // @[NegIntGen.scala 31:22]
  wire  _T_5 = 2'h0 == state; // @[Conditional.scala 37:30]
  wire  _T_6 = 2'h1 == state; // @[Conditional.scala 37:30]
  wire [1:0] _GEN_2 = equal ? 2'h3 : state; // @[NegIntGen.scala 42:24 NegIntGen.scala 43:22 NegIntGen.scala 31:22]
  wire  _T_7 = 2'h2 == state; // @[Conditional.scala 37:30]
  wire [1:0] _GEN_3 = num ? 2'h1 : _GEN_2; // @[NegIntGen.scala 47:22 NegIntGen.scala 48:22]
  wire  _T_8 = 2'h3 == state; // @[Conditional.scala 37:30]
  wire [1:0] _GEN_4 = _T_8 ? 2'h0 : state; // @[Conditional.scala 39:67 NegIntGen.scala 54:17 NegIntGen.scala 31:22]
  wire [34:0] _T_13 = {src1, 3'h0}; // @[NegIntGen.scala 60:25]
  wire [32:0] _T_14 = {src1, 1'h0}; // @[NegIntGen.scala 60:37]
  wire [34:0] _GEN_19 = {{2'd0}, _T_14}; // @[NegIntGen.scala 60:31]
  wire [34:0] _T_16 = _T_13 + _GEN_19; // @[NegIntGen.scala 60:31]
  wire [34:0] _GEN_20 = {{31'd0}, in_buffer1}; // @[NegIntGen.scala 60:43]
  wire [34:0] _T_18 = _T_16 - _GEN_20; // @[NegIntGen.scala 60:43]
  wire [34:0] _T_24 = _T_16 + _GEN_20; // @[NegIntGen.scala 63:38]
  wire [34:0] _GEN_8 = left_brackets_flag & negative_sign ? _T_18 : _T_24; // @[NegIntGen.scala 59:63 NegIntGen.scala 60:17 NegIntGen.scala 63:13]
  wire [34:0] _GEN_9 = state == 2'h1 ? _GEN_8 : {{3'd0}, src1}; // @[NegIntGen.scala 58:24 NegIntGen.scala 23:23]
  wire  _GEN_10 = in_buffer1 == 4'he ? 1'h0 : left_brackets_flag; // @[NegIntGen.scala 72:38 NegIntGen.scala 73:31 NegIntGen.scala 28:35]
  wire  _GEN_11 = in_buffer1 == 4'he ? 1'h0 : negative_sign; // @[NegIntGen.scala 72:38 NegIntGen.scala 74:26 NegIntGen.scala 29:30]
  wire  _GEN_12 = in_buffer1 == 4'hb | _GEN_11; // @[NegIntGen.scala 70:38 NegIntGen.scala 71:26]
  wire  _GEN_13 = in_buffer1 == 4'hb ? left_brackets_flag : _GEN_10; // @[NegIntGen.scala 70:38 NegIntGen.scala 28:35]
  wire  _GEN_14 = in_buffer1 == 4'hd | _GEN_13; // @[NegIntGen.scala 68:32 NegIntGen.scala 69:31]
  wire [34:0] _GEN_18 = state == 2'h3 ? 35'h0 : _GEN_9; // @[NegIntGen.scala 78:25 NegIntGen.scala 79:13]
  assign io_value_valid = state == 2'h3; // @[NegIntGen.scala 84:32]
  assign io_value_bits = src1; // @[NegIntGen.scala 85:25]
  always @(posedge clock) begin
    in_buffer1 <= io_key_in; // @[NegIntGen.scala 22:29]
    if (reset) begin // @[NegIntGen.scala 23:23]
      src1 <= 32'h0; // @[NegIntGen.scala 23:23]
    end else begin
      src1 <= _GEN_18[31:0];
    end
    if (reset) begin // @[NegIntGen.scala 28:35]
      left_brackets_flag <= 1'h0; // @[NegIntGen.scala 28:35]
    end else if (state == 2'h2) begin // @[NegIntGen.scala 67:22]
      left_brackets_flag <= _GEN_14;
    end
    if (reset) begin // @[NegIntGen.scala 29:30]
      negative_sign <= 1'h0; // @[NegIntGen.scala 29:30]
    end else if (state == 2'h2) begin // @[NegIntGen.scala 67:22]
      if (!(in_buffer1 == 4'hd)) begin // @[NegIntGen.scala 68:32]
        negative_sign <= _GEN_12;
      end
    end
    if (reset) begin // @[NegIntGen.scala 31:22]
      state <= 2'h0; // @[NegIntGen.scala 31:22]
    end else if (_T_5) begin // @[Conditional.scala 40:58]
      if (operator) begin // @[NegIntGen.scala 35:27]
        state <= 2'h2; // @[NegIntGen.scala 36:22]
      end else if (num) begin // @[NegIntGen.scala 37:28]
        state <= 2'h1; // @[NegIntGen.scala 38:22]
      end
    end else if (_T_6) begin // @[Conditional.scala 39:67]
      if (equal) begin // @[NegIntGen.scala 42:24]
        state <= 2'h3; // @[NegIntGen.scala 43:22]
      end
    end else if (_T_7) begin // @[Conditional.scala 39:67]
      state <= _GEN_3;
    end else begin
      state <= _GEN_4;
    end
  end
// Register and memory initialization
`ifdef RANDOMIZE_GARBAGE_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_INVALID_ASSIGN
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_REG_INIT
`define RANDOMIZE
`endif
`ifdef RANDOMIZE_MEM_INIT
`define RANDOMIZE
`endif
`ifndef RANDOM
`define RANDOM $random
`endif
`ifdef RANDOMIZE_MEM_INIT
  integer initvar;
`endif
`ifndef SYNTHESIS
`ifdef FIRRTL_BEFORE_INITIAL
`FIRRTL_BEFORE_INITIAL
`endif
initial begin
  `ifdef RANDOMIZE
    `ifdef INIT_RANDOM
      `INIT_RANDOM
    `endif
    `ifndef VERILATOR
      `ifdef RANDOMIZE_DELAY
        #`RANDOMIZE_DELAY begin end
      `else
        #0.002 begin end
      `endif
    `endif
`ifdef RANDOMIZE_REG_INIT
  _RAND_0 = {1{`RANDOM}};
  in_buffer1 = _RAND_0[3:0];
  _RAND_1 = {1{`RANDOM}};
  src1 = _RAND_1[31:0];
  _RAND_2 = {1{`RANDOM}};
  left_brackets_flag = _RAND_2[0:0];
  _RAND_3 = {1{`RANDOM}};
  negative_sign = _RAND_3[0:0];
  _RAND_4 = {1{`RANDOM}};
  state = _RAND_4[1:0];
`endif // RANDOMIZE_REG_INIT
  `endif // RANDOMIZE
end // initial
`ifdef FIRRTL_AFTER_INITIAL
`FIRRTL_AFTER_INITIAL
`endif
`endif // SYNTHESIS
endmodule
