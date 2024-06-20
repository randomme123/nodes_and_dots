#ifndef RENDER_HPP
#define RENDER_HPP

#include <SFML/Graphics.hpp>
#include "Graph.hpp"
#include "Ships.hpp"
#include "Structures.hpp"
#include <vector>
#include <memory>
#include "RenderEdges.hpp"
#include "RenderNodes.hpp"
#include "RenderShips.hpp"
#include "RenderStructures.hpp"

class Renderer {
public:
    Renderer(float viewport_width, float viewport_height, float field_size,
             const std::vector<std::pair<float, float>>& coords,
             const Graph& graph, const std::vector<bool>& keep_node,
             GraphManager& graphManager, std::vector<Ship>& ships,
             const std::vector<std::unique_ptr<Structure>>& structures);
    
    void run();

private:
    void processEvents();
    void handleMousePress(sf::Event::MouseButtonEvent& mouseButton);
    void handleMouseWheelScroll(sf::Event::MouseWheelScrollEvent& mouseWheel);
    void handleKeyPress(sf::Event::KeyEvent& key);
    void render();

    float viewport_width;
    float viewport_height;
    float field_size;
    const std::vector<std::pair<float, float>>& coords;
    const Graph& graph;
    const std::vector<bool>& keep_node;
    GraphManager& graphManager;
    std::vector<Ship>& ships;
    const std::vector<std::unique_ptr<Structure>>& structures;
    sf::RenderWindow window;
    sf::View view;
    std::vector<bool> selected;
    Ship* selected_ship;
    Structure* selected_structure; // Added this line to declare 'selected_structure'
    std::vector<int> selected_nodes;
    std::vector<int> path;

    RenderEdges renderEdges;
    RenderNodes renderNodes;
    RenderShips renderShips;
    RenderStructures renderStructures;
};

#endif // RENDER_HPP
