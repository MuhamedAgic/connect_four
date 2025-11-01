#ifndef CONNECT_FOUR_H
#define CONNECT_FOUR_H

#include <vector>
#include "player.h"
#include "win_condition_strategy.h"


enum class TurnOutcome {
    NEW_GAME,
    CONTINUE_GAME,
    EXIT_GAME,
    INVALID_MOVE
};


class ConnectFourGame {
public:
    ConnectFourGame();

    void run();
    TurnOutcome process_turn(const Player& player);
    bool has_winner() const;
    bool has_won(const Player& player) const;
    std::vector<Player> create_players() const;


private:
    friend class FixtureConnectFourDrawnGame;
    friend class FixtureConnectFourWonVerticalGame;
    friend class FixtureConnectFourWonHorizontalGame;
    friend class FixtureConnectFourWonDiagonallyNorthEastGame;
    friend class FixtureConnectFourWonDiagonallySouthEastGame;

    GameBoard m_board;
    std::vector<Player> m_players;
};

#endif //CONNECT_FOUR_H
