#include "connect_four_cpp_rs/src/ffi.rs.h"
#include <iostream>

bool wants_replay() {
    std::cout << "Do you want to play again? (y/n): ";
    char response;
    std::cin >> response;

    if (response == 'y' || response == 'Y') {
        return true;
    }

    if (response == 'n' || response == 'N') {
        return false;
    }

    std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
    return wants_replay();
}

int main() {
    std::cout << "🎮 Connect Four (C++ + Rust cxx FFI)" << std::endl;

    auto game = new_game();   // std::unique_ptr<Game>

    while (true) {

        // ✅ FIX: no dereference
        std::cout << board_string(*game).c_str() << std::endl;

        std::cout << "Enter column: ";
        int col;
        std::cin >> col;

        // ✅ FIX: pass object directly
        int result = play_move(*game, col);

        if (result >= 1) {
            std::cout << "Player " << result << " wins!\n";
        } else if (result == -1) {
            std::cout << "Exiting game\n";
        } else if (result == -2) {
            std::cout << "Draw!\n";
        } else if (result == -3) {
            std::cout << "Invalid move\n";
        }

        if (is_game_over(*game)) {
            if (wants_replay()) {
                std::cout << "Restarting game...\n";
                reset(*game);   // ✅ FIX
            } else {
                std::cout << "Exiting game ...\n";
                break;
            }
        }
    }

    std::cout << "Game over\n";
    return 0;
}