#include "daisysp.h"
#include "granular_recipes/engine.h"
#include "granular_recipes/recipes/lush.h"
#include "granular_recipes/recipes/sprinkle.h"
#include "granular_recipes/recipes/cloud.h"
#include "granular_recipes/recipes/stutter.h"
#include "hardware.h"

using namespace daisy;
using namespace daisysp;

// Circular buffer in external SDRAM
static constexpr size_t kCircularBufferSize = 1u << 18;
DSY_SDRAM_BSS static float gCircularBufferL[kCircularBufferSize];
DSY_SDRAM_BSS static float gCircularBufferR[kCircularBufferSize];

// Grain pool and window LUT (internal SRAM is fine for these)
static constexpr size_t kMaxGrains = 64;
static constexpr size_t kWindowSize = 1024;
static gr::Grain gGrainPool[kMaxGrains];
static float gWindowLut[kWindowSize];

// Recipe instances
static gr::LushRecipe gLush;
static gr::SprinkleRecipe gSprinkle;
static gr::CloudRecipe gCloud;
static gr::StutterRecipe gStutter;
static gr::Recipe *gRecipes[] = {&gLush, &gSprinkle, &gCloud, &gStutter};
static constexpr size_t kNumRecipes = sizeof(gRecipes) / sizeof(gRecipes[0]);

static Hardware hardware;
static gr::Engine engine;

static void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	engine.OnBlock(size);

	for (size_t i = 0; i < size; ++i)
	{
		float l, r;
		engine.Process(in[0][i], in[1][i], l, r);
		out[0][i] = l;
		out[1][i] = r;
	}
}

int main(void)
{
	hardware.Init();

	// Init engine at the Pod sample rate, passing all buffers
	const float sr = hardware.Pod().AudioSampleRate();
	engine.Init(sr, gCircularBufferL, gCircularBufferR, kCircularBufferSize,
	            gGrainPool, kMaxGrains, gWindowLut, kWindowSize,
	            gRecipes, kNumRecipes);

	hardware.Pod().StartAudio(AudioCallback);

	while (true)
	{
		hardware.Poll(engine);
	}
}
