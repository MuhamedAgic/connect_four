cmake_minimum_required(VERSION 3.28.3)
project(connect_four_test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest setup
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Test executables
add_executable(
        connect_four_game_test
        connect_four_game_test.cpp
        ../src/connect_four_game.h
        ../src/connect_four_game.cpp
        ../src/connect_four_game_board.h
        ../src/connect_four_game_board.cpp
        ../src/win_condition_strategy.h
        ../src/win_condition_strategy.cpp
        ../src/utils.h
        ../src/utils.cpp
        ../src/coordinate_2d.h
        ../src/coordinate_2d.cpp
        ../src/player.h
        ../src/player.cpp
)
add_executable(
        connect_four_board_test
        connect_four_board_test.cpp
        ../src/connect_four_game_board.h
        ../src/connect_four_game_board.cpp
        ../src/win_condition_strategy.h
        ../src/win_condition_strategy.cpp
        ../src/utils.h
        ../src/utils.cpp
        ../src/coordinate_2d.h
        ../src/coordinate_2d.cpp
        ../src/player.h
        ../src/player.cpp
)

target_link_libraries(connect_four_game_test gtest_main)
target_link_libraries(connect_four_board_test gtest_main)

add_test(NAME connect_four_game_unit_tests COMMAND connect_four_game_test)
add_test(NAME connect_four_board_unit_tests COMMAND connect_four_board_test)
