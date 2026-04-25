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
// 0x18 : Data signal of fac
//        bit 31~0 - fac[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of bin_spacing
//        bit 31~0 - bin_spacing[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of pitch_shift
//        bit 31~0 - pitch_shift[31:0] (Read/Write)
// 0x2c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XPVOC_SYNTHESIS_CONTROL_ADDR_FFT_SIZE_DATA    0x10
#define XPVOC_SYNTHESIS_CONTROL_BITS_FFT_SIZE_DATA    16
#define XPVOC_SYNTHESIS_CONTROL_ADDR_FAC_DATA         0x18
#define XPVOC_SYNTHESIS_CONTROL_BITS_FAC_DATA         32
#define XPVOC_SYNTHESIS_CONTROL_ADDR_BIN_SPACING_DATA 0x20
#define XPVOC_SYNTHESIS_CONTROL_BITS_BIN_SPACING_DATA 32
#define XPVOC_SYNTHESIS_CONTROL_ADDR_PITCH_SHIFT_DATA 0x28
#define XPVOC_SYNTHESIS_CONTROL_BITS_PITCH_SHIFT_DATA 32

