// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XFFT_MIRROR_REPLACE_H
#define XFFT_MIRROR_REPLACE_H

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
#include "xfft_mirror_replace_hw.h"

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
} XFft_mirror_replace_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XFft_mirror_replace;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XFft_mirror_replace_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XFft_mirror_replace_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XFft_mirror_replace_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XFft_mirror_replace_ReadReg(BaseAddress, RegOffset) \
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
int XFft_mirror_replace_Initialize(XFft_mirror_replace *InstancePtr, u16 DeviceId);
XFft_mirror_replace_Config* XFft_mirror_replace_LookupConfig(u16 DeviceId);
int XFft_mirror_replace_CfgInitialize(XFft_mirror_replace *InstancePtr, XFft_mirror_replace_Config *ConfigPtr);
#else
int XFft_mirror_replace_Initialize(XFft_mirror_replace *InstancePtr, const char* InstanceName);
int XFft_mirror_replace_Release(XFft_mirror_replace *InstancePtr);
#endif


void XFft_mirror_replace_Set_fft_size(XFft_mirror_replace *InstancePtr, u32 Data);
u32 XFft_mirror_replace_Get_fft_size(XFft_mirror_replace *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
