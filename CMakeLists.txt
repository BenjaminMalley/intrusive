cmake_minimum_required(VERSION 3.10)

project(intrusive C)

# Define source files
set(intrusive_sources
    ibst.c
)

# Add a library for the core functions (optional, but good practice for reusability)
add_library(intrusive_core STATIC ${intrusive_sources})

# Add an executable (e.g., a main application that uses the core functions)
# For now, we'll assume there might be a main.c later, or just a dummy executable
# If there's no main.c, we could make this a library only.
# For this example, let's assume we'll have a test executable that uses the library.
# We won't add a default application executable unless a main file is specified.

# --- Unit Testing Setup ---
enable_testing()

# Add a test executable
add_executable(intrusive_test test_main.c) # Assuming a test_main.c will contain test cases

# Link the test executable against the core library
target_link_libraries(intrusive_test intrusive_core)

# Add a test to CTest
add_test(NAME intrusive_unit_tests COMMAND intrusive_test)

# You can also add more sophisticated test frameworks like Google Test or Catch2
# For example, with Google Test:
# find_package(GTest CONFIG REQUIRED)
# target_link_libraries(intrusive_test GTest::gtest_main)
