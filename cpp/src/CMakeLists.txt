cmake_minimum_required(VERSION 3.28.3)
project(connect_four)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(connect_four main.cpp connect_four_game.h connect_four_game.cpp
        player.h
        player.cpp
        win_condition_strategy.h
        win_condition_strategy.cpp
        coordinate_2d.h
        utils.h
        connect_four_game_board.h
        connect_four_game_board.cpp
        utils.cpp
        coordinate_2d.cpp
)

