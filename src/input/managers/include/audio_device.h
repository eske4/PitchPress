#include <iostream>
#include <portaudio.h>

struct AudioDevice {
  int deviceId;             // ID of the audio device
  const PaDeviceInfo *info; // Pointer to device info

  // Constructor to initialize the AudioDevice
  AudioDevice(int id, const PaDeviceInfo *deviceInfo)
      : deviceId(id), info(deviceInfo) {}
};
