cmake_minimum_required(VERSION 2.8)

project(HHXX)

# silence policy CMP0042 warning by enabling RPATH explicitly
if(APPLE AND NOT DEFINED CMAKE_MACOSX_RPATH)
  set(CMAKE_MACOSX_RPATH TRUE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_BINARY_DIR}/bin")

find_package(GTest REQUIRED)

include_directories(
  ${GTest_INCLUDE_DIRS}
  ${HHXX_SOURCE_DIR}
)

enable_testing()
add_subdirectory(test)
