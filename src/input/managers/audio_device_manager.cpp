// AudioInput.cpp
#include "audio_device_manager.h"
#include "portaudio_utils.h"
#include <cstring>
#include <iostream>
#include <portaudio.h>

AudioDeviceManager::AudioDeviceManager() {
  err = Pa_Initialize();
  checkErr(err);
  printAvailableAudioDevices();
}

AudioDeviceManager::~AudioDeviceManager() {
  err = Pa_Terminate();
  checkErr(err);
}

void AudioDeviceManager::openStream(int index) {
  const PaDeviceInfo *device = Pa_GetDeviceInfo(index);

  if (!device)
    return;

  PaStreamParameters inputParameters;

  memset(&inputParameters, 0, sizeof(inputParameters));
  inputParameters.channelCount =
      device->maxInputChannels; // get left and right input
  inputParameters.device = index;
  inputParameters.hostApiSpecificStreamInfo = NULL;
  inputParameters.sampleFormat = paFloat32;
  inputParameters.suggestedLatency = device->defaultLowInputLatency;

  err =
      Pa_OpenStream(std::out_ptr(stream), &inputParameters, nullptr,
                    device->defaultSampleRate, 512, paNoFlag, paCallback, NULL);

  checkErr(err);

  if (stream == nullptr)
    return;

  err = Pa_StartStream(stream.get());
  std::cout << "Start of stream successful\n";
  checkErr(err);
  Pa_Sleep(1 * 1000);
}

void AudioDeviceManager::closeStream() {
  if (stream) {
    err = Pa_StopStream(stream.get());
    checkErr(err);
    err = Pa_CloseStream(stream.get());
    checkErr(err);
  }
  checkErr(err);
  printf("\nEnded stream successfully");
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
