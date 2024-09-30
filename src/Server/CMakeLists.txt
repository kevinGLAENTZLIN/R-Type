project(r-type_server)

set(NAME_CLIENT "${RTYPE}_server")
set(CLIENT_SOURCES
    ./main.cpp
)

find_package(boost_asio CONFIG REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(udp_client udp_client.cpp)
    add_executable(udp_server udp_server.cpp)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(udp_client PRIVATE Boost::asio)
    target_link_libraries(udp_server PRIVATE Boost::asio)
else()
    add_executable(${NAME_CLIENT} ${CLIENT_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_CLIENT} PRIVATE Boost::asio)
endif()
