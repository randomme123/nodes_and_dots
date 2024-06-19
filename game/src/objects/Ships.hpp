#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "Graph.hpp"

class Ship {
public:
    Ship(const std::pair<float, float>& start_position, const Graph& graph, GraphManager& graphManager, float speed);

    void update();
    void findNewDestination();

    void setSelected(bool selected);
    bool isSelected() const;

    std::pair<float, float> getPosition() const;
    float getOrientation() const;
    const std::vector<size_t>& getPath() const;
    size_t getPathIndex() const;

private:
    std::pair<float, float> position;
    const Graph& graph;
    GraphManager& graphManager;
    std::vector<size_t> path;
    size_t path_index;
    float speed;
    float orientation;
    bool selected;
};

std::vector<Ship> createShips(int num_ships, const std::vector<std::pair<float, float>>& coords, const Graph& graph, GraphManager& graphManager, float speed);

#endif // SHIPS_HPP



