// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xi2s_2_mono.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XI2s_2_mono_CfgInitialize(XI2s_2_mono *InstancePtr, XI2s_2_mono_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XI2s_2_mono_Set_fft_size(XI2s_2_mono *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XI2s_2_mono_WriteReg(InstancePtr->Control_BaseAddress, XI2S_2_MONO_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XI2s_2_mono_Get_fft_size(XI2s_2_mono *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XI2s_2_mono_ReadReg(InstancePtr->Control_BaseAddress, XI2S_2_MONO_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

