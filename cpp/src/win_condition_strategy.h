#ifndef WIN_CONDITION_STRATEGY_H
#define WIN_CONDITION_STRATEGY_H

#include "utils.h"
#include "player.h"
#include "coordinate_2d.h"
#include "connect_four_game_board.h"


struct Player;
struct Coordinate2D;
class GameBoard;


class WinConditionStrategy {
public:
    virtual ~WinConditionStrategy() {}
    virtual bool has_won(const Player& player, const GameBoard& board) = 0;

    static const int CONNECTED_COMPONENTS_NEEDED_FOR_WIN = 4;
};


class HorizontalWinConditionStrategy : public WinConditionStrategy {
public:
    HorizontalWinConditionStrategy() = default;
    bool has_won(const Player& player, const GameBoard& board) override;
};


class VerticalWinConditionStrategy : public WinConditionStrategy {
public:
    VerticalWinConditionStrategy() = default;
    bool has_won(const Player& player, const GameBoard& board) override;
};


class DiagonalWinConditionStrategy : public WinConditionStrategy {
public:
    DiagonalWinConditionStrategy() = default;
    bool has_won_on_diagonal_north_east(const Player& player, const Coordinate2D& start_coordinate, const GameBoard& board) const;
    bool has_won_on_diagonal_south_east(const Player& player, const Coordinate2D& start_coordinate, const GameBoard& board) const;
    bool has_won(const Player& player, const GameBoard& board) override;
};


#endif //WIN_CONDITION_STRATEGY_H
