cmake_minimum_required(VERSION 3.30.3)

project(
  audio_to_keystrokes
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(cmake/CPM.cmake)
include(cmake/Packages.cmake)

add_subdirectory(configured)
add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(app)
