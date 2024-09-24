# Find the Doctest package
find_package(doctest REQUIRED)

# List of test sources
set(TEST_SOURCES
    test_unit_test.cpp
)

# Create a test executable
add_executable(rtype_tests ${TEST_SOURCES})

# Link the Doctest library
target_link_libraries(rtype_tests PRIVATE doctest::doctest)

# Add the tests to CTest
add_test(NAME RTypeTests COMMAND rtype_tests)

# Include additional flags for debugging
target_compile_options(rtype_tests PRIVATE -Wall -Wextra -Werror)
