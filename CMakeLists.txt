cmake_minimum_required(VERSION 3.16)
project(02)

SET (CMAKE_BUILD_TYPE "Release")
#SET (CMAKE_BUILD_TYPE "Debug")

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17")
SET (CMAKE_CXX_FLAGS_RELEASE "-O3")
SET (CMAKE_CXX_FLAGS_DEBUG "-g3 -fsanitize=address")

SET (BASE_DIR ${CMAKE_SOURCE_DIR} )
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BASE_DIR})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable (copy copy.cpp)
target_link_libraries(copy ${OpenCV_LIBS})

add_executable (negative negative.cpp)
target_link_libraries(negative ${OpenCV_LIBS})

add_executable (mirror mirror.cpp)
target_link_libraries(mirror ${OpenCV_LIBS})

add_executable (rotate rotate.cpp)
target_link_libraries(rotate ${OpenCV_LIBS})

add_executable (changeIntensity changeIntensity.cpp)
target_link_libraries(changeIntensity ${OpenCV_LIBS})
