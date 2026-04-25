# Granular Recipes

A cross-platform C++ granular synthesis framework where **recipes** define how granular parameters relate to each other and evolve over time.

A recipe is like a developer-level behavioral preset. Developers implement hooks to manipulate a multi-dimensional parameter space, defining a particular textural identity for each recipe. Performers control the texture through two macros: **Energy** and **Intensity**.

The framework supports two processing domains:

- **Granular** (time-domain) — grain-based synthesis with a circular buffer, grain pool, and windowing engine
- **Spectral** (frequency-domain) — STFT-based processing with per-band frame buffer control, phase vocoder analysis/synthesis, and temporal blur

## How It Works

### Granular Recipes

The granular engine provides a grain pool, circular buffer, windowing, and utilities. The `Recipe` base class has five hooks:

```cpp
class Recipe {
public:
    virtual void Init(float sampleRate, size_t bufSize) = 0;
    virtual void UpdateParamsFromEnergy() = 0;
    virtual void UpdateParamsFromIntensity() {}
    virtual void OnSample() = 0;    // Per-sample animation
    virtual void OnSpawn() = 0;     // Per-grain decisions
};
```

### Spectral Recipes

Spectral recipes operate on STFT frames rather than audio samples. The `SpectralRecipe` base class:

```cpp
class SpectralRecipe {
public:
    virtual void Init(float sr, uint32_t hopSize, uint32_t bufferDepth) = 0;
    virtual void UpdateParamsFromEnergy() = 0;
    virtual void UpdateParamsFromIntensity() {}
    virtual void OnHop() = 0;       // Per-STFT-frame
    virtual void OnSample() {}      // Per-sample smooth modulation
};
```

## Included Recipes

### Granular

| Recipe       | Character                  | Energy Controls                        | Intensity Controls                                     |
| ------------ | -------------------------- | -------------------------------------- | ------------------------------------------------------ |
| **Lush**     | Evolving harmonic clouds   | Grain size, density, jitter            | Scan rate/center/depth, feedback, pitch (fifths→stack) |
| **Sprinkle** | Percussive droplets        | Grain size, density, density jitter    | Spread, hold rate, position depth, reverse, pitch      |
| **Cloud**    | Dense swirling texture     | Grain size, density, jitter, scan rate | Stereo spread, scan depth                              |
| **Stutter**  | BPM-synced rhythmic glitch | Grain size, density                    | Subdivision (whole to 32nd)                            |

### Spectral

| Recipe                | Character                  | Energy Controls         | Intensity Controls           |
| --------------------- | -------------------------- | ----------------------- | ---------------------------- |
| **Spectral Drift**    | Wandering spectral freeze  | Jitter / randomization  | Blur frames (temporal smear) |
| **Spectral Disperse** | Per-band time-scatter      | Band spread, jitter     | Pitch shift (-12 to +24st)   |
| **Spectral Stutter**  | BPM-synced spectral glitch | Pitch shift probability | Subdivision (whole to 32nd)  |

## Engines

### Engine (Granular)

Orchestrates granular recipes: manages the grain processor, 4-pole resonant filter, dry/wet mixing, and lock-free macro/recipe switching. Provides `OnBlock()` + `Process()` called from an audio callback.

### SpectralEngine

Orchestrates spectral recipes for FPGA or other STFT platforms. Manages recipe switching and macro routing. Three methods:

- `OnHop(writePtr)` — called per spectral frame, drains queues, delegates to recipe
- `Process()` — called at audio rate, delegates per-sample modulation
- `GetOutput()` — snapshots current params into a `SpectralHopOutput` struct for the platform to write to hardware

## Buffer Injection

The framework does not allocate memory internally. The caller declares all buffers at the application level and passes them to the engine at init time. This keeps the framework safe for bare-metal targets as well.

```cpp
#include "granular_recipes/engine.h"

// Decide sizes for your platform
// Circular buffer size must be a power of 2 for efficient index wrapping
static constexpr size_t kBufSize    = 1u << 18;
static constexpr size_t kMaxGrains  = 64;
static constexpr size_t kWindowSize = 1024;

// Declare buffers (use SDRAM, SRAM, or static as appropriate)
static float circBufL[kBufSize];
static float circBufR[kBufSize];
static gr::Grain grainPool[kMaxGrains];
static float windowLut[kWindowSize];

// Instantiate recipes and build a pointer array
static gr::LushRecipe lush;
static gr::SprinkleRecipe sprinkle;
static gr::Recipe *recipes[] = {&lush, &sprinkle};
static constexpr size_t kNumRecipes = sizeof(recipes) / sizeof(recipes[0]);

static gr::Engine engine;

void setup(float sampleRate)
{
    engine.Init(sampleRate,
                circBufL, circBufR, kBufSize,
                grainPool, kMaxGrains,
                windowLut, kWindowSize,
                recipes, kNumRecipes);
}
```

## Creating a Custom Recipe

```cpp
#include "granular_recipes/recipe.h"

namespace gr {

class MyRecipe : public Recipe {
public:
    void Init(float sr, size_t bufSize) override {
        Recipe::Init(sr, bufSize);
        params_.grainSizeS = 0.1f;
        params_.densityHz = 15.0f;
        params_.gain = 0.8f;
    }

    void UpdateParamsFromEnergy() override {
        const float e = params_.energy;
        params_.grainSizeS = 0.3f - 0.25f * e;
        params_.densityHz = 5.0f + 40.0f * e;
    }

    void UpdateParamsFromIntensity() override {
        params_.spread = 0.5f + 0.5f * params_.intensity;
    }

    void OnSample() override { params_.lookback = 0.1f; }
    void OnSpawn() override { params_.pitchSt = 0.0f; }
};

} // namespace gr
```

## Examples

### Daisy Pod (Granular)

Time-domain granular synthesis on the [Daisy Pod](https://www.electro-smith.com/daisy/pod) hardware. Audio callback processes grains in real-time. Knobs, encoder, and MIDI control recipes and macros.

```bash
cd examples/daisy-pod
git submodule update --init --recursive
make
make program-dfu
```

### Zynq Spectral (FPGA)

Real-time spectral granular processing on a Zybo Z7-020 (Xilinx Zynq-7020). All signal processing runs in programmable logic via custom HLS IPs:

- **STFT pipeline**: `stft_input` → `window_apply` → FFT → `fft_mirror_replace` → `pvoc_analysis` → `spectral_buffer` → `pvoc_synthesis` → IFFT → `overlap_add_stft`
- **pvoc_analysis/synthesis**: Phase vocoder.
- **spectral_buffer**: Circular frame buffer with 3 per-band read pointers and pvsblur (temporal averaging of magnitude + frequency).
- **PS app**: ARM runs `SpectralEngine` + spectral recipes, writes control params to PL via AXI-Lite each hop.

See [`examples/zynq-spectral/README.md`](examples/zynq-spectral/README.md) for build instructions.

## Directory Structure

```
granular-recipes/
  include/granular_recipes/       # Framework headers (zero platform dependencies)
    core/                         # Utilities: random, phasor, dc_block, subdivision_clock
    recipes/                      # Recipe headers (granular + spectral)
    recipe.h                      # Recipe base class (granular)
    spectral_recipe.h             # SpectralRecipe base class
    engine.h                      # Granular engine orchestration
    spectral_engine.h             # Spectral engine orchestration
    granular_params.h             # Granular parameter struct
    spectral_params.h             # Spectral parameter struct
    granular_processor.h          # Core grain engine
    grain.h, grain_pool.h         # Grain types and pool management
    circular_buffer_stereo.h      # Stereo circular buffer
    window_lut.h                  # Windowing lookup table
    fourPole.h                    # 4-pole resonant filter
    spsc_queue.h                  # Lock-free SPSC circular buffer
    config.h, utils.h             # Constants and math utilities
  src/                            # Framework sources
    recipes/                      # Recipe implementations (granular + spectral)
  examples/
    daisy-pod/                    # Daisy Pod hardware example (granular)
    zynq-spectral/                # Zybo Z7-020 FPGA example (spectral)
```

## Architecture

- **Time-domain DSP**: Grain engine, circular buffer, window LUT, grain pool. No platform dependencies.
- **Spectral DSP**: Phase vocoder analysis/synthesis, spectral frame buffer, temporal blur. Runs on FPGA PL, controlled by PS.
- **Recipe API**: `gr::Recipe` (granular) and `gr::SpectralRecipe` (spectral). Recipes use only core utilities.
- **Engines**: `gr::Engine` (granular) and `gr::SpectralEngine` (spectral). Lock-free SPSC circular buffers for thread-safe macro/recipe changes.
- **Platform Binding**: Maps hardware controls to engine calls. See `examples/` for reference bindings.
