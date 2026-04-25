// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XPVOC_SYNTHESIS_H
#define XPVOC_SYNTHESIS_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xpvoc_synthesis_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XPvoc_synthesis_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XPvoc_synthesis;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XPvoc_synthesis_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XPvoc_synthesis_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XPvoc_synthesis_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XPvoc_synthesis_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XPvoc_synthesis_Initialize(XPvoc_synthesis *InstancePtr, u16 DeviceId);
XPvoc_synthesis_Config* XPvoc_synthesis_LookupConfig(u16 DeviceId);
int XPvoc_synthesis_CfgInitialize(XPvoc_synthesis *InstancePtr, XPvoc_synthesis_Config *ConfigPtr);
#else
int XPvoc_synthesis_Initialize(XPvoc_synthesis *InstancePtr, const char* InstanceName);
int XPvoc_synthesis_Release(XPvoc_synthesis *InstancePtr);
#endif


void XPvoc_synthesis_Set_fft_size(XPvoc_synthesis *InstancePtr, u32 Data);
u32 XPvoc_synthesis_Get_fft_size(XPvoc_synthesis *InstancePtr);
void XPvoc_synthesis_Set_fac(XPvoc_synthesis *InstancePtr, u32 Data);
u32 XPvoc_synthesis_Get_fac(XPvoc_synthesis *InstancePtr);
void XPvoc_synthesis_Set_bin_spacing(XPvoc_synthesis *InstancePtr, u32 Data);
u32 XPvoc_synthesis_Get_bin_spacing(XPvoc_synthesis *InstancePtr);
void XPvoc_synthesis_Set_pitch_shift(XPvoc_synthesis *InstancePtr, u32 Data);
u32 XPvoc_synthesis_Get_pitch_shift(XPvoc_synthesis *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
