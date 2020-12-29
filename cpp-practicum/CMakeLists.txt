cmake_minimum_required(VERSION 3.14)

project(CppPraticum)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
	string(REGEX REPLACE "/W[0-4]\\s*" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	add_compile_options(/utf-8 /W4 /WX)
endif()

add_executable(main main.cpp Base.hpp StringUtil.hpp StringUtil.cpp)
