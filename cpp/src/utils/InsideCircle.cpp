// InsideCircle.cpp

#include "InsideCircle.hpp"
#include <cmath>

bool is_inside_circle(float px, float py, float cx, float cy, float radius) {
    return std::sqrt((px - cx) * (px - cx) + (py - cy) * (py - cy)) <= radius;
}