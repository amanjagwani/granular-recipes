// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfft_mirror_replace.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFft_mirror_replace_CfgInitialize(XFft_mirror_replace *InstancePtr, XFft_mirror_replace_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFft_mirror_replace_Set_fft_size(XFft_mirror_replace *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFft_mirror_replace_WriteReg(InstancePtr->Control_BaseAddress, XFFT_MIRROR_REPLACE_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XFft_mirror_replace_Get_fft_size(XFft_mirror_replace *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFft_mirror_replace_ReadReg(InstancePtr->Control_BaseAddress, XFFT_MIRROR_REPLACE_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

