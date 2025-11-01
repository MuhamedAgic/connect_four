#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

struct Coordinate2D {
    int x = 0;
    int y = 0;
};

std::ostream& operator<<(std::ostream& os, const Coordinate2D& coordinate);

#endif //COORDINATE_H
