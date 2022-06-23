// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VNegIntGen_H_
#define _VNegIntGen_H_

#include "verilated.h"

class VNegIntGen__Syms;
class VerilatedVcd;

//----------

VL_MODULE(VNegIntGen) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clock,0,0);
    VL_IN8(reset,0,0);
    VL_IN8(io_key_in,3,0);
    VL_OUT8(io_value_valid,0,0);
    VL_OUT(io_value_bits,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    VL_SIG8(NegIntGen__DOT__in_buffer1,3,0);
    VL_SIG8(NegIntGen__DOT__left_brackets_flag,0,0);
    VL_SIG8(NegIntGen__DOT__negative_sign,0,0);
    VL_SIG8(NegIntGen__DOT__state,1,0);
    VL_SIG8(NegIntGen__DOT___T_5,0,0);
    VL_SIG8(NegIntGen__DOT___T_6,0,0);
    VL_SIG8(NegIntGen__DOT___T_7,0,0);
    VL_SIG8(NegIntGen__DOT___GEN_3,1,0);
    VL_SIG8(NegIntGen__DOT___GEN_4,1,0);
    VL_SIG8(NegIntGen__DOT___GEN_12,0,0);
    VL_SIG8(NegIntGen__DOT___GEN_14,0,0);
    VL_SIG(NegIntGen__DOT__src1,31,0);
    VL_SIG64(NegIntGen__DOT___T_16,34,0);
    VL_SIG64(NegIntGen__DOT___GEN_18,34,0);
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    VL_SIG8(__Vclklast__TOP__clock,0,0);
    VL_SIG(__Vm_traceActivity,31,0);
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    VNegIntGen__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    
    // CONSTRUCTORS
  private:
    VNegIntGen& operator= (const VNegIntGen&);  ///< Copying not allowed
    VNegIntGen(const VNegIntGen&);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible WRT DPI scope names.
    VNegIntGen(const char* name="TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~VNegIntGen();
    /// Trace signals in the model; called by application code
    void trace (VerilatedVcdC* tfp, int levels, int options=0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval();
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(VNegIntGen__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(VNegIntGen__Syms* symsp, bool first);
  private:
    static QData _change_request(VNegIntGen__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(VNegIntGen__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset();
  public:
    static void _eval(VNegIntGen__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif // VL_DEBUG
  public:
    static void _eval_initial(VNegIntGen__Syms* __restrict vlSymsp);
    static void _eval_settle(VNegIntGen__Syms* __restrict vlSymsp);
    static void _sequent__TOP__1(VNegIntGen__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(VNegIntGen__Syms* __restrict vlSymsp);
    static void traceChgThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__2(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceChgThis__3(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceFullThis__1(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInitThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInitThis__1(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code);
    static void traceInit (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceFull (VerilatedVcd* vcdp, void* userthis, uint32_t code);
    static void traceChg  (VerilatedVcd* vcdp, void* userthis, uint32_t code);
} VL_ATTR_ALIGNED(128);

#endif // guard
