// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xfft_2_i2s.h"

extern XFft_2_i2s_Config XFft_2_i2s_ConfigTable[];

XFft_2_i2s_Config *XFft_2_i2s_LookupConfig(u16 DeviceId) {
	XFft_2_i2s_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFFT_2_I2S_NUM_INSTANCES; Index++) {
		if (XFft_2_i2s_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFft_2_i2s_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFft_2_i2s_Initialize(XFft_2_i2s *InstancePtr, u16 DeviceId) {
	XFft_2_i2s_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFft_2_i2s_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFft_2_i2s_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

