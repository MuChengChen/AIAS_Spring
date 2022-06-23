// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VNegIntGen.h for the primary calling header

#include "VNegIntGen.h"        // For This
#include "VNegIntGen__Syms.h"


//--------------------
// STATIC VARIABLES


//--------------------

VL_CTOR_IMP(VNegIntGen) {
    VNegIntGen__Syms* __restrict vlSymsp = __VlSymsp = new VNegIntGen__Syms(this, name());
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void VNegIntGen::__Vconfigure(VNegIntGen__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

VNegIntGen::~VNegIntGen() {
    delete __VlSymsp; __VlSymsp=NULL;
}

//--------------------


void VNegIntGen::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate VNegIntGen::eval\n"); );
    VNegIntGen__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
	vlSymsp->__Vm_activity = true;
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't converge");
    }
}

void VNegIntGen::_eval_initial_loop(VNegIntGen__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    int __VclockLoop = 0;
    QData __Vchange = 1;
    while (VL_LIKELY(__Vchange)) {
	_eval_settle(vlSymsp);
	_eval(vlSymsp);
	__Vchange = _change_request(vlSymsp);
	if (VL_UNLIKELY(++__VclockLoop > 100)) VL_FATAL_MT(__FILE__,__LINE__,__FILE__,"Verilated model didn't DC converge");
    }
}

//--------------------
// Internal Methods

VL_INLINE_OPT void VNegIntGen::_sequent__TOP__1(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_sequent__TOP__1\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    VL_SIG8(__Vdly__NegIntGen__DOT__in_buffer1,3,0);
    VL_SIG8(__Vdly__NegIntGen__DOT__state,1,0);
    // Body
    __Vdly__NegIntGen__DOT__in_buffer1 = vlTOPp->NegIntGen__DOT__in_buffer1;
    __Vdly__NegIntGen__DOT__state = vlTOPp->NegIntGen__DOT__state;
    // ALWAYS at NegIntGen.v:47
    __Vdly__NegIntGen__DOT__in_buffer1 = vlTOPp->io_key_in;
    vlTOPp->NegIntGen__DOT__src1 = ((IData)(vlTOPp->reset)
				     ? 0U : (IData)(vlTOPp->NegIntGen__DOT___GEN_18));
    if (vlTOPp->reset) {
	vlTOPp->NegIntGen__DOT__left_brackets_flag = 0U;
    } else {
	if ((2U == (IData)(vlTOPp->NegIntGen__DOT__state))) {
	    vlTOPp->NegIntGen__DOT__left_brackets_flag 
		= vlTOPp->NegIntGen__DOT___GEN_14;
	}
    }
    if (vlTOPp->reset) {
	vlTOPp->NegIntGen__DOT__negative_sign = 0U;
    } else {
	if ((2U == (IData)(vlTOPp->NegIntGen__DOT__state))) {
	    if ((0xdU != (IData)(vlTOPp->NegIntGen__DOT__in_buffer1))) {
		vlTOPp->NegIntGen__DOT__negative_sign 
		    = vlTOPp->NegIntGen__DOT___GEN_12;
	    }
	}
    }
    if (vlTOPp->reset) {
	__Vdly__NegIntGen__DOT__state = 0U;
    } else {
	if (vlTOPp->NegIntGen__DOT___T_5) {
	    if (((0xaU <= (IData)(vlTOPp->io_key_in)) 
		 & (0xeU >= (IData)(vlTOPp->io_key_in)))) {
		__Vdly__NegIntGen__DOT__state = 2U;
	    } else {
		if ((0xaU > (IData)(vlTOPp->io_key_in))) {
		    __Vdly__NegIntGen__DOT__state = 1U;
		}
	    }
	} else {
	    if (vlTOPp->NegIntGen__DOT___T_6) {
		if ((0xfU == (IData)(vlTOPp->io_key_in))) {
		    __Vdly__NegIntGen__DOT__state = 3U;
		}
	    } else {
		__Vdly__NegIntGen__DOT__state = ((IData)(vlTOPp->NegIntGen__DOT___T_7)
						  ? (IData)(vlTOPp->NegIntGen__DOT___GEN_3)
						  : (IData)(vlTOPp->NegIntGen__DOT___GEN_4));
	    }
	}
    }
    vlTOPp->NegIntGen__DOT__in_buffer1 = __Vdly__NegIntGen__DOT__in_buffer1;
    vlTOPp->NegIntGen__DOT__state = __Vdly__NegIntGen__DOT__state;
    vlTOPp->NegIntGen__DOT___GEN_12 = ((0xbU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
				       | ((0xeU != (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
					  & (IData)(vlTOPp->NegIntGen__DOT__negative_sign)));
    vlTOPp->NegIntGen__DOT___GEN_14 = ((0xdU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
				       | ((0xbU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1))
					   ? (IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag)
					   : ((0xeU 
					       != (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
					      & (IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag))));
    vlTOPp->NegIntGen__DOT___T_5 = (0U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___T_6 = (1U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___T_7 = (2U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___GEN_4 = ((3U == (IData)(vlTOPp->NegIntGen__DOT__state))
				       ? 0U : (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->io_value_valid = (3U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->io_value_bits = vlTOPp->NegIntGen__DOT__src1;
    vlTOPp->NegIntGen__DOT___T_16 = (VL_ULL(0x7ffffffff) 
				     & (((QData)((IData)(vlTOPp->NegIntGen__DOT__src1)) 
					 << 3U) + ((QData)((IData)(vlTOPp->NegIntGen__DOT__src1)) 
						   << 1U)));
    vlTOPp->NegIntGen__DOT___GEN_18 = (VL_ULL(0x7ffffffff) 
				       & ((3U == (IData)(vlTOPp->NegIntGen__DOT__state))
					   ? VL_ULL(0)
					   : ((1U == (IData)(vlTOPp->NegIntGen__DOT__state))
					       ? (((IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag) 
						   & (IData)(vlTOPp->NegIntGen__DOT__negative_sign))
						   ? 
						  (vlTOPp->NegIntGen__DOT___T_16 
						   - (QData)((IData)(vlTOPp->NegIntGen__DOT__in_buffer1)))
						   : 
						  (vlTOPp->NegIntGen__DOT___T_16 
						   + (QData)((IData)(vlTOPp->NegIntGen__DOT__in_buffer1))))
					       : (QData)((IData)(vlTOPp->NegIntGen__DOT__src1)))));
}

void VNegIntGen::_settle__TOP__2(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_settle__TOP__2\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->NegIntGen__DOT___T_5 = (0U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___T_6 = (1U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___T_7 = (2U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->NegIntGen__DOT___GEN_4 = ((3U == (IData)(vlTOPp->NegIntGen__DOT__state))
				       ? 0U : (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->io_value_valid = (3U == (IData)(vlTOPp->NegIntGen__DOT__state));
    vlTOPp->io_value_bits = vlTOPp->NegIntGen__DOT__src1;
    vlTOPp->NegIntGen__DOT___GEN_3 = ((0xaU > (IData)(vlTOPp->io_key_in))
				       ? 1U : ((0xfU 
						== (IData)(vlTOPp->io_key_in))
					        ? 3U
					        : (IData)(vlTOPp->NegIntGen__DOT__state)));
    vlTOPp->NegIntGen__DOT___GEN_12 = ((0xbU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
				       | ((0xeU != (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
					  & (IData)(vlTOPp->NegIntGen__DOT__negative_sign)));
    vlTOPp->NegIntGen__DOT___GEN_14 = ((0xdU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
				       | ((0xbU == (IData)(vlTOPp->NegIntGen__DOT__in_buffer1))
					   ? (IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag)
					   : ((0xeU 
					       != (IData)(vlTOPp->NegIntGen__DOT__in_buffer1)) 
					      & (IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag))));
    vlTOPp->NegIntGen__DOT___T_16 = (VL_ULL(0x7ffffffff) 
				     & (((QData)((IData)(vlTOPp->NegIntGen__DOT__src1)) 
					 << 3U) + ((QData)((IData)(vlTOPp->NegIntGen__DOT__src1)) 
						   << 1U)));
    vlTOPp->NegIntGen__DOT___GEN_18 = (VL_ULL(0x7ffffffff) 
				       & ((3U == (IData)(vlTOPp->NegIntGen__DOT__state))
					   ? VL_ULL(0)
					   : ((1U == (IData)(vlTOPp->NegIntGen__DOT__state))
					       ? (((IData)(vlTOPp->NegIntGen__DOT__left_brackets_flag) 
						   & (IData)(vlTOPp->NegIntGen__DOT__negative_sign))
						   ? 
						  (vlTOPp->NegIntGen__DOT___T_16 
						   - (QData)((IData)(vlTOPp->NegIntGen__DOT__in_buffer1)))
						   : 
						  (vlTOPp->NegIntGen__DOT___T_16 
						   + (QData)((IData)(vlTOPp->NegIntGen__DOT__in_buffer1))))
					       : (QData)((IData)(vlTOPp->NegIntGen__DOT__src1)))));
}

VL_INLINE_OPT void VNegIntGen::_combo__TOP__3(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_combo__TOP__3\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->NegIntGen__DOT___GEN_3 = ((0xaU > (IData)(vlTOPp->io_key_in))
				       ? 1U : ((0xfU 
						== (IData)(vlTOPp->io_key_in))
					        ? 3U
					        : (IData)(vlTOPp->NegIntGen__DOT__state)));
}

void VNegIntGen::_eval(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_eval\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clock) & (~ (IData)(vlTOPp->__Vclklast__TOP__clock)))) {
	vlTOPp->_sequent__TOP__1(vlSymsp);
	vlTOPp->__Vm_traceActivity = (2U | vlTOPp->__Vm_traceActivity);
    }
    vlTOPp->_combo__TOP__3(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clock = vlTOPp->clock;
}

void VNegIntGen::_eval_initial(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_eval_initial\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VNegIntGen::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::final\n"); );
    // Variables
    VNegIntGen__Syms* __restrict vlSymsp = this->__VlSymsp;
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void VNegIntGen::_eval_settle(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_eval_settle\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData VNegIntGen::_change_request(VNegIntGen__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_change_request\n"); );
    VNegIntGen* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void VNegIntGen::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clock & 0xfeU))) {
	Verilated::overWidthError("clock");}
    if (VL_UNLIKELY((reset & 0xfeU))) {
	Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((io_key_in & 0xf0U))) {
	Verilated::overWidthError("io_key_in");}
}
#endif // VL_DEBUG

void VNegIntGen::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VNegIntGen::_ctor_var_reset\n"); );
    // Body
    clock = VL_RAND_RESET_I(1);
    reset = VL_RAND_RESET_I(1);
    io_key_in = VL_RAND_RESET_I(4);
    io_value_valid = VL_RAND_RESET_I(1);
    io_value_bits = VL_RAND_RESET_I(32);
    NegIntGen__DOT__in_buffer1 = VL_RAND_RESET_I(4);
    NegIntGen__DOT__src1 = VL_RAND_RESET_I(32);
    NegIntGen__DOT__left_brackets_flag = VL_RAND_RESET_I(1);
    NegIntGen__DOT__negative_sign = VL_RAND_RESET_I(1);
    NegIntGen__DOT__state = VL_RAND_RESET_I(2);
    NegIntGen__DOT___T_5 = VL_RAND_RESET_I(1);
    NegIntGen__DOT___T_6 = VL_RAND_RESET_I(1);
    NegIntGen__DOT___T_7 = VL_RAND_RESET_I(1);
    NegIntGen__DOT___GEN_3 = VL_RAND_RESET_I(2);
    NegIntGen__DOT___GEN_4 = VL_RAND_RESET_I(2);
    NegIntGen__DOT___T_16 = VL_RAND_RESET_Q(35);
    NegIntGen__DOT___GEN_12 = VL_RAND_RESET_I(1);
    NegIntGen__DOT___GEN_14 = VL_RAND_RESET_I(1);
    NegIntGen__DOT___GEN_18 = VL_RAND_RESET_Q(35);
    __Vclklast__TOP__clock = VL_RAND_RESET_I(1);
    __Vm_traceActivity = VL_RAND_RESET_I(32);
}
