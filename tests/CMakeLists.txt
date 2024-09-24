# Find the Doctest package
find_package(doctest REQUIRED)
set(TEST_NAME "r-type_tests")
# List of test sources
set(TEST_SOURCES
    test_unit_test.cpp
)

# Create a test executable
add_executable(${TEST_NAME} ${TEST_SOURCES})
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/tests")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")
# Link the Doctest library
target_link_libraries(${TEST_NAME} PRIVATE doctest::doctest)

# Add the tests to CTest
add_test(NAME RTypeTests COMMAND ${TEST_NAME})

# Include additional flags for debugging
target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra -Werror)

