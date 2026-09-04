cmake_minimum_required(VERSION 3.16)
project(OskGameFramework VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_game  sfl_intro.cpp Scena.cpp Game.cpp SFMLGame.cpp)

target_include_directories(test_game PRIVATE   ${CMAKE_SOURCE_DIR}  ${CMAKE_SOURCE_DIR}/SFML-2.6.2/include)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS system window graphics REQUIRED)

target_link_libraries(test_game PRIVATE sfml-system sfml-window  sfml-graphics )
