// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XI2S_2_MONO_H
#define XI2S_2_MONO_H

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
#include "xi2s_2_mono_hw.h"

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
} XI2s_2_mono_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XI2s_2_mono;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XI2s_2_mono_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XI2s_2_mono_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XI2s_2_mono_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XI2s_2_mono_ReadReg(BaseAddress, RegOffset) \
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
int XI2s_2_mono_Initialize(XI2s_2_mono *InstancePtr, u16 DeviceId);
XI2s_2_mono_Config* XI2s_2_mono_LookupConfig(u16 DeviceId);
int XI2s_2_mono_CfgInitialize(XI2s_2_mono *InstancePtr, XI2s_2_mono_Config *ConfigPtr);
#else
int XI2s_2_mono_Initialize(XI2s_2_mono *InstancePtr, const char* InstanceName);
int XI2s_2_mono_Release(XI2s_2_mono *InstancePtr);
#endif


void XI2s_2_mono_Set_fft_size(XI2s_2_mono *InstancePtr, u32 Data);
u32 XI2s_2_mono_Get_fft_size(XI2s_2_mono *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
