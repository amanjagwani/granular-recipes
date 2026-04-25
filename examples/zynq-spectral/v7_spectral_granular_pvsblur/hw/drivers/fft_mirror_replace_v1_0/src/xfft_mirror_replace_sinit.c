// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xfft_mirror_replace.h"

extern XFft_mirror_replace_Config XFft_mirror_replace_ConfigTable[];

XFft_mirror_replace_Config *XFft_mirror_replace_LookupConfig(u16 DeviceId) {
	XFft_mirror_replace_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XFFT_MIRROR_REPLACE_NUM_INSTANCES; Index++) {
		if (XFft_mirror_replace_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XFft_mirror_replace_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XFft_mirror_replace_Initialize(XFft_mirror_replace *InstancePtr, u16 DeviceId) {
	XFft_mirror_replace_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XFft_mirror_replace_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XFft_mirror_replace_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

