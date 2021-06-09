cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(operating-system-experiment)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
add_library(cru_system SHARED Thread.cpp)
target_link_libraries(cru_system PUBLIC Microsoft.GSL::GSL fmt::fmt)
target_compile_definitions(cru_system PUBLIC CRU_EXPORT_API)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cru_system)