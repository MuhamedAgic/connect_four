#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include "coordinate_2d.h"

int generate_random_number(int min_range, int max_range);
void print_coordinates(const std::vector<Coordinate2D>& coordinates);
bool confirms();

#endif // UTILS_H