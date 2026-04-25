// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xpvoc_synthesis.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPvoc_synthesis_CfgInitialize(XPvoc_synthesis *InstancePtr, XPvoc_synthesis_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPvoc_synthesis_Set_fft_size(XPvoc_synthesis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_synthesis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XPvoc_synthesis_Get_fft_size(XPvoc_synthesis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_synthesis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

void XPvoc_synthesis_Set_fac(XPvoc_synthesis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_synthesis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_FAC_DATA, Data);
}

u32 XPvoc_synthesis_Get_fac(XPvoc_synthesis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_synthesis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_FAC_DATA);
    return Data;
}

void XPvoc_synthesis_Set_bin_spacing(XPvoc_synthesis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_synthesis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_BIN_SPACING_DATA, Data);
}

u32 XPvoc_synthesis_Get_bin_spacing(XPvoc_synthesis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_synthesis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_BIN_SPACING_DATA);
    return Data;
}

void XPvoc_synthesis_Set_pitch_shift(XPvoc_synthesis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_synthesis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_PITCH_SHIFT_DATA, Data);
}

u32 XPvoc_synthesis_Get_pitch_shift(XPvoc_synthesis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_synthesis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_SYNTHESIS_CONTROL_ADDR_PITCH_SHIFT_DATA);
    return Data;
}

