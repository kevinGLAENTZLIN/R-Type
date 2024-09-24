project(MyRaylib)

set(NAME_LIB "myraylib")
set(NAME_DEBUG_EXE "${NAME_LIB}-Debug")
set(LIB_SOURCES
    ./MyRaylib.cpp
)
# Créer la bibliothèque
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(${NAME_LIB} STATIC ${LIB_SOURCES})
set_target_properties(${NAME_LIB} PROPERTIES
    OUTPUT_NAME ${NAME_LIB}
    SUFFIX ".a"
)

# Inclure les répertoires des headers
target_include_directories(${NAME_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
# Compiler le main.cpp seulement en mode Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    add_executable(${NAME_DEBUG_EXE} main.cpp)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(${NAME_DEBUG_EXE} PRIVATE ${NAME_LIB})
endif()

