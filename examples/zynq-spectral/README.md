# Zynq Spectral Granular

Real-time spectral granular processing on a **Zybo Z7-020** (Xilinx Zynq-7020 FPGA). All signal processing runs in programmable logic (PL) via custom HLS IPs. The ARM PS runs spectral recipes from the granular-recipes framework and writes control parameters to PL via AXI-Lite.

## Hardware

- **Board**: Digilent Zybo Z7-020 (XC7Z020-1CLG400C)
- **Audio codec**: SSM2603 (I2S, 48 kHz, 24-bit)
- **PL clock**: 122.88 MHz
- **MIDI**: 31250 baud via UART (PS MIO)

## Signal Flow

```
I2S RX → i2s_2_mono → stft_input → window_apply → FFT (1024-pt float)
    → fft_mirror_replace → pvoc_analysis → spectral_buffer → pvoc_synthesis
    → IFFT → window_apply → overlap_add_stft → fft_2_i2s → I2S TX
```

The PS controls `spectral_buffer` (per-band read positions, blur) and `pvoc_synthesis` (pitch shift) at runtime via AXI-Lite registers. Recipes compute these parameters from Energy and Intensity macros.

## HLS IPs

| IP                   | Function                                                          |
| -------------------- | ----------------------------------------------------------------- |
| `stft_input`         | Hop-based frame collection with overlap                           |
| `window_apply`       | Hann window (analysis + synthesis)                                |
| `fft_mirror_replace` | Conjugate symmetry enforcement                                    |
| `pvoc_analysis`      | Rectangular → polar (magnitude, frequency Hz)                     |
| `spectral_buffer`    | Spectral frame circular buffer, 3 per-band read pointers, pvsblur |
| `pvoc_synthesis`     | Polar → rectangular with pvscale bin remapping for pitch shift    |
| `overlap_add_stft`   | Overlap-add reconstruction                                        |

## Spectral Recipes

| Recipe       | Energy                       | Intensity                  |
| ------------ | ---------------------------- | -------------------------- |
| **Drift**    | Jitter (hold → random chaos) | Blur (sharp → smeared)     |
| **Disperse** | Band separation + jitter     | Pitch (-12 to +24 st)      |
| **Stutter**  | Pitch probability            | Subdivision (whole → 32nd) |

Controlled via MIDI: CC 36 = Energy, CC 37 = Intensity. Note On E1/F1/F#1 selects recipe.

## Building in Vitis 2022.2

### Prerequisites

- Vivado/Vitis 2022.2
- Zybo Z7-020 board files installed

### Open the workspace

1. Launch Vitis 2022.2
2. **File → Switch Workspace** → select `examples/zynq-spectral/`
3. **File → Import Projects** → select `examples/zynq-spectral/` → import all three projects:
   - `v7_spectral_granular_pvsblur` (platform)
   - `spectral_granular_vitis_app` (application)
   - `spectral_granular_vitis_app_system` (system)

### Rebuild the platform (first time only)

1. In the Explorer, right-click `v7_spectral_granular_pvsblur` → **Build**
2. This regenerates the BSP, FSBL, and driver headers from the XSA

### Add framework include path

1. Right-click `spectral_granular_vitis_app` → **Properties**
2. **C/C++ Build → Settings → ARM v7 g++ compiler → Directories**
3. Add include path: `${workspace_loc}/../../include`

### Add framework source files

The app needs these framework `.cpp` files compiled alongside `main.cpp`:

- `src/spectral_engine.cpp`
- `src/recipes/spectral_drift.cpp`
- `src/recipes/spectral_disperse.cpp`
- `src/recipes/spectral_stutter.cpp`

To link them:

1. Right-click `spectral_granular_vitis_app/src/` → **New → File**
2. Click **Advanced >>** → check **Link to file in the file system**
3. Browse to each `.cpp` file under `granular-recipes/src/`
4. Repeat for all four files

Alternatively, use **Paths and Symbols → Source Location → Link Folder** to link the entire `src/` directory.

### Build and run

## Parameters

| Constant       | Value | Description                 |
| -------------- | ----- | --------------------------- |
| `FFT_SIZE`     | 1024  | STFT frame size             |
| `HOP_SIZE`     | 256   | STFT hop (75% overlap)      |
| `BUFFER_DEPTH` | 32    | Spectral frame buffer depth |
| `SR`           | 48000 | Sample rate                 |

These are set in `main.cpp` and written to PL IPs at startup via AXI-Lite.
