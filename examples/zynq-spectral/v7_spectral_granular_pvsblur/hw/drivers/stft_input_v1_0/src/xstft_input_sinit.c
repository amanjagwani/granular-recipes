// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xstft_input.h"

extern XStft_input_Config XStft_input_ConfigTable[];

XStft_input_Config *XStft_input_LookupConfig(u16 DeviceId) {
	XStft_input_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XSTFT_INPUT_NUM_INSTANCES; Index++) {
		if (XStft_input_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XStft_input_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XStft_input_Initialize(XStft_input *InstancePtr, u16 DeviceId) {
	XStft_input_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XStft_input_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XStft_input_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

