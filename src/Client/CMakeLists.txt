project(R-Type-ECS)

set(NAME_CLIENT "${RTYPE}_client")
set(CLIENT_SOURCES
    ./main.cpp
    ./udp_client.cpp
)

add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif()

