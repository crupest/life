cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

set(CMAKE_CXX_STANDARD 20)

project(computer-graphics-experiment)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(4 4.cpp)
target_link_libraries(4 PRIVATE glad::glad glfw)
