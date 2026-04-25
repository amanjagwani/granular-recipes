// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xspectral_buffer.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XSpectral_buffer_CfgInitialize(XSpectral_buffer *InstancePtr, XSpectral_buffer_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XSpectral_buffer_Set_fft_size(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_FFT_SIZE_DATA, Data);
}

u32 XSpectral_buffer_Get_fft_size(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_FFT_SIZE_DATA);
    return Data;
}

void XSpectral_buffer_Set_buffer_depth(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_BUFFER_DEPTH_DATA, Data);
}

u32 XSpectral_buffer_Get_buffer_depth(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_BUFFER_DEPTH_DATA);
    return Data;
}

void XSpectral_buffer_Set_read_position_lo(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_LO_DATA, Data);
}

u32 XSpectral_buffer_Get_read_position_lo(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_LO_DATA);
    return Data;
}

void XSpectral_buffer_Set_read_position_mid(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_MID_DATA, Data);
}

u32 XSpectral_buffer_Get_read_position_mid(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_MID_DATA);
    return Data;
}

void XSpectral_buffer_Set_read_position_hi(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_HI_DATA, Data);
}

u32 XSpectral_buffer_Get_read_position_hi(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_HI_DATA);
    return Data;
}

void XSpectral_buffer_Set_blur_frames(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_BLUR_FRAMES_DATA, Data);
}

u32 XSpectral_buffer_Get_blur_frames(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_BLUR_FRAMES_DATA);
    return Data;
}

void XSpectral_buffer_Set_inv_blur(XSpectral_buffer *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XSpectral_buffer_WriteReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_INV_BLUR_DATA, Data);
}

u32 XSpectral_buffer_Get_inv_blur(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_INV_BLUR_DATA);
    return Data;
}

u32 XSpectral_buffer_Get_write_ptr_out(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_WRITE_PTR_OUT_DATA);
    return Data;
}

u32 XSpectral_buffer_Get_write_ptr_out_vld(XSpectral_buffer *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XSpectral_buffer_ReadReg(InstancePtr->Control_BaseAddress, XSPECTRAL_BUFFER_CONTROL_ADDR_WRITE_PTR_OUT_CTRL);
    return Data & 0x1;
}

