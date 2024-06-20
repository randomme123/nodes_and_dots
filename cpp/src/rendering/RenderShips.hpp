#ifndef RENDER_SHIPS_HPP
#define RENDER_SHIPS_HPP

#include <SFML/Graphics.hpp>
#include "Ships.hpp"
#include <vector>
#include <utility>

class RenderShips {
public:
    RenderShips(std::vector<Ship>& ships, const std::vector<std::pair<float, float>>& coords);
    void draw(sf::RenderWindow& window, Ship* selected_ship) const;

private:
    std::vector<Ship>& ships;
    const std::vector<std::pair<float, float>>& coords;
};

#endif // RENDER_SHIPS_HPP

