#include "audio.h"
#include "xparameters.h"
#include "xfft_2_i2s.h"
#include "xi2s_2_mono.h"
#include "xstft_input.h"
#include "xwindow_apply.h"
#include "xspectral_buffer.h"
#include "xfft_mirror_replace.h"
#include "xoverlap_add_stft.h"
#include "xpvoc_analysis.h"
#include "xpvoc_synthesis.h"
#include "xil_cache.h"
#include "xil_io.h"
#include <math.h>
#include <string.h>
#include <stdint.h>
#include "xuartps.h"
#include "xil_printf.h"

extern "C"
{
#include "xi2stx.h"
}
}
extern "C"
{
#include "xi2srx.h"
}
}

#include "granular_recipes/spectral_engine.h"
#include "granular_recipes/recipes/spectral_drift.h"
#include "granular_recipes/recipes/spectral_disperse.h"
#include "granular_recipes/recipes/spectral_stutter.h"
#include "midi_spectral.h"

#ifndef SR
#define SR 48000
#endif
#define I2S_FS 48

static inline u32 f2u(float v)
{
	union
	{
		float f;
		u32 u;
	} c;
	c.f = v;
	return c.u;
}

constexpr uint32_t FFT_SIZE = 1024;
constexpr uint32_t HOP_SIZE = 256;
constexpr uint32_t BUFFER_DEPTH = 32;
constexpr uint32_t OUTPUT_GAIN = 0;

// Precomputed constants for pvoc analysis/synthesis (avoid float math on PL)
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
static const float ANALYSIS_FAC = (float)SR / (2.0f * M_PI * (float)HOP_SIZE);
static const float SYNTHESIS_FAC = (2.0f * M_PI * (float)HOP_SIZE) / (float)SR;
static const float BIN_SPACING = (float)SR / (float)FFT_SIZE;

// Device IDs
#define I2S_2_MONO_DEVICE_ID XPAR_I2S_2_MONO_0_DEVICE_ID
#define FFT_2_I2S_DEVICE_ID XPAR_FFT_2_I2S_0_DEVICE_ID
#define STFT_INPUT_DEVICE_ID XPAR_STFT_INPUT_0_DEVICE_ID
#define WINDOW_APPLY_0_DEVICE_ID XPAR_WINDOW_APPLY_0_DEVICE_ID
#define WINDOW_APPLY_1_DEVICE_ID XPAR_WINDOW_APPLY_1_DEVICE_ID
#define SPECTRAL_BUFFER_DEVICE_ID XPAR_SPECTRAL_BUFFER_0_DEVICE_ID
#define FFT_MIRROR_REPLACE_DEVICE_ID XPAR_XFFT_MIRROR_REPLACE_0_DEVICE_ID
#define OVERLAP_ADD_STFT_DEVICE_ID XPAR_OVERLAP_ADD_STFT_0_DEVICE_ID
#define PVOC_ANALYSIS_DEVICE_ID XPAR_PVOC_ANALYSIS_0_DEVICE_ID
#define PVOC_SYNTHESIS_DEVICE_ID XPAR_PVOC_SYNTHESIS_0_DEVICE_ID

int main()
{
	// ============================================================
	// I2S codec setup
	// ============================================================
	XI2s_Tx I2sInstance;
	XI2s_Rx I2sRxInstance;
	XI2srx_Config *RxConfig = XI2s_Rx_LookupConfig(XPAR_I2S_RECEIVER_0_DEVICE_ID);
	int Status = XI2s_Rx_CfgInitialize(&I2sRxInstance, RxConfig, RxConfig->BaseAddress);
	XI2s_Rx_SetSclkOutDiv(&I2sRxInstance, 256 * I2S_FS, I2S_FS);
	XI2s_Rx_SetChMux(&I2sRxInstance, XI2S_RX_CHID0, XI2S_RX_CHMUX_XI2S_01);
	XI2s_Rx_Enable(&I2sRxInstance, TRUE);

	XI2stx_Config *TxConfig = XI2s_Tx_LookupConfig(XPAR_I2S_TRANSMITTER_0_DEVICE_ID);
	Status = XI2s_Tx_CfgInitialize(&I2sInstance, TxConfig, TxConfig->BaseAddress);
	XI2s_Tx_SetChMux(&I2sInstance, XI2S_TX_CHID0, XI2S_TX_CHMUX_AXIS_01);
	XI2s_Tx_Enable(&I2sInstance, TRUE);

	IicConfig(XPAR_XIICPS_0_DEVICE_ID);
	AudioPllConfig();

	// ============================================================
	// HLS IP init
	// ============================================================
	XI2s_2_mono i2sMonoInstance;
	int status = XI2s_2_mono_Initialize(&i2sMonoInstance, I2S_2_MONO_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XFft_2_i2s fft2I2sInstance;
	status = XFft_2_i2s_Initialize(&fft2I2sInstance, FFT_2_I2S_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XStft_input stftInputInstance;
	status = XStft_input_Initialize(&stftInputInstance, STFT_INPUT_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XWindow_apply windowApply0;
	status = XWindow_apply_Initialize(&windowApply0, WINDOW_APPLY_0_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XWindow_apply windowApply1;
	status = XWindow_apply_Initialize(&windowApply1, WINDOW_APPLY_1_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XSpectral_buffer spectralBufferInstance;
	status = XSpectral_buffer_Initialize(&spectralBufferInstance, SPECTRAL_BUFFER_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XFft_mirror_replace mirrorReplaceInstance;
	status = XFft_mirror_replace_Initialize(&mirrorReplaceInstance, FFT_MIRROR_REPLACE_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XOverlap_add_stft overlapAddStftInstance;
	status = XOverlap_add_stft_Initialize(&overlapAddStftInstance, OVERLAP_ADD_STFT_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XPvoc_analysis pvocAnalysisInstance;
	status = XPvoc_analysis_Initialize(&pvocAnalysisInstance, PVOC_ANALYSIS_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	XPvoc_synthesis pvocSynthesisInstance;
	status = XPvoc_synthesis_Initialize(&pvocSynthesisInstance, PVOC_SYNTHESIS_DEVICE_ID);
	if (status != XST_SUCCESS)
		return XST_FAILURE;

	// ============================================================
	// Configure PL IPs
	// ============================================================
	XI2s_2_mono_Set_fft_size(&i2sMonoInstance, HOP_SIZE);
	XFft_2_i2s_Set_fft_size(&fft2I2sInstance, HOP_SIZE);
	XStft_input_Set_fft_size(&stftInputInstance, FFT_SIZE);
	XStft_input_Set_hop_size(&stftInputInstance, HOP_SIZE);
	XWindow_apply_Set_fft_size(&windowApply0, FFT_SIZE);
	XWindow_apply_Set_fft_size(&windowApply1, FFT_SIZE);
	XSpectral_buffer_Set_fft_size(&spectralBufferInstance, FFT_SIZE);
	XSpectral_buffer_Set_buffer_depth(&spectralBufferInstance, BUFFER_DEPTH);
	XSpectral_buffer_Set_read_position_lo(&spectralBufferInstance, 0);
	XSpectral_buffer_Set_read_position_mid(&spectralBufferInstance, 0);
	XSpectral_buffer_Set_read_position_hi(&spectralBufferInstance, 0);
	XSpectral_buffer_Set_blur_frames(&spectralBufferInstance, 1);
	XSpectral_buffer_Set_inv_blur(&spectralBufferInstance, f2u(1.0f));
	XFft_mirror_replace_Set_fft_size(&mirrorReplaceInstance, FFT_SIZE);
	XPvoc_analysis_Set_fft_size(&pvocAnalysisInstance, FFT_SIZE);
	XPvoc_analysis_Set_hop_size(&pvocAnalysisInstance, HOP_SIZE);
	XPvoc_analysis_Set_sample_rate(&pvocAnalysisInstance, SR);
	XPvoc_analysis_Set_fac(&pvocAnalysisInstance, f2u(ANALYSIS_FAC));
	XPvoc_analysis_Set_bin_spacing(&pvocAnalysisInstance, f2u(BIN_SPACING));
	XPvoc_synthesis_Set_fft_size(&pvocSynthesisInstance, FFT_SIZE);
	XPvoc_synthesis_Set_fac(&pvocSynthesisInstance, f2u(SYNTHESIS_FAC));
	XPvoc_synthesis_Set_bin_spacing(&pvocSynthesisInstance, f2u(BIN_SPACING));
	XPvoc_synthesis_Set_pitch_shift(&pvocSynthesisInstance, f2u(1.0f));
	XOverlap_add_stft_Set_fft_size(&overlapAddStftInstance, FFT_SIZE);
	XOverlap_add_stft_Set_hop_size(&overlapAddStftInstance, HOP_SIZE);
	XOverlap_add_stft_Set_output_gain(&overlapAddStftInstance, OUTPUT_GAIN);

	// ============================================================
	// MIDI init
	// ============================================================
	init_midi_uart();

	// ============================================================
	// Spectral engine
	// ============================================================
	gr::SpectralDriftRecipe drift;
	gr::SpectralDisperseRecipe disperse;
	gr::SpectralStutterRecipe stutter;

	gr::SpectralRecipe *recipes[NUM_RECIPES] = {&drift, &disperse, &stutter};

	gr::SpectralEngine engine;
	engine.Init(SR, HOP_SIZE, BUFFER_DEPTH, recipes, NUM_RECIPES);
	engine.SetMacro(gr::SpectralMacro::ENERGY, 0.5f);

	xil_printf("Spectral Granular — ready\n\r");

	// ============================================================
	// Main loop
	// ============================================================
	uint16_t lastWp = 0;
	constexpr uint32_t TICKS_PER_SAMPLE = 325000000 / SR;
	uint32_t lastSampleTick = 0;
	volatile uint32_t *globalTimerLo = (volatile uint32_t *)0xF8F00200;
	volatile uint32_t *globalTimerCtrl = (volatile uint32_t *)0xF8F00208;
	*globalTimerCtrl |= 0x1;
	lastSampleTick = *globalTimerLo;

	while (1)
	{
		process_midi_message(&Uart_PS, engine);

		uint32_t now = *globalTimerLo;
		if ((now - lastSampleTick) >= TICKS_PER_SAMPLE)
		{
			lastSampleTick += TICKS_PER_SAMPLE;
			engine.Process();
		}

		uint16_t wp = XSpectral_buffer_Get_write_ptr_out(&spectralBufferInstance);
		if (wp != lastWp)
		{
			lastWp = wp;
			engine.OnHop(wp);
		}

		gr::SpectralHopOutput hopOut = engine.GetOutput();
		XPvoc_synthesis_Set_pitch_shift(&pvocSynthesisInstance, f2u(hopOut.pitchRatio));
		XSpectral_buffer_Set_read_position_lo(&spectralBufferInstance, hopOut.readPositionLo);
		XSpectral_buffer_Set_read_position_mid(&spectralBufferInstance, hopOut.readPositionMid);
		XSpectral_buffer_Set_read_position_hi(&spectralBufferInstance, hopOut.readPositionHi);
		XSpectral_buffer_Set_blur_frames(&spectralBufferInstance, hopOut.blurFrames);
		XSpectral_buffer_Set_inv_blur(&spectralBufferInstance, f2u(hopOut.invBlur));
	}

	return 0;
}
