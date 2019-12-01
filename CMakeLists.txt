# create project
cmake_minimum_required(VERSION 3.0.0)
project(SantaRacer VERSION 0.1.0)

# include CTest
include(CTest)
enable_testing()

# define executable
set(SOURCES
      src/SantaRacer/Args.cpp
      src/SantaRacer/Args.hpp
      src/SantaRacer/Config.cpp
      src/SantaRacer/Config.hpp
      src/SantaRacer/Draw.cpp
      src/SantaRacer/Draw.hpp
      src/SantaRacer/Game.cpp
      src/SantaRacer/Game.hpp
      src/SantaRacer/Gift.cpp
      src/SantaRacer/Gift.hpp
      src/SantaRacer/Globals.hpp
      src/SantaRacer/Landscape.cpp
      src/SantaRacer/Landscape.hpp
      src/SantaRacer/Level.cpp
      src/SantaRacer/Level.hpp
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
      src/SantaRacer/Snowflake.cpp
      src/SantaRacer/Snowflake.hpp
      src/SantaRacer/Sound.cpp
      src/SantaRacer/Sound.hpp
      src/SantaRacer/Text.cpp
      src/SantaRacer/Text.hpp
      src/SantaRacer/LevelObject/Angel.cpp
      src/SantaRacer/LevelObject/Angel.hpp
      src/SantaRacer/LevelObject/Balloon.cpp
      src/SantaRacer/LevelObject/Balloon.hpp
      src/SantaRacer/LevelObject/Chimney.cpp
      src/SantaRacer/LevelObject/Chimney.hpp
      src/SantaRacer/LevelObject/Cloud.cpp
      src/SantaRacer/LevelObject/Cloud.hpp
      src/SantaRacer/LevelObject/Finish.cpp
      src/SantaRacer/LevelObject/Finish.hpp
      src/SantaRacer/LevelObject/Goblin.cpp
      src/SantaRacer/LevelObject/Goblin.hpp
      src/SantaRacer/LevelObject/GoblinSnowball.cpp
      src/SantaRacer/LevelObject/GoblinSnowball.hpp
      src/SantaRacer/LevelObject/LevelObject.cpp
      src/SantaRacer/LevelObject/LevelObject.hpp
      src/SantaRacer/LevelObject/SleighStar.cpp
      src/SantaRacer/LevelObject/SleighStar.hpp
      src/SantaRacer/LevelObject/Snowman.cpp
      src/SantaRacer/LevelObject/Snowman.hpp
      src/SantaRacer/LevelObject/SnowmanStar.cpp
      src/SantaRacer/LevelObject/SnowmanStar.hpp
    )
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
