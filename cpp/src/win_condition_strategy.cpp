#include "win_condition_strategy.h"

bool HorizontalWinConditionStrategy::has_won(const Player& player, const GameBoard& board) {
    std::vector<Coordinate2D> winning_coordinates;
    int max_connected_moves_count = 0;
    for (int i = 0; i < board.rows(); i++) {
        for (int j = 0; j < board.cols(); j++) {
            if (board.at(i, j) == player) {
                winning_coordinates.push_back(Coordinate2D {i, j});
                ++max_connected_moves_count;
                if (max_connected_moves_count == CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
                    std::cout << "Winning move: ";
                    print_coordinates(winning_coordinates);
                    return true;
                }
            }
            else {
                max_connected_moves_count = 0;
                winning_coordinates.clear();
            }
        }
        // reset on new row
        max_connected_moves_count = 0;
        winning_coordinates.clear();
    }
    return false;
}


bool VerticalWinConditionStrategy::has_won(const Player& player, const GameBoard& board) {
    std::vector<Coordinate2D> winning_coordinates;
    int max_connected_moves_count = 0;
    for (int i = 0; i < board.cols(); i++) {
        for (int j = 0; j < board.rows(); j++) {
            if (board.at(j, i) == player) {
                winning_coordinates.push_back(Coordinate2D {j, i});
                ++max_connected_moves_count;
                if (max_connected_moves_count == CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
                    std::cout << "Winning moves: ";
                    print_coordinates(winning_coordinates);
                    return true;
                }
            }
            else {
                max_connected_moves_count = 0;
                winning_coordinates.clear();
            }
        }
        // reset on new column
        max_connected_moves_count = 0;
        winning_coordinates.clear();
    }
    return false;
}


bool DiagonalWinConditionStrategy::has_won(const Player& player, const GameBoard& board) {
    // generate start coordinates to look diagonally
    std::vector<Coordinate2D> start_coordinates_win_check_south_east;
    std::vector<Coordinate2D> start_coordinates_win_check_north_east;
    for (int i = 0; i < board.cols(); i++) {// top border
        start_coordinates_win_check_south_east.push_back(Coordinate2D {0, i});
    }
    for (int i = 0; i < board.rows(); i++) { // left border
        start_coordinates_win_check_south_east.push_back(Coordinate2D {i, 0});
        start_coordinates_win_check_north_east.push_back(Coordinate2D {i, 0});
    }
    for (int i = 0; i < board.cols(); i++) { // bottom border
        start_coordinates_win_check_north_east.push_back(Coordinate2D {board.rows() - 1, i});
    }

    // check if player won on south east diagonal
    for (auto& coordinate : start_coordinates_win_check_south_east) {
        if (has_won_on_diagonal_south_east(player, coordinate, board)) {
            return true;
        }
    }

    // check if player won on north east diagonal
    for (auto& coordinate : start_coordinates_win_check_north_east) {
        if (has_won_on_diagonal_north_east(player, coordinate, board)) {
            return true;
        }
    }
    return false;
}


bool DiagonalWinConditionStrategy::has_won_on_diagonal_south_east(const Player& player,
                                                                const Coordinate2D& start_coordinate,
                                                                const GameBoard& board) const {
    // starts looking from start coordinate in to the south east direction to see if the player has won
    if (start_coordinate.x > board.rows() - CONNECTED_COMPONENTS_NEEDED_FOR_WIN
        && start_coordinate.y < CONNECTED_COMPONENTS_NEEDED_FOR_WIN - 1) {
        return false; // bottom left corner no win possible
    }
    if (start_coordinate.x < CONNECTED_COMPONENTS_NEEDED_FOR_WIN - 1
        && start_coordinate.y > board.cols() - CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
        return false; // top right corner no win possible
    }

    std::vector<Coordinate2D> winning_coordinates;

    // start looking on one diagonal
    int max_connected_moves_count = 0;
    int curr_col = start_coordinate.y;
    for (int i = start_coordinate.x; i < board.rows(); i++) { // downwards to the right side
        if (board.at(i, curr_col) == player) {
            winning_coordinates.push_back(Coordinate2D {i, curr_col});
            ++max_connected_moves_count;
            if (max_connected_moves_count == CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
                std::cout << "Winning moves: ";
                print_coordinates(winning_coordinates);
                return true;
            }
        }
        else {
            max_connected_moves_count = 0;
            winning_coordinates.clear();
        }

        if (curr_col < board.cols() - 1) {
            ++curr_col; // from left to right
        }
        else {
            break;
        }
    }
    return false;
}


bool DiagonalWinConditionStrategy::has_won_on_diagonal_north_east(const Player& player,
                                                                const Coordinate2D& start_coordinate,
                                                                const GameBoard& board) const {
    // starts looking from start coordinate in to the north east direction to see if the player has won
    if (start_coordinate.x < CONNECTED_COMPONENTS_NEEDED_FOR_WIN - 1
        && start_coordinate.y < CONNECTED_COMPONENTS_NEEDED_FOR_WIN - 1) {
        return false; // top left corner no win possible
    }
    if (start_coordinate.x > board.rows() - CONNECTED_COMPONENTS_NEEDED_FOR_WIN
        && start_coordinate.y > board.cols() - CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
        return false; // bottom right corner no win possible
    }

    std::vector<Coordinate2D> winning_coordinates;

    // start looking on one diagonal
    int max_connected_moves_count = 0;
    int curr_col = start_coordinate.y;
    for (int i = start_coordinate.x; i > 0; i--) { // upwards to the right side
        if (board.at(i, curr_col) == player) {
            winning_coordinates.push_back(Coordinate2D {i, curr_col});
            ++max_connected_moves_count;
            if (max_connected_moves_count == CONNECTED_COMPONENTS_NEEDED_FOR_WIN) {
                std::cout << "Winning moves: ";
                print_coordinates(winning_coordinates);
                return true;
            }
        }
        else {
            max_connected_moves_count = 0;
            winning_coordinates.clear();
        }

        if (curr_col < board.cols() - 1) {
            ++curr_col; // from left to right
        }
        else {
            break;
        }
    }
    return false;
}
