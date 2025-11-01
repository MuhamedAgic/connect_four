#include <gtest/gtest.h>
#include "../src/connect_four_game_board.h"


// More elegant way to not duplicate this class?
class FixtureConnectFourDrawnGame : public ::testing::Test {
protected:
    GameBoard board;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        Player p2 {2, PlayerType::COMPUTER, "o"};
        Player p3 {3, PlayerType::COMPUTER, "v"};
        Player p4 {4, PlayerType::COMPUTER, "@"};
        for (int i = 0; i < board.rows(); i++) {
            for (int j = 0; j < board.cols(); j++) {
                if (i % 2 == 0) {
                    if (j % 2 == 0) {
                        board.m_board.at(i).at(j) = p1;
                    }
                    else {
                        board.m_board.at(i).at(j) = p2;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        board.m_board.at(i).at(j) = p3;
                    }
                    else {
                        board.m_board.at(i).at(j) = p4;
                    }
                }
            }
        }
        std::cout << "Setup drawn board complete" << std::endl;
        board.display();
    }
};


class FixtureConnectFourGameBottomRowFull : public ::testing::Test {
protected:
    GameBoard board;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        int curr_row = 0;
        for (int i = 0; i < board.m_cols; i++) {
            board.m_board.at(board.m_rows - 1).at(i) = p1;
            ++curr_row;
        }
        std::cout << "Setup bottom row full board complete" << std::endl;
        board.display();
    }
};


class FixtureConnectFourGameFirstColumnFull : public ::testing::Test {
protected:
    GameBoard board;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        int curr_row = 0;
        for (int i = 0; i < board.m_rows; i++) {
            board.m_board.at(i).at(0) = p1;
            ++curr_row;
        }
        std::cout << "Setup first column full board complete" << std::endl;
        board.display();
    }
};


TEST_F(FixtureConnectFourDrawnGame, BoardFull) {
    EXPECT_TRUE(board.is_full());
}


TEST_F(FixtureConnectFourGameBottomRowFull, TestGravity) {
    Player p {1, PlayerType::HUMAN, "x"};

    // If I drop a move, it cannot be on the bottom, since the bottom is already full
    const std::optional<Coordinate2D> move = board.drop_move_on_column(p, 0);
    EXPECT_TRUE(move.has_value());
    EXPECT_EQ(move.value().x, board.rows() - 2); // not rows - 1 because bottom row is full
    std::cout << "After dropping on column 0" << std::endl;
    board.display();
}


TEST_F(FixtureConnectFourGameFirstColumnFull, InsertInFullColumnImpossible) {
    Player p {1, PlayerType::HUMAN, "x"};
    EXPECT_FALSE(board.drop_move_on_column(p, 0).has_value());  // If I drop a move on a full column
}

