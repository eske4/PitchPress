#pragma once

#include "audio_device.h"
#include <memory>
#include <portaudio.h>
#include <vector>

class AudioDeviceManager {
public:
  // Default constructor
  AudioDeviceManager();
  ~AudioDeviceManager();

  void openStream(int device);
  void closeStream();

private:
  void printAvailableAudioDevices();
  std::vector<AudioDevice> getAudioDevices();
  PaError err;
  std::unique_ptr<PaStream, decltype(&Pa_CloseStream)> stream{nullptr,
                                                              &Pa_CloseStream};
};
