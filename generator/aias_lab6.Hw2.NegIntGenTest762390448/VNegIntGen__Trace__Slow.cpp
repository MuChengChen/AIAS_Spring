// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VNegIntGen__Syms.h"


//======================

void VNegIntGen::trace (VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addCallback (&VNegIntGen::traceInit, &VNegIntGen::traceFull, &VNegIntGen::traceChg, this);
}
void VNegIntGen::traceInit(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->open()
    VNegIntGen* t=(VNegIntGen*)userthis;
    VNegIntGen__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (!Verilated::calcUnusedSigs()) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    vcdp->scopeEscape(' ');
    t->traceInitThis (vlSymsp, vcdp, code);
    vcdp->scopeEscape('.');
}
void VNegIntGen::traceFull(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    VNegIntGen* t=(VNegIntGen*)userthis;
    VNegIntGen__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    t->traceFullThis (vlSymsp, vcdp, code);
}

//======================


void VNegIntGen::traceInitThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    vcdp->module(vlSymsp->name());  // Setup signal names
    // Body
    {
	vlTOPp->traceInitThis__1(vlSymsp, vcdp, code);
    }
}

void VNegIntGen::traceFullThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vlTOPp->traceFullThis__1(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void VNegIntGen::traceInitThis__1(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->declBit  (c+6,"clock",-1);
	vcdp->declBit  (c+7,"reset",-1);
	vcdp->declBus  (c+8,"io_key_in",-1,3,0);
	vcdp->declBit  (c+9,"io_value_valid",-1);
	vcdp->declBus  (c+10,"io_value_bits",-1,31,0);
	vcdp->declBit  (c+6,"NegIntGen clock",-1);
	vcdp->declBit  (c+7,"NegIntGen reset",-1);
	vcdp->declBus  (c+8,"NegIntGen io_key_in",-1,3,0);
	vcdp->declBit  (c+9,"NegIntGen io_value_valid",-1);
	vcdp->declBus  (c+10,"NegIntGen io_value_bits",-1,31,0);
	vcdp->declBit  (c+11,"NegIntGen operator",-1);
	vcdp->declBit  (c+12,"NegIntGen num",-1);
	vcdp->declBit  (c+13,"NegIntGen equal",-1);
	vcdp->declBus  (c+1,"NegIntGen in_buffer1",-1,3,0);
	vcdp->declBus  (c+2,"NegIntGen src1",-1,31,0);
	vcdp->declBit  (c+3,"NegIntGen left_brackets_flag",-1);
	vcdp->declBit  (c+4,"NegIntGen negative_sign",-1);
	vcdp->declBus  (c+5,"NegIntGen state",-1,1,0);
	// Tracing: NegIntGen _T_5 // Ignored: Inlined leading underscore at NegIntGen.v:23
	// Tracing: NegIntGen _T_6 // Ignored: Inlined leading underscore at NegIntGen.v:24
	// Tracing: NegIntGen _GEN_2 // Ignored: Inlined leading underscore at NegIntGen.v:25
	// Tracing: NegIntGen _T_7 // Ignored: Inlined leading underscore at NegIntGen.v:26
	// Tracing: NegIntGen _GEN_3 // Ignored: Inlined leading underscore at NegIntGen.v:27
	// Tracing: NegIntGen _T_8 // Ignored: Inlined leading underscore at NegIntGen.v:28
	// Tracing: NegIntGen _GEN_4 // Ignored: Inlined leading underscore at NegIntGen.v:29
	// Tracing: NegIntGen _T_13 // Ignored: Inlined leading underscore at NegIntGen.v:30
	// Tracing: NegIntGen _T_14 // Ignored: Inlined leading underscore at NegIntGen.v:31
	// Tracing: NegIntGen _GEN_19 // Ignored: Inlined leading underscore at NegIntGen.v:32
	// Tracing: NegIntGen _T_16 // Ignored: Inlined leading underscore at NegIntGen.v:33
	// Tracing: NegIntGen _GEN_20 // Ignored: Inlined leading underscore at NegIntGen.v:34
	// Tracing: NegIntGen _T_18 // Ignored: Inlined leading underscore at NegIntGen.v:35
	// Tracing: NegIntGen _T_24 // Ignored: Inlined leading underscore at NegIntGen.v:36
	// Tracing: NegIntGen _GEN_8 // Ignored: Inlined leading underscore at NegIntGen.v:37
	// Tracing: NegIntGen _GEN_9 // Ignored: Inlined leading underscore at NegIntGen.v:38
	// Tracing: NegIntGen _GEN_10 // Ignored: Inlined leading underscore at NegIntGen.v:39
	// Tracing: NegIntGen _GEN_11 // Ignored: Inlined leading underscore at NegIntGen.v:40
	// Tracing: NegIntGen _GEN_12 // Ignored: Inlined leading underscore at NegIntGen.v:41
	// Tracing: NegIntGen _GEN_13 // Ignored: Inlined leading underscore at NegIntGen.v:42
	// Tracing: NegIntGen _GEN_14 // Ignored: Inlined leading underscore at NegIntGen.v:43
	// Tracing: NegIntGen _GEN_18 // Ignored: Inlined leading underscore at NegIntGen.v:44
    }
}

void VNegIntGen::traceFullThis__1(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->fullBus  (c+1,(vlTOPp->NegIntGen__DOT__in_buffer1),4);
	vcdp->fullBus  (c+2,(vlTOPp->NegIntGen__DOT__src1),32);
	vcdp->fullBit  (c+3,(vlTOPp->NegIntGen__DOT__left_brackets_flag));
	vcdp->fullBit  (c+4,(vlTOPp->NegIntGen__DOT__negative_sign));
	vcdp->fullBus  (c+5,(vlTOPp->NegIntGen__DOT__state),2);
	vcdp->fullBit  (c+6,(vlTOPp->clock));
	vcdp->fullBit  (c+7,(vlTOPp->reset));
	vcdp->fullBus  (c+8,(vlTOPp->io_key_in),4);
	vcdp->fullBit  (c+9,(vlTOPp->io_value_valid));
	vcdp->fullBus  (c+10,(vlTOPp->io_value_bits),32);
	vcdp->fullBit  (c+11,(((0xaU <= (IData)(vlTOPp->io_key_in)) 
			       & (0xeU >= (IData)(vlTOPp->io_key_in)))));
	vcdp->fullBit  (c+12,((0xaU > (IData)(vlTOPp->io_key_in))));
	vcdp->fullBit  (c+13,((0xfU == (IData)(vlTOPp->io_key_in))));
    }
}
