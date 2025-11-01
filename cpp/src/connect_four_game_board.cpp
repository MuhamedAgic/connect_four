#include "connect_four_game_board.h"


GameBoard::GameBoard() {
    setup_default_win_condition_strategies();
}


GameBoard::GameBoard(const int r, const int c) :
    m_rows(r),
    m_cols(c) {
    setup_default_win_condition_strategies();
}


void GameBoard::setup_default_win_condition_strategies() {
    m_win_condition_strategies.push_back(std::make_unique<HorizontalWinConditionStrategy>());
    m_win_condition_strategies.push_back(std::make_unique<VerticalWinConditionStrategy>());
    m_win_condition_strategies.push_back(std::make_unique<DiagonalWinConditionStrategy>());
}


void GameBoard::clear() {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            m_board.at(i).at(j) = Player {0,  PlayerType::COMPUTER};
        }
    }
}


void GameBoard::display() const {
    std::cout << " ";
    for (int i = 0; i < m_cols; i++) {
        std::cout << std::setw(3) << i;
    }
    std::cout << std::endl;

    draw_top_bottom();
    for (int i = 0; i < m_rows; i++) {
        std::cout << '|';
        for (int j = 0; j < m_cols; j++) {
            std::cout << std::setw(3) << m_board.at(i).at(j).marker;
        }
        std::cout << std::setw(3) << "|" << std::endl;
    }
    draw_top_bottom();
    std::cout << std::endl;
}


void GameBoard::draw_top_bottom() const {
    std::cout  << '|';
    for (int j = 0; j < m_cols; j++) {
        std::cout << std::setw(3) << "-";
    }
    std::cout << std::setw(3) << "|" << std::endl;
}


std::optional<int> GameBoard::ask_desired_move() const {
    std::cout << "What move would you like to play?" << std::endl;
    std::cout << "Col: ";

    std::string input;
    std::cin >> input;

    int desired_move_col;
    try {
        desired_move_col = std::stoi(input);
    }
    catch (const std::exception& e) {
        std::cout << "Could not parse input, exception occurred: " << e.what() << std::endl;
        return std::nullopt;
    }

    if (!is_valid_move(desired_move_col)) {
        std::cout << "Invalid move on column: " << desired_move_col << std::endl;
        std::cout << "Please select another column" << std::endl;
        return std::nullopt;
    }

    return desired_move_col;
}


bool GameBoard::is_full() const {
    for (int i = 0; i < m_rows; i++) {
        for (int j = 0; j < m_cols; j++) {
            if (m_board.at(i).at(j).id == EMPTY_SPOT) {
                return false;
            }
        }
    }
    return true;
}


bool GameBoard::is_valid_move(const int desired_move_col) const {
    if (desired_move_col < 0 || desired_move_col >= m_cols) {
        return false;
    }

    // look from the bottom up until we find an empty spot
    for (int i = 0; i < m_rows; i++) {
        if (m_board.at(i).at(desired_move_col).id == EMPTY_SPOT) {
            return true;
        }
    }

    return false;
}


std::vector<int> GameBoard::get_possible_column_moves() const {
    std::vector<int> available_columns;
    for (int i = 0; i < m_cols; i++) {
        if (is_valid_move(i)) {
            available_columns.push_back(i);
        }
    }
    return available_columns;
}


std::optional<Coordinate2D> GameBoard::get_move(const Player& player) {
    switch (player.type) {
        case PlayerType::HUMAN:
            return play_move(player);
        case PlayerType::COMPUTER:
            return play_generated_move(player);
        default:
            std::cout << "Error: Unknown player type" << std::endl;
            return std::nullopt;
    }
}


std::optional<Coordinate2D> GameBoard::play_move(const Player& player) {
    std::optional<int> desired_move_col = ask_desired_move();
    if (!desired_move_col.has_value()) {
        return std::nullopt;
    }

    if (desired_move_col < 0 || desired_move_col >= m_cols) {
        std::cout << "Invalid move (column " << desired_move_col.value() << "), please enter a valid move" << std::endl;
        return std::nullopt;
    }

    std::optional<Coordinate2D> player_desired_move = apply_gravity(desired_move_col.value());
    if (!player_desired_move.has_value()) {
        return std::nullopt;
    }

    m_board.at(player_desired_move.value().x).at(player_desired_move.value().y) = player;
    return player_desired_move;
}


std::optional<Coordinate2D> GameBoard::generate_move() const {
    std::vector<int> available_columns = get_possible_column_moves();
    if (available_columns.empty()) {
        return std::nullopt; // No moves available
    }
    const int random_index = generate_random_number(0, available_columns.size() - 1);
    const int random_column = available_columns.at(random_index);
    std::optional<Coordinate2D> generated_move = apply_gravity(random_column);
    return generated_move;
}


std::optional<Coordinate2D> GameBoard::play_generated_move(const Player& player) {
    // we can directly play the move, because the validated in generate_move()
    std::optional<Coordinate2D> generated_move = generate_move();
    if (generated_move.has_value()) {
        m_board.at(generated_move.value().x).at(generated_move.value().y) = player;
        return generated_move;
    }
    return std::nullopt;
}


std::optional<Coordinate2D> GameBoard::apply_gravity(const int desired_move_col) const {
    for (int i = m_rows - 1; i >= 0; i--) {
        if (m_board.at(i).at(desired_move_col).id == EMPTY_SPOT) {
            return Coordinate2D {i, desired_move_col };
        }
    }
    return std::nullopt;
}


bool GameBoard::hardcode_move(const Player& player, const Coordinate2D& coordinate) {
    if (coordinate.x >= 0 && coordinate.x < m_rows
        && coordinate.y >= 0 && coordinate.x < m_cols) {
        m_board.at(coordinate.x).at(coordinate.y) = player;
        return true;
        }
    return false;
}


std::optional<Coordinate2D> GameBoard::drop_move_on_column(const Player& player, const int col) {
    if (col < 0 || col > m_cols) {
        return std::nullopt;
    }
    std::optional<Coordinate2D> move = apply_gravity(col);
    if (move.has_value()) {
        m_board.at(move.value().x).at(move.value().y) = player;
        return move.value();
    }
    return std::nullopt;
}


std::optional<Player> GameBoard::at(const int row, const int col) const {
    if (row < 0 || row >= m_rows) {
        std::cout << "Requested check on invalid row " << row << std::endl;
        return std::nullopt;
    }
    if (col < 0 || col >= m_cols) {
        std::cout << "Requested check on invalid col " << col << std::endl;
        return std::nullopt;
    }
    return m_board.at(row).at(col);
}


const std::vector<std::unique_ptr<WinConditionStrategy>>& GameBoard::get_win_condition_strategies() const {
    return m_win_condition_strategies;
}


int GameBoard::rows() const {
    return m_rows;
}


int GameBoard::cols() const {
    return m_cols;
}