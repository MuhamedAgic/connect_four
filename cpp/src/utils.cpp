#include <random>
#include "utils.h"

int generate_random_number(int min_range, int max_range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min_range, max_range);
    int random_number = distr(gen);
    return random_number;
}


void print_coordinates(const std::vector<Coordinate2D>& coordinates) {
    for (int j = 0; j < coordinates.size(); j++) {
        std::cout << coordinates.at(j);
        if (j != coordinates.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}


bool confirms() {
    std::string input;
    std::cin >> input;
    if (input == "y") {
        return true;
    }
    else if (input == "n") {
        return false;
    }
    std::cout << "please type 'y' or 'n'" << std::endl;
    return confirms();
}
