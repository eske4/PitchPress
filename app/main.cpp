#include "audio_device_manager.h"
#include "config.hpp"
#include <cstdlib>
#include <iostream> // Include the iostream library for input and output
#include <string>

int main() { // Entry point of the program
  std::cout << project_name << '\n';
  std::cout << project_version << '\n';
  AudioDeviceManager mic;
  int input;
  std::cin >> input;
  mic.openStream(input);
  Pa_Sleep(1 * 1000);
  mic.closeStream();

  return EXIT_SUCCESS;
}
