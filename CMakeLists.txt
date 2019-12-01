# create project
cmake_minimum_required(VERSION 3.0.0)
project(SantaRacer VERSION 0.1.0)

# include CTest
include(CTest)
enable_testing()

# define executable
set(SOURCES
    src/SantaRacer/Angel.cpp
    src/SantaRacer/Angel.hpp
    src/SantaRacer/Args.cpp
    src/SantaRacer/Args.hpp
    src/SantaRacer/Balloon.cpp
    src/SantaRacer/Balloon.hpp
    src/SantaRacer/Chimney.cpp
    src/SantaRacer/Chimney.hpp
    src/SantaRacer/Cloud.cpp
    src/SantaRacer/Cloud.hpp
    src/SantaRacer/Config.cpp
    src/SantaRacer/Config.hpp
    src/SantaRacer/Draw.cpp
    src/SantaRacer/Draw.hpp
    src/SantaRacer/Finish.cpp
    src/SantaRacer/Finish.hpp
    src/SantaRacer/Game.cpp
    src/SantaRacer/Game.hpp
    src/SantaRacer/Gift.cpp
    src/SantaRacer/Gift.hpp
    src/SantaRacer/Globals.hpp
    src/SantaRacer/Goblin.cpp
    src/SantaRacer/Goblin.hpp
    src/SantaRacer/GoblinSnowball.cpp
    src/SantaRacer/GoblinSnowball.hpp
    src/SantaRacer/Landscape.cpp
    src/SantaRacer/Landscape.hpp
    src/SantaRacer/Level.cpp
    src/SantaRacer/Level.hpp
    src/SantaRacer/LevelObject.cpp
    src/SantaRacer/LevelObject.hpp
    src/SantaRacer/Mask.cpp
    src/SantaRacer/Mask.hpp
    src/SantaRacer/Output.cpp
    src/SantaRacer/Output.hpp
    src/SantaRacer/Random.cpp
    src/SantaRacer/Random.hpp
    src/SantaRacer/SantaRacer.cpp
    src/SantaRacer/SantaRacer.hpp
    src/SantaRacer/Score.cpp
    src/SantaRacer/Score.hpp
    src/SantaRacer/Setup.cpp
    src/SantaRacer/Setup.hpp
    src/SantaRacer/Sleigh.cpp
    src/SantaRacer/Sleigh.hpp
    src/SantaRacer/SleighStar.cpp
    src/SantaRacer/SleighStar.hpp
    src/SantaRacer/Snowflake.cpp
    src/SantaRacer/Snowflake.hpp
    src/SantaRacer/Snowman.cpp
    src/SantaRacer/Snowman.hpp
    src/SantaRacer/SnowmanStar.cpp
    src/SantaRacer/SnowmanStar.hpp
    src/SantaRacer/Sound.cpp
    src/SantaRacer/Sound.hpp
    src/SantaRacer/Text.cpp
    src/SantaRacer/Text.hpp)
add_executable(SantaRacer ${SOURCES})

# own compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Wall -Wextra")

# include header files
include_directories(src)

# include/link SDL
find_package(SDL)
include_directories(${SDL_INCLUDE_DIR})
target_link_libraries(SantaRacer ${SDL_LIBRARY} SDL_image SDL_mixer)

# include CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
