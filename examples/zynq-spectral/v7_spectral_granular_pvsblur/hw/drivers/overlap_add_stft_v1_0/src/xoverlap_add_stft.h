// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XOVERLAP_ADD_STFT_H
#define XOVERLAP_ADD_STFT_H

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
#include "xoverlap_add_stft_hw.h"

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
} XOverlap_add_stft_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XOverlap_add_stft;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XOverlap_add_stft_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XOverlap_add_stft_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XOverlap_add_stft_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XOverlap_add_stft_ReadReg(BaseAddress, RegOffset) \
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
int XOverlap_add_stft_Initialize(XOverlap_add_stft *InstancePtr, u16 DeviceId);
XOverlap_add_stft_Config* XOverlap_add_stft_LookupConfig(u16 DeviceId);
int XOverlap_add_stft_CfgInitialize(XOverlap_add_stft *InstancePtr, XOverlap_add_stft_Config *ConfigPtr);
#else
int XOverlap_add_stft_Initialize(XOverlap_add_stft *InstancePtr, const char* InstanceName);
int XOverlap_add_stft_Release(XOverlap_add_stft *InstancePtr);
#endif


void XOverlap_add_stft_Set_fft_size(XOverlap_add_stft *InstancePtr, u32 Data);
u32 XOverlap_add_stft_Get_fft_size(XOverlap_add_stft *InstancePtr);
void XOverlap_add_stft_Set_hop_size(XOverlap_add_stft *InstancePtr, u32 Data);
u32 XOverlap_add_stft_Get_hop_size(XOverlap_add_stft *InstancePtr);
void XOverlap_add_stft_Set_output_gain(XOverlap_add_stft *InstancePtr, u32 Data);
u32 XOverlap_add_stft_Get_output_gain(XOverlap_add_stft *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
