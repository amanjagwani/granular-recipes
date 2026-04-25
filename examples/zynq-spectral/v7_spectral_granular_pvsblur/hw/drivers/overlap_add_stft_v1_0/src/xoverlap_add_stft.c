// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xoverlap_add_stft.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XOverlap_add_stft_CfgInitialize(XOverlap_add_stft *InstancePtr, XOverlap_add_stft_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XOverlap_add_stft_Set_fft_size(XOverlap_add_stft *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XOverlap_add_stft_WriteReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XOverlap_add_stft_Get_fft_size(XOverlap_add_stft *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XOverlap_add_stft_ReadReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

void XOverlap_add_stft_Set_hop_size(XOverlap_add_stft *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XOverlap_add_stft_WriteReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_HOP_SIZE_DATA, Data);
}

u32 XOverlap_add_stft_Get_hop_size(XOverlap_add_stft *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XOverlap_add_stft_ReadReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_HOP_SIZE_DATA);
    return Data;
}

void XOverlap_add_stft_Set_output_gain(XOverlap_add_stft *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XOverlap_add_stft_WriteReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_OUTPUT_GAIN_DATA, Data);
}

u32 XOverlap_add_stft_Get_output_gain(XOverlap_add_stft *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XOverlap_add_stft_ReadReg(InstancePtr->Control_BaseAddress, XOVERLAP_ADD_STFT_CONTROL_ADDR_OUTPUT_GAIN_DATA);
    return Data;
}

