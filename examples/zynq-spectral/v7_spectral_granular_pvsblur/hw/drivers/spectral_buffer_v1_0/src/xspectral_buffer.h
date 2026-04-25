// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XSPECTRAL_BUFFER_H
#define XSPECTRAL_BUFFER_H

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
#include "xspectral_buffer_hw.h"

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
} XSpectral_buffer_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XSpectral_buffer;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XSpectral_buffer_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XSpectral_buffer_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XSpectral_buffer_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XSpectral_buffer_ReadReg(BaseAddress, RegOffset) \
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
int XSpectral_buffer_Initialize(XSpectral_buffer *InstancePtr, u16 DeviceId);
XSpectral_buffer_Config* XSpectral_buffer_LookupConfig(u16 DeviceId);
int XSpectral_buffer_CfgInitialize(XSpectral_buffer *InstancePtr, XSpectral_buffer_Config *ConfigPtr);
#else
int XSpectral_buffer_Initialize(XSpectral_buffer *InstancePtr, const char* InstanceName);
int XSpectral_buffer_Release(XSpectral_buffer *InstancePtr);
#endif


void XSpectral_buffer_Set_fft_size(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_fft_size(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_buffer_depth(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_buffer_depth(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_read_position_lo(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_read_position_lo(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_read_position_mid(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_read_position_mid(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_read_position_hi(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_read_position_hi(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_blur_frames(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_blur_frames(XSpectral_buffer *InstancePtr);
void XSpectral_buffer_Set_inv_blur(XSpectral_buffer *InstancePtr, u32 Data);
u32 XSpectral_buffer_Get_inv_blur(XSpectral_buffer *InstancePtr);
u32 XSpectral_buffer_Get_write_ptr_out(XSpectral_buffer *InstancePtr);
u32 XSpectral_buffer_Get_write_ptr_out_vld(XSpectral_buffer *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
