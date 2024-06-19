#include "RenderStructures.hpp"

RenderStructures::RenderStructures(const std::vector<std::unique_ptr<Structure>>& structures) : structures(structures) {}

void RenderStructures::draw(sf::RenderWindow& window) const {
    for (const auto& structure : structures) {
        sf::RectangleShape structure_shape(sf::Vector2f(10, 10));
        structure_shape.setFillColor(structure->getColor());
        sf::Vector2f position = structure->getPosition();
        structure_shape.setPosition(position.x - structure_shape.getSize().x / 2, position.y - structure_shape.getSize().y / 2);
        window.draw(structure_shape);
    }
}
