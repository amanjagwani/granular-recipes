#pragma once
#include <cstdint>
#include <algorithm>
#include <array>
#include <cmath>
#include "daisy_pod.h"
#include "granular_recipes/engine.h"

class Hardware
{
public:
    enum class Page : uint8_t
    {
        MIXGRANMIX,
        ENERGYINTENSITY,
        CUTOFFRES,
        COUNT
    };

    void Init();
    void Poll(gr::Engine &engine);

    daisy::DaisyPod &Pod() { return pod_; }

private:
    daisy::DaisyPod pod_;

    Page currentPage_{Page::MIXGRANMIX};
    Page prevPage_{Page::MIXGRANMIX};

    float pot1_{0.f}, pot2_{0.f};
    float prevPot1_{0.f}, prevPot2_{0.f};

    static inline void macrosForPage(Page page, gr::Macro &macro1, gr::Macro &macro2);
    void applyPotsToEngine(gr::Engine &engine);
    void updateLeds(gr::Engine &engine);
    void handleMidi_(daisy::MidiEvent &msg, gr::Engine &engine);
};
