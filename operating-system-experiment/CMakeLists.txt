cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_INSTALLATION_ROOT}/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

project(operating-system-experiment)

set(CMAKE_CXX_STANDARD 17)

find_package(fmt CONFIG REQUIRED)
find_package(Microsoft.GSL CONFIG REQUIRED)
add_library(cru_system SHARED Thread.cpp Mutex.cpp Interlocked.cpp Semaphore.cpp)
target_link_libraries(cru_system PUBLIC Microsoft.GSL::GSL fmt::fmt)
target_compile_definitions(cru_system PUBLIC CRU_EXPORT_API)
if(UNIX)
target_link_libraries(cru_system PUBLIC pthread)
endif()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cru_system)

add_executable(data_race_demo DataRaceDemo.cpp)
target_link_libraries(data_race_demo PRIVATE cru_system)

add_executable(mutex_avoid_data_race_demo MutexAvoidDataRaceDemo.cpp)
target_link_libraries(mutex_avoid_data_race_demo PRIVATE cru_system)

add_executable(interlocked_avoid_data_race_demo InterlockedAvoidDataRaceDemo.cpp)
target_link_libraries(interlocked_avoid_data_race_demo PRIVATE cru_system)

add_executable(semaphore_avoid_data_race_demo SemaphoreAvoidDataRaceDemo.cpp)
target_link_libraries(semaphore_avoid_data_race_demo PRIVATE cru_system)

add_executable(parallel_calculation_demo ParallelCalculationDemo.cpp)
target_link_libraries(parallel_calculation_demo PRIVATE cru_system)

add_executable(dead_lock_detection_demo DeadLockDetectionDemo.cpp)
