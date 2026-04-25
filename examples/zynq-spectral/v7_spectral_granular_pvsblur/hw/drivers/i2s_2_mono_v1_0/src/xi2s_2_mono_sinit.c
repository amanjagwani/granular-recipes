// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xi2s_2_mono.h"

extern XI2s_2_mono_Config XI2s_2_mono_ConfigTable[];

XI2s_2_mono_Config *XI2s_2_mono_LookupConfig(u16 DeviceId) {
	XI2s_2_mono_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XI2S_2_MONO_NUM_INSTANCES; Index++) {
		if (XI2s_2_mono_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XI2s_2_mono_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XI2s_2_mono_Initialize(XI2s_2_mono *InstancePtr, u16 DeviceId) {
	XI2s_2_mono_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XI2s_2_mono_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XI2s_2_mono_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

