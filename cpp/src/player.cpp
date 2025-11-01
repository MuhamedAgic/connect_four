#include "player.h"

bool Player::operator==(const Player& player) const {
    return id == player.id && type == player.type && marker == player.marker;
}
