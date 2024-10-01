enable_testing()

add_executable(microphone_test microphone_test.cpp)
target_link_libraries(microphone_test GTest::gtest_main AudioDeviceManager)

include(GoogleTest)
gtest_discover_tests(microphone_test)
