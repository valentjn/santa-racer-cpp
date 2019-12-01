# create project
cmake_minimum_required(VERSION 3.0.0)
project(SantaRacer VERSION 0.1.0)

# include CTest
include(CTest)
enable_testing()

# define executable
file(GLOB SOURCES "src/*.cpp")
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
