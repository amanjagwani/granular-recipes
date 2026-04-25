// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xwindow_apply.h"

extern XWindow_apply_Config XWindow_apply_ConfigTable[];

XWindow_apply_Config *XWindow_apply_LookupConfig(u16 DeviceId) {
	XWindow_apply_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XWINDOW_APPLY_NUM_INSTANCES; Index++) {
		if (XWindow_apply_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XWindow_apply_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XWindow_apply_Initialize(XWindow_apply *InstancePtr, u16 DeviceId) {
	XWindow_apply_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XWindow_apply_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XWindow_apply_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

