// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSTFT_INPUT_H
#define XSTFT_INPUT_H

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
#include "xstft_input_hw.h"

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
} XStft_input_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XStft_input;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XStft_input_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XStft_input_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XStft_input_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XStft_input_ReadReg(BaseAddress, RegOffset) \
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
int XStft_input_Initialize(XStft_input *InstancePtr, u16 DeviceId);
XStft_input_Config* XStft_input_LookupConfig(u16 DeviceId);
int XStft_input_CfgInitialize(XStft_input *InstancePtr, XStft_input_Config *ConfigPtr);
#else
int XStft_input_Initialize(XStft_input *InstancePtr, const char* InstanceName);
int XStft_input_Release(XStft_input *InstancePtr);
#endif


void XStft_input_Set_fft_size(XStft_input *InstancePtr, u32 Data);
u32 XStft_input_Get_fft_size(XStft_input *InstancePtr);
void XStft_input_Set_hop_size(XStft_input *InstancePtr, u32 Data);
u32 XStft_input_Get_hop_size(XStft_input *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
