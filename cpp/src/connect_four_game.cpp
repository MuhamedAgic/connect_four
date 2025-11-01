#include <iostream>
#include <algorithm>
#include <optional>
#include "connect_four_game.h"


ConnectFourGame::ConnectFourGame() {
    m_players = create_players();
}


void ConnectFourGame::run() {
    std::cout << "Welcome to connect four!" << std::endl;
    m_board.display();

    TurnOutcome turn_outcome = TurnOutcome::CONTINUE_GAME;
    while (turn_outcome != TurnOutcome::EXIT_GAME) {
        for (int i = 0; i < m_players.size(); i++) {
            turn_outcome = process_turn(m_players.at(i));
            while (turn_outcome == TurnOutcome::INVALID_MOVE) {
                turn_outcome = process_turn(m_players.at(i));
            }
            if (turn_outcome == TurnOutcome::NEW_GAME) {
                i = -1; // start with player one again
            }
            else if (turn_outcome == TurnOutcome::EXIT_GAME) {
                break;
            }
        }
    }

    std::cout << "Game ended!" << std::endl;
}


TurnOutcome ConnectFourGame::process_turn(const Player& player) {
    std::optional<Coordinate2D> last_played_move = m_board.get_move(player);
    if (!last_played_move.has_value()) {
        return TurnOutcome::INVALID_MOVE;
    }

    if (player.type == PlayerType::COMPUTER) {
        std::cout << "Computer (player " << player.id << ") moves: ";
    }
    else if (player.type == PlayerType::HUMAN) {
        std::cout << "You (player " << player.id << ") moved: ";
    }
    std::cout << last_played_move.value() << std::endl;

    m_board.display();

    bool game_over = false;
    if (has_won(player)) {
        std::cout << "Player " << player.id << " won!" << std::endl;
        game_over = true;
    }

    if (m_board.is_full() && !has_won(player)) {
        std::cout << "Board is full and it's a draw!" << std::endl;
        game_over = true;
    }

    if (game_over) {
        std::cout << "Do you wish to play another game? y/n: ";
        if (confirms()) {
            m_board.clear();
            m_board.display();
            return TurnOutcome::NEW_GAME;
        }
        return TurnOutcome::EXIT_GAME;
    }

    return TurnOutcome::CONTINUE_GAME;
}


std::vector<Player> ConnectFourGame::create_players() const {
    std::vector<Player> players;
    Player p1 {1, PlayerType::HUMAN, "x"};
    Player p2 {2, PlayerType::COMPUTER, "o"};
    // Player p3 {3, PlayerType::COMPUTER, "v"};
    players.push_back(p1);
    players.push_back(p2);
    // players.push_back(p3);
    return players;
}


bool ConnectFourGame::has_won(const Player& player) const {
    return std::any_of(m_board.get_win_condition_strategies().begin(),
                        m_board.get_win_condition_strategies().end(),
                        [this, &player](const auto& win_condition_strategy) {
                            return win_condition_strategy->has_won(player, m_board);
                        });
}


bool ConnectFourGame::has_winner() const {
    return std::any_of(m_players.begin(),
                        m_players.end(),
                        [this](const Player& p) { return has_won(p); });
}
