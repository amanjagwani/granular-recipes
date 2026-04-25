#ifndef MIDI_SPECTRAL_H
#define MIDI_SPECTRAL_H

#include "xuartps.h"
#include "granular_recipes/spectral_engine.h"
#include "xil_printf.h"

#define UART_DEVICE_ID XPAR_XUARTPS_0_DEVICE_ID
#define UART_BAUD_RATE 31250

#define CC_ENERGY 36
#define CC_INTENSITY 37

#define NOTE_DRIFT 40    // E1
#define NOTE_DISPERSE 41 // F1
#define NOTE_STUTTER 42  // F#1

#define NUM_RECIPES 3

XUartPs Uart_PS;

void init_midi_uart()
{
    XUartPs_Config *uConfig = XUartPs_LookupConfig(UART_DEVICE_ID);
    if (uConfig == NULL)
    {
        xil_printf("Error finding UART configuration\n\r");
        return;
    }

    int uStatus = XUartPs_CfgInitialize(&Uart_PS, uConfig, uConfig->BaseAddress);
    if (uStatus != XST_SUCCESS)
    {
        xil_printf("Error initializing UART\n\r");
        return;
    }

    XUartPs_SetBaudRate(&Uart_PS, UART_BAUD_RATE);
    xil_printf("MIDI UART initialized at %d baud\n\r", UART_BAUD_RATE);
}

void process_midi_message(XUartPs *uart_instance, gr::SpectralEngine &engine)
{
    static uint8_t running_status = 0;
    static uint8_t data_bytes[2] = {0};
    static uint8_t data_count = 0;

    while (XUartPs_IsReceiveData(uart_instance->Config.BaseAddress))
    {
        uint8_t byte = XUartPs_ReadReg(uart_instance->Config.BaseAddress, XUARTPS_FIFO_OFFSET);

        if (byte & 0x80)
        {
            if ((byte >= 0x80) && (byte < 0xF0))
            {
                running_status = byte;
                data_count = 0;
            }
        }
        else
        {
            if (running_status == 0)
                continue;

            data_bytes[data_count++] = byte;

            int expected = 0;
            switch (running_status & 0xF0)
            {
            case 0x80:
            case 0x90:
            case 0xB0:
            case 0xE0:
                expected = 2;
                break;
            case 0xC0:
            case 0xD0:
                expected = 1;
                break;
            default:
                expected = 0;
                break;
            }

            if (expected > 0 && data_count >= expected)
            {
                uint8_t status = running_status & 0xF0;

                if (status == 0x90 && data_bytes[1] > 0)
                {
                    int note = data_bytes[0];
                    int newIdx = -1;

                    if (note == NOTE_DRIFT)
                        newIdx = 0;
                    else if (note == NOTE_DISPERSE)
                        newIdx = 1;
                    else if (note == NOTE_STUTTER)
                        newIdx = 2;

                    if (newIdx >= 0 && newIdx != (int)engine.GetRecipeIndex())
                    {
                        engine.SetRecipe(newIdx);
                        xil_printf("Recipe: %d\n\r", newIdx);
                    }
                }
                else if (status == 0xB0)
                {
                    int cc_number = data_bytes[0];
                    int cc_value = data_bytes[1];
                    float normalized = (float)cc_value / 127.0f;

                    if (cc_number == CC_ENERGY)
                    {
                        engine.SetMacro(gr::SpectralMacro::ENERGY, normalized);
                    }
                    else if (cc_number == CC_INTENSITY)
                    {
                        engine.SetMacro(gr::SpectralMacro::INTENSITY, normalized);
                    }
                }

                data_count = 0;
            }
        }
    }
}

#endif
