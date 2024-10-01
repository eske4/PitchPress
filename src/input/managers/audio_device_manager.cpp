// AudioInput.cpp
#include "audio_device_manager.h"
#include "portaudio_utils.h"
#include <cstring>
#include <iostream>
#include <portaudio.h>

AudioDeviceManager::AudioDeviceManager() {
  err = Pa_Initialize();
  printAvailableAudioDevices();
}

AudioDeviceManager::~AudioDeviceManager() {
  err = Pa_Terminate();
  std::cout << "I deleted myself";
}

void AudioDeviceManager::openStream(int device) {
  PaStreamParameters inputParameters, outputParameters;

  memset(&inputParameters, 0, sizeof(inputParameters));
  inputParameters.channelCount = 2; // get left and right input
  inputParameters.device = device;
  inputParameters.hostApiSpecificStreamInfo = NULL;
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency =
      Pa_GetDeviceInfo(device)->defaultLowInputLatency;

  err = Pa_OpenStream(std::out_ptr(stream), &inputParameters, nullptr, 48000,
                      512, paNoFlag, paCallback, NULL);
  std::cout << "Opening the stream\n";
  checkErr(err);

  err = Pa_StartStream(stream.get());
  std::cout << "Starting the stream\n";
  checkErr(err);
  Pa_Sleep(1 * 1000);
}

void AudioDeviceManager::closeStream() {
  err = Pa_StopStream(stream.get());
  std::cout << "Stopping the stream\n";
  checkErr(err);
}

void AudioDeviceManager::printAvailableAudioDevices() {
  std::cout << "I started";
  // checkErr(err);

  int numDevices = Pa_GetDeviceCount();
  const PaDeviceInfo *deviceInfo;
  for (int i = 0; i < numDevices; i++) {
    deviceInfo = Pa_GetDeviceInfo(i);
    printAudioDevice(deviceInfo, i);
  }
}
