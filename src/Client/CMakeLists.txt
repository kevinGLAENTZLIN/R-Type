project(R-Type-Client)


find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
        GIT_SHALLOW 1
    )
    FetchContent_MakeAvailable(raylib)
endif()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    if (NOT DEFINED RAYLIB_CPP_VERSION)
        set(RAYLIB_CPP_VERSION v5.0.2)
    endif()
    include(FetchContent)
    FetchContent_Declare(
        raylib_cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG ${RAYLIB_CPP_VERSION}
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif()

set(NAME_CLIENT "${RTYPE}_client")
set(CLIENT_SOURCES
    ./main.cpp
    ./Game/Game.cpp
    ./udp_client.cpp
)

find_package(boost_asio CONFIG REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_CMD})
else()
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
endif()

if(WIN32)
    # Configuration pour Windows
    target_link_libraries(${NAME_CLIENT} PRIVATE winmm)
elseif(APPLE)
    # Configuration pour macOS
    target_link_libraries(${NAME_CLIENT} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(UNIX AND NOT APPLE)
    # Configuration pour Linux
    target_link_libraries(${NAME_CLIENT} PRIVATE m pthread dl rt X11)
endif()
