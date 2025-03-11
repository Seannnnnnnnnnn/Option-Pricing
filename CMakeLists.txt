# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(EuropeanOptionPricing)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add the third-party directory to the project
add_subdirectory(third_party/googletest)

# Add source files
set(SOURCES
    src/american_option.h
    src/european_option.h
    src/option_base.h
    src/option_type.h
    src/payoff.h
    src/pricing-engines/lattice_crr.cpp
    src/pricing-engines/lattice_crr.h
    src/pricing-engines/black_scholes.cpp
    src/pricing-engines/black_scholes.h
    src/pricing-engines/pricing_engine_base.cpp
    src/pricing-engines/pricing_engine_base.h
    src/side.h
    src/tests/testing_constants.h
)

# Add test files
set(TEST_SOURCES
    src/tests/test_european_option.cpp
    src/tests/test_american_option.cpp
)

# Create executable
add_executable(EuropeanOptionPricing ${SOURCES} ${TEST_SOURCES})
add_executable(AmericanOptionPricing ${SOURCES} ${TEST_SOURCES})

# Link Google Test with your project
target_link_libraries(EuropeanOptionPricing gtest gtest_main)
target_link_libraries(AmericanOptionPricing gtest gtest_main)

# Enable testing
enable_testing()

# Add test
add_test(NAME TestEuropeanOption COMMAND EuropeanOptionPricing)
add_test(NAME TestAmericanOption COMMAND AmericanOptionPricing)

# Include directories for your project
target_include_directories(EuropeanOptionPricing PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_include_directories(AmericanOptionPricing PRIVATE ${PROJECT_SOURCE_DIR}/src)
