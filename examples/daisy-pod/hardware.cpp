#include "hardware.h"

void Hardware::Init()
{
    pod_.Init();
    pod_.SetAudioSampleRate(daisy::SaiHandle::Config::SampleRate::SAI_48KHZ);
    pod_.SetAudioBlockSize(256);
    pod_.StartAdc();

    pod_.midi.StartReceive();

    pod_.ClearLeds();
    pod_.UpdateLeds();
}

inline void Hardware::macrosForPage(Page page, gr::Macro &macro1, gr::Macro &macro2)
{
    switch (page)
    {
    case Page::MIXGRANMIX:
        macro1 = gr::Macro::MIX;
        macro2 = gr::Macro::GRANMIX;
        break;

    case Page::ENERGYINTENSITY:
        macro1 = gr::Macro::ENERGY;
        macro2 = gr::Macro::INTENSITY;
        break;

    case Page::CUTOFFRES:
        macro1 = gr::Macro::CUTOFF;
        macro2 = gr::Macro::RESONANCE;
        break;
    }
}

void Hardware::applyPotsToEngine(gr::Engine &engine)
{
    gr::Macro macro1 = gr::Macro::MIX, macro2 = gr::Macro::GRANMIX;
    Hardware::macrosForPage(currentPage_, macro1, macro2);
    if (std::abs(pot1_ - prevPot1_) > 0.01f)
    {
        engine.SetMacro(macro1, pot1_);
        prevPot1_ = pot1_;
    }

    if (std::abs(pot2_ - prevPot2_) > 0.01f)
    {
        engine.SetMacro(macro2, pot2_);
        prevPot2_ = pot2_;
    }
}

void Hardware::Poll(gr::Engine &engine)
{
    pod_.ProcessAnalogControls();
    pod_.ProcessDigitalControls();

    pot1_ = pod_.GetKnobValue(daisy::DaisyPod::KNOB_1);
    pot2_ = pod_.GetKnobValue(daisy::DaisyPod::KNOB_2);

    if (pod_.encoder.RisingEdge())
    {
        size_t next = (engine.GetRecipeIndex() + 1) % engine.GetNumRecipes();
        engine.SetRecipe(next);
    }

    const int inc = pod_.encoder.Increment();
    if (inc != 0)
    {
        const int current = static_cast<int>(currentPage_);
        const int count = static_cast<int>(Page::COUNT);
        const int next = (current + inc + count) % count;
        currentPage_ = static_cast<Page>(next);
    }

    pod_.midi.Listen();
    while (pod_.midi.HasEvents())
    {
        auto msg = pod_.midi.PopEvent();
        handleMidi_(msg, engine);
    }

    applyPotsToEngine(engine);
    updateLeds(engine);
    pod_.UpdateLeds();
}

void Hardware::handleMidi_(daisy::MidiEvent &msg, gr::Engine &engine)
{
    switch (msg.type)
    {
    case daisy::ControlChange:
    {
        auto cc = msg.AsControlChange();
        const float val = cc.value / 127.0f;
        switch (cc.control_number)
        {
        case 32: engine.SetMacro(gr::Macro::MIX, val); break;
        case 33: engine.SetMacro(gr::Macro::CUTOFF, val); break;
        case 34: engine.SetMacro(gr::Macro::RESONANCE, val); break;
        case 36: engine.SetMacro(gr::Macro::ENERGY, val); break;
        case 37: engine.SetMacro(gr::Macro::INTENSITY, val); break;
        }
        break;
    }
    case daisy::NoteOn:
    {
        auto note = msg.AsNoteOn();
        if (note.velocity > 0)
        {
            size_t next = (engine.GetRecipeIndex() + 1) % engine.GetNumRecipes();
            engine.SetRecipe(next);
        }
        break;
    }
    default:
        break;
    }
}

void Hardware::updateLeds(gr::Engine &engine)
{
    switch (engine.GetRecipeIndex())
    {
    case 0:
        pod_.led1.Set(0.0f, 0.0f, 1.0f);
        break; // blue
    case 1:
        pod_.led1.Set(1.0f, 0.0f, 0.0f);
        break; // red
    case 2:
        pod_.led1.Set(0.6f, 0.0f, 1.0f);
        break; // purple
    case 3:
        pod_.led1.Set(1.0f, 1.0f, 0.0f);
        break; // yellow
    default:
        pod_.led1.Set(0.0f, 0.0f, 0.0f);
        break; // off
    }

    switch (currentPage_)
    {
    case Page::MIXGRANMIX:
        pod_.led2.Set(1.0f, 1.0f, 1.0f);
        break; // white
    case Page::ENERGYINTENSITY:
        pod_.led2.Set(1.0f, 0.0f, 1.0f);
        break; // magenta
    case Page::CUTOFFRES:
        pod_.led2.Set(0.0f, 1.0f, 1.0f);
        break; // cyan
    default:
        pod_.led2.Set(0.0f, 0.0f, 0.0f);
        break; // off
    }
}
