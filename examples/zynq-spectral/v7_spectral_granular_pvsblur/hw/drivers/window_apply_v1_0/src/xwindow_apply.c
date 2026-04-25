// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xwindow_apply.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XWindow_apply_CfgInitialize(XWindow_apply *InstancePtr, XWindow_apply_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XWindow_apply_Set_fft_size(XWindow_apply *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XWindow_apply_WriteReg(InstancePtr->Control_BaseAddress, XWINDOW_APPLY_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XWindow_apply_Get_fft_size(XWindow_apply *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XWindow_apply_ReadReg(InstancePtr->Control_BaseAddress, XWINDOW_APPLY_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

