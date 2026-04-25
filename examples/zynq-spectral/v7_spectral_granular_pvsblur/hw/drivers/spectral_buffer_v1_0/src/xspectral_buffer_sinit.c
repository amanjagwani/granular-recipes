// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xspectral_buffer.h"

extern XSpectral_buffer_Config XSpectral_buffer_ConfigTable[];

XSpectral_buffer_Config *XSpectral_buffer_LookupConfig(u16 DeviceId) {
	XSpectral_buffer_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSPECTRAL_BUFFER_NUM_INSTANCES; Index++) {
		if (XSpectral_buffer_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XSpectral_buffer_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XSpectral_buffer_Initialize(XSpectral_buffer *InstancePtr, u16 DeviceId) {
	XSpectral_buffer_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XSpectral_buffer_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XSpectral_buffer_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

