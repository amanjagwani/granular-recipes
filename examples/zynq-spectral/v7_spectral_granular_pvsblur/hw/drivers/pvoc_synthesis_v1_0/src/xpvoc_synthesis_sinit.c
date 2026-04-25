// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xpvoc_synthesis.h"

extern XPvoc_synthesis_Config XPvoc_synthesis_ConfigTable[];

XPvoc_synthesis_Config *XPvoc_synthesis_LookupConfig(u16 DeviceId) {
	XPvoc_synthesis_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XPVOC_SYNTHESIS_NUM_INSTANCES; Index++) {
		if (XPvoc_synthesis_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XPvoc_synthesis_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XPvoc_synthesis_Initialize(XPvoc_synthesis *InstancePtr, u16 DeviceId) {
	XPvoc_synthesis_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XPvoc_synthesis_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XPvoc_synthesis_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

