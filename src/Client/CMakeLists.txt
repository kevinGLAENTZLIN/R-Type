project(R-Type-Client)

set(NAME_CLIENT "${RTYPE}_client")
set(CLIENT_SOURCES
    ./main.cpp
    ./Game/Game.cpp
    ./udp_client.cpp
    # ./Network/udp_client.cpp
    ../Server/Client_info.cpp
    ../Server/Game_info.cpp
    ../Utils/Protocol/Protocol.cpp
    ../Utils/Response/Response.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_UTILS})
else()
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_CLIENT} PUBLIC Boost::asio)
    target_link_libraries(${NAME_CLIENT} PUBLIC raylib raylib_cpp ${NAME_LIB})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_CMD})
    target_link_libraries(${NAME_CLIENT} PRIVATE ${NAME_LIB_UTILS})
endif()