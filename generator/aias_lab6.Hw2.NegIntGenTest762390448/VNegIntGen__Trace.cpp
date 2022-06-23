// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "VNegIntGen__Syms.h"


//======================

void VNegIntGen::traceChg(VerilatedVcd* vcdp, void* userthis, uint32_t code) {
    // Callback from vcd->dump()
    VNegIntGen* t=(VNegIntGen*)userthis;
    VNegIntGen__Syms* __restrict vlSymsp = t->__VlSymsp;  // Setup global symbol table
    if (vlSymsp->getClearActivity()) {
	t->traceChgThis (vlSymsp, vcdp, code);
    }
}

//======================


void VNegIntGen::traceChgThis(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	if (VL_UNLIKELY((2U & vlTOPp->__Vm_traceActivity))) {
	    vlTOPp->traceChgThis__2(vlSymsp, vcdp, code);
	}
	vlTOPp->traceChgThis__3(vlSymsp, vcdp, code);
    }
    // Final
    vlTOPp->__Vm_traceActivity = 0U;
}

void VNegIntGen::traceChgThis__2(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBus  (c+1,(vlTOPp->NegIntGen__DOT__in_buffer1),4);
	vcdp->chgBus  (c+2,(vlTOPp->NegIntGen__DOT__src1),32);
	vcdp->chgBit  (c+3,(vlTOPp->NegIntGen__DOT__left_brackets_flag));
	vcdp->chgBit  (c+4,(vlTOPp->NegIntGen__DOT__negative_sign));
	vcdp->chgBus  (c+5,(vlTOPp->NegIntGen__DOT__state),2);
    }
}

void VNegIntGen::traceChgThis__3(VNegIntGen__Syms* __restrict vlSymsp, VerilatedVcd* vcdp, uint32_t code) {
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    int c=code;
    if (0 && vcdp && c) {}  // Prevent unused
    // Body
    {
	vcdp->chgBit  (c+6,(vlTOPp->clock));
	vcdp->chgBit  (c+7,(vlTOPp->reset));
	vcdp->chgBus  (c+8,(vlTOPp->io_key_in),4);
	vcdp->chgBit  (c+9,(vlTOPp->io_value_valid));
	vcdp->chgBus  (c+10,(vlTOPp->io_value_bits),32);
	vcdp->chgBit  (c+11,(((0xaU <= (IData)(vlTOPp->io_key_in)) 
			      & (0xeU >= (IData)(vlTOPp->io_key_in)))));
	vcdp->chgBit  (c+12,((0xaU > (IData)(vlTOPp->io_key_in))));
	vcdp->chgBit  (c+13,((0xfU == (IData)(vlTOPp->io_key_in))));
    }
}
