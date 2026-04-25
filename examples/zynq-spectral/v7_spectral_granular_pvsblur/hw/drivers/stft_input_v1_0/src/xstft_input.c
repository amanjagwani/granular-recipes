// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xstft_input.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XStft_input_CfgInitialize(XStft_input *InstancePtr, XStft_input_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XStft_input_Set_fft_size(XStft_input *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStft_input_WriteReg(InstancePtr->Control_BaseAddress, XSTFT_INPUT_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XStft_input_Get_fft_size(XStft_input *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStft_input_ReadReg(InstancePtr->Control_BaseAddress, XSTFT_INPUT_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

void XStft_input_Set_hop_size(XStft_input *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XStft_input_WriteReg(InstancePtr->Control_BaseAddress, XSTFT_INPUT_CONTROL_ADDR_HOP_SIZE_DATA, Data);
}

u32 XStft_input_Get_hop_size(XStft_input *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XStft_input_ReadReg(InstancePtr->Control_BaseAddress, XSTFT_INPUT_CONTROL_ADDR_HOP_SIZE_DATA);
    return Data;
}

