cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(information-security-experiment)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(des des.cpp)
target_link_libraries(des PRIVATE OpenSSL::Crypto)

add_executable(md5 md5.cpp)
target_link_libraries(md5 PRIVATE OpenSSL::Crypto)

add_executable(rsa rsa.cpp)
target_link_libraries(rsa PRIVATE OpenSSL::Crypto)
