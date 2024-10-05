#pragma once

#include <cstdlib>
#include <iostream> // Include <iostream> for std::cout
#include <portaudio.h>

static void checkErr(PaError err) {
    if (err != paNoError) {
        std::cout << "PortAudio error: " << Pa_GetErrorText(err) << std::endl;
        exit(EXIT_FAILURE);
    }
}

static int paCallback(const void* inputBuffer, void* outputBuffer, unsigned long framesPerBuffer, const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags,
                      void* userData) {
    float* in = (float*)inputBuffer;
    (void)outputBuffer;

    const int dispSize = 100; // Size of the display
    printf("\r");

    float vol_l = 0.0f;
    float vol_r = 0.0f;

    // Calculate maximum volumes
    for (unsigned long i = 0; i < framesPerBuffer * 2; i += 2) {
        vol_l = std::max(vol_l, std::abs(in[i]));     // Calculate vol_l
        vol_r = std::max(vol_r, std::abs(in[i + 1])); // Calculate vol_r
    }

    // Draw the volume bars
    for (int i = 0; i < dispSize; i++) {
        float barProportion = i / static_cast<float>(dispSize);
        if (barProportion <= vol_l && barProportion <= vol_r) {
            printf("█"); // Both channels max
        } else if (barProportion <= vol_l) {
            printf("▀"); // Left channel max
        } else if (barProportion <= vol_r) {
            printf("▄"); // Right channel max
        } else {
            printf(" "); // No volume
        }
    }

    // Flush output to ensure it appears immediately
    fflush(stdout);

    return 0;
}
void printAudioDevice(const PaDeviceInfo* deviceInfo, int deviceNum) {
    std::cout << "Device: " << deviceNum << "\n"
              << "-----------------------------------\n"
              << " Name:                 " << deviceInfo->name << "\n"
              << " Max Input Channels:   " << deviceInfo->maxInputChannels << "\n"
              << " Max Output Channels:  " << deviceInfo->maxOutputChannels << "\n"
              << " Default Sample Rate:  " << deviceInfo->defaultSampleRate << " Hz\n"
              << "-----------------------------------\n\n";
}
