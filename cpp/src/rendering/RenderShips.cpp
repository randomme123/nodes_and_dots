#include "RenderShips.hpp"
#include "utils/InsideCircle.hpp"
#include <cmath> // For std::sqrt

RenderShips::RenderShips(std::vector<Ship>& ships, const std::vector<std::pair<float, float>>& coords)
    : ships(ships), coords(coords) {}

void RenderShips::draw(sf::RenderWindow& window, Ship* selected_ship) const {
    // Get the current mouse position relative to the window
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    for (auto& ship : ships) {
        sf::ConvexShape triangle;
        triangle.setPointCount(3);

        // Define the points of the triangle (assuming an equilateral triangle)
        float size = 16.0f; // Size of the triangle
        float halfSize = size / 2.0f;
        float height = std::sqrt(3.0f) / 2.0f * size;

        triangle.setPoint(0, sf::Vector2f(0.0f, -2.0f * halfSize / std::sqrt(3.0f)));
        triangle.setPoint(1, sf::Vector2f(-halfSize, halfSize / std::sqrt(3.0f)));
        triangle.setPoint(2, sf::Vector2f(halfSize, halfSize / std::sqrt(3.0f)));

        // Set the fill color
        triangle.setFillColor(sf::Color::Blue);

        // Rotate the triangle according to the ship's orientation
        triangle.setRotation(ship.getOrientation());

        // Move the triangle to the ship's position (centroid alignment)
        triangle.setPosition(ship.getPosition().first, ship.getPosition().second);

        // Draw the triangle
        window.draw(triangle);

        // Check if the mouse is near the ship
        if (is_inside_circle(worldPos.x, worldPos.y, ship.getPosition().first, ship.getPosition().second, 20)) {
            sf::CircleShape proximity_circle(10);
            proximity_circle.setFillColor(sf::Color::Transparent);
            proximity_circle.setOutlineThickness(1);
            proximity_circle.setOutlineColor(sf::Color::Yellow);
            proximity_circle.setPosition(ship.getPosition().first - proximity_circle.getRadius(), ship.getPosition().second - proximity_circle.getRadius());
            window.draw(proximity_circle);
        }
        if (ship.isSelected()) {
            sf::CircleShape selected_circle(10);
            selected_circle.setFillColor(sf::Color::Transparent);
            selected_circle.setOutlineThickness(1);
            selected_circle.setOutlineColor(sf::Color::Red);
            selected_circle.setPosition(ship.getPosition().first - selected_circle.getRadius(), ship.getPosition().second - selected_circle.getRadius());
            window.draw(selected_circle);

            // Draw the remaining path for the selected ship
            const auto& ship_path = ship.getPath();
            for (size_t i = ship.getPathIndex(); i < ship_path.size() - 1; ++i) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(coords[ship_path[i]].first, coords[ship_path[i]].second), sf::Color(255, 0, 255, 255)),
                    sf::Vertex(sf::Vector2f(coords[ship_path[i + 1]].first, coords[ship_path[i + 1]].second), sf::Color(255, 0, 255, 255))
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }
}
