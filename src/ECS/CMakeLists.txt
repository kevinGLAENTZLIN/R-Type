project(R-Type-ECS)

set(NAME_LIB ${RTYPE})
set(NAME_DEBUG_EXE "${RTYPE}-ECS-Debug")

set(LIB_SOURCES
    Entity/Enemy/Enemy.cpp
    Entity/EntityManager/EntityManager.cpp
    Entity/Missile/Missile.cpp
    Entity/Player/Player.cpp
    Component/Position/Position.cpp
    Component/Velocity/Velocity.cpp
    System/SystemVelocity/SystemVelocity.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/Component
    ${CMAKE_CURRENT_SOURCE_DIR}/Component/ComponentManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Component/Position
    ${CMAKE_CURRENT_SOURCE_DIR}/Component/Velocity
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity/Enemy
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity/EntityManager
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity/Missile
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/System
    ${CMAKE_CURRENT_SOURCE_DIR}/System/System
    ${CMAKE_CURRENT_SOURCE_DIR}/System/SystemManager
    ${CMAKE_CURRENT_SOURCE_DIR}/System/SystemVelocity
)

# Compiler le main.cpp seulement en mode Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    add_executable(${NAME_DEBUG_EXE} main.cpp)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(${NAME_DEBUG_EXE} PRIVATE ${NAME_LIB})
endif()

