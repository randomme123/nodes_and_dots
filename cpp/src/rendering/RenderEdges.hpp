#ifndef RENDER_EDGES_HPP
#define RENDER_EDGES_HPP

#include <SFML/Graphics.hpp>
#include "Graph.hpp"

class RenderEdges {
public:
    RenderEdges(const Graph& graph, const std::vector<std::pair<float, float>>& coords);
    void draw(sf::RenderWindow& window, const std::vector<int>& path) const;

private:
    const Graph& graph;
    const std::vector<std::pair<float, float>>& coords;
};

#endif // RENDER_EDGES_HPP