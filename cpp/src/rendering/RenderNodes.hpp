#ifndef RENDER_NODES_HPP
#define RENDER_NODES_HPP

#include <SFML/Graphics.hpp>

class RenderNodes {
public:
    RenderNodes(const std::vector<std::pair<float, float>>& coords, const std::vector<bool>& keep_node, const std::vector<bool>& selected);
    void draw(sf::RenderWindow& window) const;

private:
    const std::vector<std::pair<float, float>>& coords;
    const std::vector<bool>& keep_node;
    const std::vector<bool>& selected;
};

#endif // RENDER_NODES_HPP
