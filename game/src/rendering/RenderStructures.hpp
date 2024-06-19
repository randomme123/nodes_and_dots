#ifndef RENDER_STRUCTURES_HPP
#define RENDER_STRUCTURES_HPP

#include <SFML/Graphics.hpp>
#include "Structures.hpp"

class RenderStructures {
public:
    RenderStructures(const std::vector<std::unique_ptr<Structure>>& structures);
    void draw(sf::RenderWindow& window) const;

private:
    const std::vector<std::unique_ptr<Structure>>& structures;
};

#endif // RENDER_STRUCTURES_HPP
