cmake_minimum_required(VERSION 3.20)

project(digital-image-process-lab)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(HistogramEqulization HistogramEqulization.cpp)
target_link_libraries(HistogramEqulization ${OpenCV_LIBS})

add_executable(DiscreteFourierTransform DiscreteFourierTransform.cpp)
target_link_libraries(DiscreteFourierTransform ${OpenCV_LIBS})

add_executable(MorphologicalTransformation MorphologicalTransformation.cpp)
target_link_libraries(MorphologicalTransformation ${OpenCV_LIBS})
