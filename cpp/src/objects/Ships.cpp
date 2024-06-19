#include "Ships.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cmath>

Ship::Ship(const std::pair<float, float>& start_position, const Graph& graph, GraphManager& graphManager, float speed)
    : position(start_position), graph(graph), graphManager(graphManager), path_index(0), speed(speed), orientation(0.0f), selected(false) {
    findNewDestination();
}

void Ship::update() {
    if (path_index < path.size() - 1) {
        assert(path_index + 1 < graphManager.get_coords().size());
        auto target = graphManager.get_coords()[path[path_index + 1]];
        float dx = static_cast<float>(target.first - position.first);
        float dy = static_cast<float>(target.second - position.second);
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance > speed) {
            position.first += dx / distance * speed;
            position.second += dy / distance * speed;
            orientation = std::atan2(dy, dx) * 180.0f / 3.14159265f - 30.0f; // Convert radians to degrees and adjust
        } else {
            position = target;
            path_index++;
        }
    } else {
        findNewDestination();
    }
}

void Ship::findNewDestination() {
    const auto& coords = graphManager.get_coords();
    const auto& keep_node = graphManager.get_keep_node();  // Ensure this method returns a const reference to the keep_node vector

    // Filter to get indices of valid coordinates
    std::vector<size_t> valid_indices;
    for (size_t i = 0; i < coords.size(); ++i) {
        if (keep_node[i]) {
            valid_indices.push_back(i);
        }
    }

    assert(!valid_indices.empty());

    // Find current position index among valid coordinates
    auto current_position_it = std::find(coords.begin(), coords.end(), position);
    assert(current_position_it != coords.end());  // Ensure current position is in the list
    size_t current_index = std::distance(coords.begin(), current_position_it);
    
    if (!keep_node[current_index]) {
        // Current position is not valid, find the nearest valid
        // This is a fallback, ideally this situation should be managed to not happen
        auto nearest_valid = std::min_element(valid_indices.begin(), valid_indices.end(), [&](size_t a, size_t b) {
            float da = std::hypot(static_cast<float>(coords[a].first - position.first), static_cast<float>(coords[a].second - position.second));
            float db = std::hypot(static_cast<float>(coords[b].first - position.first), static_cast<float>(coords[b].second - position.second));
            return da < db;
        });
        current_index = *nearest_valid;
        position = coords[current_index];  // Update the ship's position to the nearest valid position
    }

    // Randomly choose a destination from valid indices
    size_t goal_index = valid_indices[std::rand() % valid_indices.size()];

    assert(current_index < coords.size());
    assert(goal_index < coords.size());

    auto int_path = graphManager.compute_shortest_path(graph, static_cast<int>(current_index), static_cast<int>(goal_index));
    path = std::vector<size_t>(int_path.begin(), int_path.end());
    path_index = 0;
}

void Ship::setSelected(bool selected) {
    this->selected = selected;
}

bool Ship::isSelected() const {
    return selected;
}

std::pair<float, float> Ship::getPosition() const {
    return position;
}

float Ship::getOrientation() const {
    return orientation;
}

const std::vector<size_t>& Ship::getPath() const {
    return path;
}

size_t Ship::getPathIndex() const {
    return path_index;
}

std::vector<Ship> createShips(int num_ships, const std::vector<std::pair<float, float>>& coords, const Graph& graph, GraphManager& graphManager, float speed) {
    std::vector<Ship> ships;
    std::srand(static_cast<unsigned int>(std::time(0)));

    std::vector<std::pair<float, float>> valid_coords = graphManager.get_valid_coords();
    
    for (int i = 0; i < num_ships; ++i) {
        size_t index = std::rand() % valid_coords.size();
        assert(index < valid_coords.size());
        ships.emplace_back(valid_coords[index], graph, graphManager, speed);
    }

    return ships;
}
