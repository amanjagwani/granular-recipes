# Granular Recipes

A cross-platform C++ granular synthesis framework where **recipes** define how granular parameters relate to each other and evolve over time.

A recipe is like a developer-level behavioral preset. Developers implement hooks to manipulate a multi-dimensional parameter space, defining a particular textural identity for each recipe. Performers control the texture through two macros: **Energy** and **Intensity**.

## How It Works

The framework provides a granular engine (grain pool, circular buffer, windowing, utilities etc.) and a `Recipe` base class with five hooks:

```cpp
class Recipe {
public:
    virtual void Init(float sampleRate, size_t bufSize) = 0;
    virtual void UpdateParamsFromEnergy() = 0;   // Energy macro -> parameter trajectories
    virtual void UpdateParamsFromIntensity() {}   // Intensity macro -> secondary behavior
    virtual void OnSample() = 0;                 // Per-sample animation (scanning, clocks)
    virtual void OnSpawn() = 0;                  // Per-grain decisions (pitch, reverse)
};
```

Each recipe maps Energy (0-1) and Intensity (0-1) to correlated parameter trajectories, creating a musically coherent texture from a single pair of controls.

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
| **Spectral Disperse** | Per-band time-scatter      | Band spread, jitter     | Pitch shift (-12 to +24st)   |
| **Spectral Drift**    | Wandering spectral freeze  | Jitter / randomization  | Blur frames (temporal smear) |
| **Spectral Stutter**  | BPM-synced spectral glitch | Pitch shift probability | Subdivision (whole to 32nd)  |

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
        const float intens = params_.intensity;
        params_.spread = 0.5f + 0.5f * intens;
    }

    void OnSample() override {
        // Per-sample parameter animation
        params_.lookback = 0.1f;
    }

    void OnSpawn() override {
        // Per-grain modulation
        params_.pitchSt = 0.0f;
    }
};

} // namespace gr
```

To use it, add an instance to your `Recipe*` array and pass it to `Engine::Init()` — no engine changes needed:

```cpp
static gr::MyRecipe myRecipe;
static gr::Recipe *recipes[] = {&myRecipe, /* ... */};
```

## Directory Structure

```
granular-recipes/
  include/granular_recipes/       # Framework headers (zero platform dependencies)
    core/                         # Utilities: random, phasor, dc_block, subdivision_clock
    recipes/                      # Recipe headers (lush, sprinkle, cloud, stutter,
                                  #   spectral_disperse, spectral_drift, spectral_stutter)
    recipe.h                      # Recipe base class (granular)
    spectral_recipe.h             # SpectralRecipe base class
    engine.h                      # Engine orchestration + SPSC queues
    granular_processor.h          # Core grain engine
    granular_params.h             # Granular parameter struct
    spectral_params.h             # Spectral parameter struct
    grain.h, grain_pool.h         # Grain types and pool management
    circular_buffer_stereo.h      # Stereo circular buffer
    window_lut.h                  # Windowing lookup table
    fourPole.h                    # 4-pole resonant filter
    spsc_queue.h                  # Lock-free single-producer single-consumer queue
    config.h, utils.h             # Constants and math utilities
  src/                            # Framework sources
    recipes/                      # Recipe implementations (granular + spectral)
  examples/
    daisy-pod/                    # Daisy Pod hardware example
      libs/libDaisy/, libs/DaisySP/
```

## Building the Daisy Pod Example

Requires the [Daisy Toolchain](https://github.com/electro-smith/DaisyWiki/wiki/1.-Setting-Up-Your-Development-Environment).

```bash
cd examples/daisy-pod
git submodule update --init --recursive
make
make program-dfu
```

## Architecture

- **Core DSP**: Grain engine, circular buffer, window LUT, grain pool. No platform dependencies.
- **Recipe API**: `gr::Recipe` base class. Recipes use only core utilities (`gr::core::Random`, `gr::core::Phasor`, `gr::core::DcBlock`).
- **Engine**: Orchestrates recipes + granular processor + LPF + dry/wet mix. Lock-free SPSC circular buffers for thread-safe macro/recipe changes.
- **Platform Binding**: Maps hardware controls to Engine calls. The Daisy Pod example is the reference binding.
