// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2023 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of fft_size
//        bit 15~0 - fft_size[15:0] (Read/Write)
//        others   - reserved
// 0x14 : reserved
// 0x18 : Data signal of hop_size
//        bit 15~0 - hop_size[15:0] (Read/Write)
//        others   - reserved
// 0x1c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XSTFT_INPUT_CONTROL_ADDR_FFT_SIZE_DATA 0x10
#define XSTFT_INPUT_CONTROL_BITS_FFT_SIZE_DATA 16
#define XSTFT_INPUT_CONTROL_ADDR_HOP_SIZE_DATA 0x18
#define XSTFT_INPUT_CONTROL_BITS_HOP_SIZE_DATA 16

