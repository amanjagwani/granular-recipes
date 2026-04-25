// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xfft_2_i2s.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XFft_2_i2s_CfgInitialize(XFft_2_i2s *InstancePtr, XFft_2_i2s_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XFft_2_i2s_Set_fft_size(XFft_2_i2s *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XFft_2_i2s_WriteReg(InstancePtr->Control_BaseAddress, XFFT_2_I2S_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XFft_2_i2s_Get_fft_size(XFft_2_i2s *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XFft_2_i2s_ReadReg(InstancePtr->Control_BaseAddress, XFFT_2_I2S_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

