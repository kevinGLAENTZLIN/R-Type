project(R-Type-ECS)

include(FetchContent)

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

set(NAME_LIB ${RTYPE})
set(NAME_DEBUG_EXE "${RTYPE}-ECS-Debug")

set(LIB_SOURCES
    ./Core/Core.cpp
    ./Utils/Utils.cpp
    ./Entity/Missile/Missile.cpp
    ./Entity/Enemy/Enemy.cpp
    ./Entity/EntityManager/EntityManager.cpp
    ./Entity/Button/Button.cpp
    ./Entity/Player/Player.cpp
    ./Component/Position/Position.cpp
    ./Component/Health/Health.cpp
    ./Component/Projectile/Projectile.cpp
    ./Component/Velocity/Velocity.cpp
    ./Component/Hitbox/Hitbox.cpp
    ./Component/Text/Text.cpp
    ./Component/Volume/Volume.cpp
    ./Component/Input/Input.cpp
    ./System/Velocity/Velocity.cpp
    ./System/Collision/Collision.cpp
    ./System/ProjectileCollision/ProjectileCollision.cpp
    ./System/InputUpdates/InputUpdates.cpp
    ./Game/Game.cpp
    ./Component/Render/Render.cpp
    ./System/Render/Render.cpp
    ./RessourcePool/RessourcePool.cpp

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
target_link_libraries(${NAME_LIB} PUBLIC raylib raylib_cpp)
# Inclure les répertoires des headers
target_include_directories(${NAME_LIB} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}Core
    ${CMAKE_CURRENT_SOURCE_DIR}Utils
    ${CMAKE_CURRENT_SOURCE_DIR}Entity
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Missile
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Enemy
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/EntityManager
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Button
    ${CMAKE_CURRENT_SOURCE_DIR}Entity/Player
    ${CMAKE_CURRENT_SOURCE_DIR}Component
    ${CMAKE_CURRENT_SOURCE_DIR}Component/ComponentManager
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Position
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Health
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Render
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Velocity
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Hitbox
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Text
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Volume
    ${CMAKE_CURRENT_SOURCE_DIR}Component/Projectile
    ${CMAKE_CURRENT_SOURCE_DIR}System
    ${CMAKE_CURRENT_SOURCE_DIR}System/ButtonClick
    ${CMAKE_CURRENT_SOURCE_DIR}System/SystemManager
    ${CMAKE_CURRENT_SOURCE_DIR}System/Velocity
    ${CMAKE_CURRENT_SOURCE_DIR}System/System
    ${CMAKE_CURRENT_SOURCE_DIR}System/Collision
    ${CMAKE_CURRENT_SOURCE_DIR}System/ProjectileCollision
    ${CMAKE_CURRENT_SOURCE_DIR}System/InputUpdates
)

# Compiler le main.cpp seulement en mode Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    add_executable(${NAME_DEBUG_EXE} main.cpp)

    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug")
    target_link_libraries(${NAME_DEBUG_EXE} PRIVATE ${NAME_LIB})
endif()
