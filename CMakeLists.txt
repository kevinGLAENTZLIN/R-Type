cmake_minimum_required(VERSION 3.10)

project(R-Type VERSION 1.0)
set(RTYPE "r-type")
# Définir le standard C++ à 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Définir le type de build par défaut à Release si non spécifié
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

# Ajouter le sous-répertoire ECS
add_subdirectory(src/ECS)
add_subdirectory(src/Client)

# Configurations spécifiques pour Debug et Release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Afficher le type de build
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

