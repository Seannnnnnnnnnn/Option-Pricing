cmake_minimum_required(VERSION 3.10)

project(OptionPricing VERSION 1.0)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the path to the third-party libraries (Google Test)
set(GTEST_DIR "${CMAKE_SOURCE_DIR}/third_party/googletest")

include_directories(${GTEST_DIR}/googletest/include)

add_subdirectory(${GTEST_DIR} ${CMAKE_BINARY_DIR}/third_party/googletest)

add_executable(test_option src/tests/test_european_option.cpp)

target_link_libraries(test_option gtest gtest_main)

target_sources(test_option PRIVATE src/european_option.cpp src/option_base.cpp)

target_include_directories(test_option PRIVATE src)
