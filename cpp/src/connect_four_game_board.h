#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <optional>
#include <vector>
#include <iomanip>

#include "win_condition_strategy.h"
#include "player.h"

class WinConditionStrategy;

class GameBoard {
public:
    GameBoard();
    GameBoard(int r, int c);

    void clear();
    void display() const;
    void draw_top_bottom() const;

    bool has_winner() const;
    bool has_won(const Player& player) const;
    bool is_full() const;
    bool is_valid_move(const int desired_move_col) const;

    std::vector<int> get_possible_column_moves() const;
    const std::vector<std::unique_ptr<WinConditionStrategy>>& get_win_condition_strategies() const;

    std::optional<int> ask_desired_move() const;
    std::optional<Coordinate2D> get_move(const Player& player);
    std::optional<Coordinate2D> play_move(const Player& player);
    std::optional<Coordinate2D> generate_move() const;
    std::optional<Coordinate2D> play_generated_move(const Player& player);
    std::optional<Coordinate2D> apply_gravity(const int desired_move_col) const;
    std::optional<Player> at(const int row, const int col) const;

    // functions for test purposes
    std::optional<Coordinate2D> drop_move_on_column(const Player& player, const int col);
    bool hardcode_move(const Player& player, const Coordinate2D& coordinate);
    int rows() const;
    int cols() const;

    static const int EMPTY_SPOT = 0;

private:
    friend class FixtureConnectFourDrawnGame;
    friend class FixtureConnectFourDrawnGame;
    friend class FixtureConnectFourWonVerticalGame;
    friend class FixtureConnectFourWonHorizontalGame;
    friend class FixtureConnectFourWonDiagonallyNorthEastGame;
    friend class FixtureConnectFourWonDiagonallySouthEastGame;
    friend class FixtureConnectFourGameBottomRowFull;
    friend class FixtureConnectFourGameFirstColumnFull;

    int m_rows = 6;
    int m_cols = 7;
    std::vector<std::vector<Player>> m_board = std::vector<std::vector<Player>>(m_rows, std::vector<Player>(m_cols, Player {0, PlayerType::HUMAN}));

    std::vector<std::unique_ptr<WinConditionStrategy>> m_win_condition_strategies;

    void setup_default_win_condition_strategies();
};

#endif //GAME_BOARD_H
