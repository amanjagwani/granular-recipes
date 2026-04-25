// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xpvoc_analysis.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XPvoc_analysis_CfgInitialize(XPvoc_analysis *InstancePtr, XPvoc_analysis_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XPvoc_analysis_Set_fft_size(XPvoc_analysis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_analysis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XPvoc_analysis_Get_fft_size(XPvoc_analysis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_analysis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

void XPvoc_analysis_Set_hop_size(XPvoc_analysis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_analysis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_HOP_SIZE_DATA, Data);
}

u32 XPvoc_analysis_Get_hop_size(XPvoc_analysis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_analysis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_HOP_SIZE_DATA);
    return Data;
}

void XPvoc_analysis_Set_sample_rate(XPvoc_analysis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_analysis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_SAMPLE_RATE_DATA, Data);
}

u32 XPvoc_analysis_Get_sample_rate(XPvoc_analysis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_analysis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_SAMPLE_RATE_DATA);
    return Data;
}

void XPvoc_analysis_Set_fac(XPvoc_analysis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_analysis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_FAC_DATA, Data);
}

u32 XPvoc_analysis_Get_fac(XPvoc_analysis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_analysis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_FAC_DATA);
    return Data;
}

void XPvoc_analysis_Set_bin_spacing(XPvoc_analysis *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XPvoc_analysis_WriteReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_BIN_SPACING_DATA, Data);
}

u32 XPvoc_analysis_Get_bin_spacing(XPvoc_analysis *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XPvoc_analysis_ReadReg(InstancePtr->Control_BaseAddress, XPVOC_ANALYSIS_CONTROL_ADDR_BIN_SPACING_DATA);
    return Data;
}

