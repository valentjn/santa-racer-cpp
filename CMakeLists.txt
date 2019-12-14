# create project
cmake_minimum_required(VERSION 3.0.0)
project(SantaRacer VERSION 0.1.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# include CTest
include(CTest)
enable_testing()

# define executable
set(SOURCES
      src/SantaRacer/Chimney.cpp
      src/SantaRacer/Chimney.hpp
      src/SantaRacer/Game.cpp
      src/SantaRacer/Game.hpp
      src/SantaRacer/Gift.cpp
      src/SantaRacer/Gift.hpp
      src/SantaRacer/Landscape.cpp
      src/SantaRacer/Landscape.hpp
      src/SantaRacer/Level.cpp
      src/SantaRacer/Level.hpp
      src/SantaRacer/Main.cpp
      src/SantaRacer/Options.cpp
      src/SantaRacer/Options.hpp
      src/SantaRacer/Printer.cpp
      src/SantaRacer/Printer.hpp
      src/SantaRacer/Printer.inl
      src/SantaRacer/RNG.cpp
      src/SantaRacer/RNG.hpp
      src/SantaRacer/Score.cpp
      src/SantaRacer/Score.hpp
      src/SantaRacer/Sleigh.cpp
      src/SantaRacer/Sleigh.hpp
      src/SantaRacer/SleighStar.cpp
      src/SantaRacer/SleighStar.hpp
      src/SantaRacer/Snowflake.cpp
      src/SantaRacer/Snowflake.hpp
      src/SantaRacer/SnowmanStar.cpp
      src/SantaRacer/SnowmanStar.hpp
      src/SantaRacer/Text.cpp
      src/SantaRacer/Text.hpp

      src/SantaRacer/Asset/AssetLibrary.hpp
      src/SantaRacer/Asset/AssetLibrary.inl
      src/SantaRacer/Asset/DataLibrary.cpp
      src/SantaRacer/Asset/DataLibrary.hpp
      src/SantaRacer/Asset/Image.cpp
      src/SantaRacer/Asset/Image.hpp
      src/SantaRacer/Asset/ImageLibrary.cpp
      src/SantaRacer/Asset/ImageLibrary.hpp
      src/SantaRacer/Asset/Music.cpp
      src/SantaRacer/Asset/Music.hpp
      src/SantaRacer/Asset/MusicLibrary.cpp
      src/SantaRacer/Asset/MusicLibrary.hpp
      src/SantaRacer/Asset/Sound.cpp
      src/SantaRacer/Asset/Sound.hpp
      src/SantaRacer/Asset/SoundLibrary.cpp
      src/SantaRacer/Asset/SoundLibrary.hpp

      src/SantaRacer/LevelObject/Angel.cpp
      src/SantaRacer/LevelObject/Angel.hpp
      src/SantaRacer/LevelObject/Balloon.cpp
      src/SantaRacer/LevelObject/Balloon.hpp
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
      src/SantaRacer/LevelObject/Snowman.cpp
      src/SantaRacer/LevelObject/Snowman.hpp
    )
add_executable(SantaRacer ${SOURCES})

# own compiler settings
set_property(TARGET SantaRacer PROPERTY CXX_STANDARD 17)
target_compile_options(SantaRacer PRIVATE -Wall -Wextra)

# include header files
target_include_directories(SantaRacer PRIVATE src)

# include/link SDL
find_package(SDL2)
find_package(SDL2_image)
find_package(SDL2_mixer)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(SantaRacer ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY})

# include CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
