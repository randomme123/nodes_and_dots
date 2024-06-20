#include "RenderStructures.hpp"

RenderStructures::RenderStructures(const std::vector<std::unique_ptr<Structure>>& structures) : structures(structures) {}

void RenderStructures::draw(sf::RenderWindow& window, Structure* selected_structure) const {
    for (const auto& structure : structures) {
        sf::RectangleShape structure_shape(sf::Vector2f(10, 10));
        if (structure.get() == selected_structure) {
            structure_shape.setSize(sf::Vector2f(30, 30)); // Render extra large if selected
            structure_shape.setFillColor(sf::Color::Yellow); // Highlight color
        } else {
            structure_shape.setFillColor(structure->getColor());
        }
        sf::Vector2f position = structure->getPosition();
        structure_shape.setPosition(position.x - structure_shape.getSize().x / 2, position.y - structure_shape.getSize().y / 2);
        window.draw(structure_shape);
    }
}
