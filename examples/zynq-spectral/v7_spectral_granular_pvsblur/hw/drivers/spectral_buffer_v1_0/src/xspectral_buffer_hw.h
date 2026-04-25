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
// 0x18 : Data signal of buffer_depth
//        bit 15~0 - buffer_depth[15:0] (Read/Write)
//        others   - reserved
// 0x1c : reserved
// 0x20 : Data signal of read_position_lo
//        bit 15~0 - read_position_lo[15:0] (Read/Write)
//        others   - reserved
// 0x24 : reserved
// 0x28 : Data signal of read_position_mid
//        bit 15~0 - read_position_mid[15:0] (Read/Write)
//        others   - reserved
// 0x2c : reserved
// 0x30 : Data signal of read_position_hi
//        bit 15~0 - read_position_hi[15:0] (Read/Write)
//        others   - reserved
// 0x34 : reserved
// 0x38 : Data signal of blur_frames
//        bit 15~0 - blur_frames[15:0] (Read/Write)
//        others   - reserved
// 0x3c : reserved
// 0x40 : Data signal of inv_blur
//        bit 31~0 - inv_blur[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of write_ptr_out
//        bit 15~0 - write_ptr_out[15:0] (Read)
//        others   - reserved
// 0x4c : Control signal of write_ptr_out
//        bit 0  - write_ptr_out_ap_vld (Read/COR)
//        others - reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XSPECTRAL_BUFFER_CONTROL_ADDR_FFT_SIZE_DATA          0x10
#define XSPECTRAL_BUFFER_CONTROL_BITS_FFT_SIZE_DATA          16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_BUFFER_DEPTH_DATA      0x18
#define XSPECTRAL_BUFFER_CONTROL_BITS_BUFFER_DEPTH_DATA      16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_LO_DATA  0x20
#define XSPECTRAL_BUFFER_CONTROL_BITS_READ_POSITION_LO_DATA  16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_MID_DATA 0x28
#define XSPECTRAL_BUFFER_CONTROL_BITS_READ_POSITION_MID_DATA 16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_READ_POSITION_HI_DATA  0x30
#define XSPECTRAL_BUFFER_CONTROL_BITS_READ_POSITION_HI_DATA  16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_BLUR_FRAMES_DATA       0x38
#define XSPECTRAL_BUFFER_CONTROL_BITS_BLUR_FRAMES_DATA       16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_INV_BLUR_DATA          0x40
#define XSPECTRAL_BUFFER_CONTROL_BITS_INV_BLUR_DATA          32
#define XSPECTRAL_BUFFER_CONTROL_ADDR_WRITE_PTR_OUT_DATA     0x48
#define XSPECTRAL_BUFFER_CONTROL_BITS_WRITE_PTR_OUT_DATA     16
#define XSPECTRAL_BUFFER_CONTROL_ADDR_WRITE_PTR_OUT_CTRL     0x4c

