#include "RenderEdges.hpp"
#include <boost/graph/graph_traits.hpp>

RenderEdges::RenderEdges(const Graph& graph, const std::vector<std::pair<float, float>>& coords)
    : graph(graph), coords(coords) {}

void RenderEdges::draw(sf::RenderWindow& window, const std::vector<int>& path) const {
    auto edges = boost::edges(graph);
    for (auto it = edges.first; it != edges.second; ++it) {
        auto u = boost::source(*it, graph);
        auto v = boost::target(*it, graph);
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(coords[u].first, coords[u].second), sf::Color(0, 255, 0, 40)),
            sf::Vertex(sf::Vector2f(coords[v].first, coords[v].second), sf::Color(0, 255, 0, 40))
        };

        bool is_edge_in_path = false;
        if (!path.empty()) {
            for (size_t j = 0; j < path.size() - 1; ++j) {
                if ((path[j] == u && path[j + 1] == v) || (path[j] == v && path[j + 1] == u)) {
                    is_edge_in_path = true;
                    break;
                }
            }
        }

        if (is_edge_in_path) {
            line[0].color = sf::Color(255, 0, 255, 255);
            line[1].color = sf::Color(255, 0, 255, 255);
            window.draw(line, 2, sf::Lines);
        } else {
            window.draw(line, 2, sf::Lines);
        }
    }
}
