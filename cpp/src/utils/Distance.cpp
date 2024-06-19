// Distance.cpp

#include "Distance.hpp"

float euclidean_distance(const std::pair<float, float>& a, const std::pair<float, float>& b) {
    return static_cast<float>(std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2)));
}
