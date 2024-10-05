set(LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/audio_device_manager.cpp)
set(LIBRARY_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/audio_device_manager.h
                   ${CMAKE_CURRENT_SOURCE_DIR}/include/portaudio_utils.h)

# Create the Microphone library
add_library(AudioDeviceManager ${LIBRARY_SOURCES} ${LIBRARY_HEADER})

target_link_libraries(AudioDeviceManager PUBLIC portaudio)
target_include_directories(AudioDeviceManager
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
