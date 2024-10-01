#include "audio_device_manager.h"
#include <gtest/gtest.h>

// Expect continues the test whiel assert stop the test instantly, so if you
// want the test to continue use expect

TEST(TestTopic, MicTest) {
  AudioDeviceManager *mic = new AudioDeviceManager();
  ASSERT_NE(mic, nullptr) << "Oh no, mic is empty";
}
