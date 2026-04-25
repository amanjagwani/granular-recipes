// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xoverlap_add_stft.h"

extern XOverlap_add_stft_Config XOverlap_add_stft_ConfigTable[];

XOverlap_add_stft_Config *XOverlap_add_stft_LookupConfig(u16 DeviceId) {
	XOverlap_add_stft_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XOVERLAP_ADD_STFT_NUM_INSTANCES; Index++) {
		if (XOverlap_add_stft_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XOverlap_add_stft_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XOverlap_add_stft_Initialize(XOverlap_add_stft *InstancePtr, u16 DeviceId) {
	XOverlap_add_stft_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XOverlap_add_stft_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XOverlap_add_stft_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

