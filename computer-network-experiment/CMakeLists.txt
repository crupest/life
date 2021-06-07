cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(network-experiment)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
add_library(base STATIC Common.cpp StringUtil.cpp IO.cpp)
target_link_libraries(base PUBLIC Microsoft.GSL::GSL fmt::fmt Folly::folly)
if(WIN32)
target_link_libraries(base PUBLIC Ws2_32)
endif()

add_executable(client client.cpp)
target_link_libraries(client PRIVATE base)

add_executable(server server.cpp)
find_package(folly CONFIG REQUIRED)
target_link_libraries(server PRIVATE base)
