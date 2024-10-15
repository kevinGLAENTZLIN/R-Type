project(R-Type-Utils)

set(NAME_LIB "Utils")
set(NAME_DEBUG_EXE "${RTYPE}-Utils-Debug")

set(LIB_SOURCES
    ./Response/Response.cpp
    ./Protocol/Protocol.cpp
    ./ParametersMap/ParametersMap.cpp
    )

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

add_library(${NAME_LIB} STATIC ${LIB_SOURCES})

set_target_properties(${NAME_LIB} PROPERTIES
    OUTPUT_NAME ${NAME_LIB}
    SUFFIX ".a"
)

target_include_directories(${NAME_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}Protocol
    ${CMAKE_CURRENT_SOURCE_DIR}Response
)
