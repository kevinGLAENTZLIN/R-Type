cmake_minimum_required(VERSION 3.10)

project(R-Type VERSION 1.0)
set(RTYPE "r-type")
# Définir le standard C++ à 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_subdirectory(src/ECS)
add_subdirectory(src/Utils)
add_subdirectory(src/Command)
add_subdirectory(src/Client)
add_subdirectory(src/Server)

enable_testing()
add_subdirectory(tests)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    message(STATUS "Found clang-tidy: ${CLANG_TIDY}")
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*;-header-filter=.*;-warnings-as-errors=*")
else()
    message(WARNING "clang-tidy not found!")
endif()

# Afficher le type de build
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
