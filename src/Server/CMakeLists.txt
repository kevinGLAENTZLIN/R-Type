project(r-type_server)

set(NAME_SERVER "${RTYPE}_server")
set(SERVER_SOURCES
    ./udp_server.cpp
    ./main.cpp
)

find_package(boost_asio CONFIG REQUIRED)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(udp_server udp_server.cpp)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(udp_server PRIVATE Boost::asio)
else()
    add_executable(${NAME_SERVER} ${SERVER_SOURCES})

    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
    set(CMAKE_RUNTIME_OUPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries(${NAME_SERVER} PRIVATE Boost::asio)
endif()

