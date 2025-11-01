#include "coordinate_2d.h"

std::ostream& operator<<(std::ostream& os, const Coordinate2D& coordinate) {
    os << "(" << coordinate.x << ", " << coordinate.y << ")";
    return os;
}