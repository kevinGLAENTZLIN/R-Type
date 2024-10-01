# Find the Doctest package (required for testing)
find_package(doctest REQUIRED)

# Define the name of the test executable
set(TEST_NAME "r-type_tests")

# List the test source files
set(TEST_SOURCES
    MainTest.cpp
    EntityManager.cpp
)

# Create the test executable from the sources
add_executable(${TEST_NAME} ${TEST_SOURCES})

# Link the Doctest library to the test executable
target_link_libraries(${TEST_NAME} PRIVATE doctest::doctest)
target_link_libraries(${TEST_NAME} PRIVATE ${NAME_LIB})

# Add the tests to CTest for integration with the testing framework
add_test(NAME RTypeTests COMMAND ${TEST_NAME})

target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Include additional compiler flags to enable stricter compilation warnings
target_compile_options(${TEST_NAME} PRIVATE
    -Wall
    -Wextra
    -Werror
)
