cmake_minimum_required(VERSION 3.14)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(CppPraticum)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
	string(REGEX REPLACE "/W[0-4]\\s*" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	add_compile_options(/utf-8 /W4 /WX)
endif()

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)

add_executable(main
	Base.hpp

	Book.hpp
	Book.cpp
	Vendor.hpp
	Vendor.cpp
	Record.hpp
	Record.cpp

	main.cpp
)
target_link_libraries(main PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui)
