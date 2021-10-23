cmake_minimum_required(VERSION 3.21)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

set(CMAKE_CXX_STANDARD 20)

project(cru-algorithm-experiment)

find_package(dlib CONFIG REQUIRED)

add_executable(3.1 3.1.cpp)
target_link_libraries(3.1 PRIVATE dlib::dlib)

add_executable(3.2 3.2.cpp)
target_link_libraries(3.2 PRIVATE dlib::dlib)
