#include <gtest/gtest.h>
#include "../src/connect_four_game.h"


class FixtureConnectFourDrawnGame : public ::testing::Test {
protected:
    ConnectFourGame game;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        Player p2 {2, PlayerType::COMPUTER, "o"};
        Player p3 {3, PlayerType::COMPUTER, "v"};
        Player p4 {4, PlayerType::COMPUTER, "@"};
        for (int i = 0; i < game.m_board.rows(); i++) {
            for (int j = 0; j < game.m_board.cols(); j++) {
                if (i % 2 == 0) {
                    if (j % 2 == 0) {
                        game.m_board.m_board.at(i).at(j) = p1;
                    }
                    else {
                        game.m_board.m_board.at(i).at(j) = p2;
                    }
                }
                else {
                    if (j % 2 == 0) {
                        game.m_board.m_board.at(i).at(j) = p3;
                    }
                    else {
                        game.m_board.m_board.at(i).at(j) = p4;
                    }
                }
            }
        }
        std::cout << "Setup drawn board complete" << std::endl;
        game.m_board.display();
    }
};


class FixtureConnectFourWonVerticalGame : public ::testing::Test {
protected:
    ConnectFourGame game;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        for (int i = game.m_board.rows() - WinConditionStrategy::CONNECTED_COMPONENTS_NEEDED_FOR_WIN; i < game.m_board.rows(); i++) {
            game.m_board.m_board.at(i).at(0) = p1;
        }
        std::cout << "Setup vertical won board complete" << std::endl;
        game.m_board.display();
    }
};


class FixtureConnectFourWonHorizontalGame : public ::testing::Test {
protected:
    ConnectFourGame game;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        for (int i = 0; i < WinConditionStrategy::CONNECTED_COMPONENTS_NEEDED_FOR_WIN; i++) {
            game.m_board.m_board.at(game.m_board.rows() - 1).at(i) = p1;
        }
        std::cout << "Setup horizontal won board complete" << std::endl;
        game.m_board.display();
    }
};


class FixtureConnectFourWonDiagonallyNorthEastGame : public ::testing::Test {
protected:
    ConnectFourGame game;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        int curr_row = game.m_board.rows() - 1;
        for (int i = 0; i < WinConditionStrategy::CONNECTED_COMPONENTS_NEEDED_FOR_WIN; i++) {
            game.m_board.m_board.at(curr_row).at(i) = p1;
            --curr_row;
        }
        std::cout << "Setup diagonally north east won board complete" << std::endl;
        game.m_board.display();
    }
};


class FixtureConnectFourWonDiagonallySouthEastGame : public ::testing::Test {
protected:
    ConnectFourGame game;

    void SetUp() override {
        Player p1 {1, PlayerType::HUMAN, "x"};
        int curr_row = 0;
        for (int i = 0; i < WinConditionStrategy::CONNECTED_COMPONENTS_NEEDED_FOR_WIN; i++) {
            game.m_board.m_board.at(curr_row).at(i) = p1;
            ++curr_row;
        }
        std::cout << "Setup diagonally south east won board complete" << std::endl;
        game.m_board.display();
    }
};


TEST_F(FixtureConnectFourDrawnGame, BoardFull) {
    EXPECT_FALSE(game.has_winner());
}


TEST_F(FixtureConnectFourWonVerticalGame, WonGameVertically) {
    EXPECT_TRUE(game.has_winner());
}


TEST_F(FixtureConnectFourWonHorizontalGame, WonGameHorizontally) {
    EXPECT_TRUE(game.has_winner());
}


TEST_F(FixtureConnectFourWonDiagonallyNorthEastGame, WonDiagonallyNorthEastGame) {
    EXPECT_TRUE(game.has_winner());
}


TEST_F(FixtureConnectFourWonDiagonallySouthEastGame, WonDiagonallySouthEastGame) {
    EXPECT_TRUE(game.has_winner());
}