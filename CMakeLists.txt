cmake_minimum_required (VERSION 3.22)

project(MiniClang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${MINICLANG_SRC_INCLUDE_DIR} ${MINICLANG_TEST_INCLUDE_DIR} ${MINICLANG_EXTERN_INCLUDE_DIR})
include_directories(BEFORE src) # This is needed for gtest.

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# #####################################################################################################################
# Other CMake modules
# MUST BE ADDED AFTER CONFIGURING COMPILER PARAMETERS
# #####################################################################################################################
add_subdirectory(src)

option(MINICLANG_TEST "Build tests" ON)
if(MINICLANG_TEST)
  enable_testing()
  set(CTEST_OUTPUT_ON_FAILURE ON)
  add_subdirectory(test)
endif()