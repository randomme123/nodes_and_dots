#include "RenderNodes.hpp"

RenderNodes::RenderNodes(const std::vector<std::pair<float, float>>& coords, const std::vector<bool>& keep_node, const std::vector<bool>& selected)
    : coords(coords), keep_node(keep_node), selected(selected) {}

void RenderNodes::draw(sf::RenderWindow& window) const {
    for (size_t i = 0; i < coords.size(); ++i) {
        if (!keep_node[i]) continue;
        sf::CircleShape circle(1);
        circle.setPosition(coords[i].first - circle.getRadius(), coords[i].second - circle.getRadius());
        if (selected[i]) {
            circle.setFillColor(sf::Color::Red);
        } else {
            circle.setFillColor(sf::Color::Red);
        }
        window.draw(circle);
    }
}
