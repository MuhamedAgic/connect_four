#ifndef PLAYER_H
#define PLAYER_H

#include <string>


enum class PlayerType {
    HUMAN,
    COMPUTER
};


struct Player {
    int id;
    PlayerType type;
    std::string marker;
    bool operator==(const Player& player) const;
};


#endif //PLAYER_H
