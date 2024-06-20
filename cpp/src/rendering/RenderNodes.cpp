#include "RenderNodes.hpp"

RenderNodes::RenderNodes(const std::vector<std::pair<float, float>>& coords, const std::vector<bool>& keep_node, const std::vector<bool>& selected)
    : coords(coords), keep_node(keep_node), selected(selected) {}

void RenderNodes::draw(sf::RenderWindow& window, const std::vector<int>& selected_nodes) const {
    for (size_t i = 0; i < coords.size(); ++i) {
        if (keep_node[i]) {
            sf::CircleShape node_shape(5);
            node_shape.setFillColor(sf::Color::Green);

            if (std::find(selected_nodes.begin(), selected_nodes.end(), i) != selected_nodes.end()) {
                node_shape.setRadius(10); // Render extra large if selected
                node_shape.setFillColor(sf::Color::Yellow); // Highlight color
            }

            node_shape.setPosition(coords[i].first - node_shape.getRadius(), coords[i].second - node_shape.getRadius());
            window.draw(node_shape);
        }
    }
}

