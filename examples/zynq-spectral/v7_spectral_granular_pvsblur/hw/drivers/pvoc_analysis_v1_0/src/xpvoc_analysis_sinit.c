// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xpvoc_analysis.h"

extern XPvoc_analysis_Config XPvoc_analysis_ConfigTable[];

XPvoc_analysis_Config *XPvoc_analysis_LookupConfig(u16 DeviceId) {
	XPvoc_analysis_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XPVOC_ANALYSIS_NUM_INSTANCES; Index++) {
		if (XPvoc_analysis_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XPvoc_analysis_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XPvoc_analysis_Initialize(XPvoc_analysis *InstancePtr, u16 DeviceId) {
	XPvoc_analysis_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XPvoc_analysis_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XPvoc_analysis_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

