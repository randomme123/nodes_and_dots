#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Graph.hpp"
#include "Render.hpp"
#include "Ships.hpp"
#include "StructureConfig.hpp"
#include "Structures.hpp"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Constants configuration
    const int grid_size = 12; // Grid Size
    const int nodes_per_cell = 24; // nodes per cell
    const float field_size = 4000.0f; // Field size of 4000x4000
    const float viewport_width = 1500.0f;
    const float viewport_height = 900.0f;
    const int ships_amount = 250; // Amount of Ships to create
    const float ship_speed = 3.0f; // Speed of the ships

    // Constants configuration for structures
    const std::vector<StructureConfig> structureConfigs = {
        {"CoalMine", sf::Color(128, 128, 128, 255), 100},           // Gray
        {"IronMine", sf::Color(183, 65, 14, 255), 100},             // Rusty
        {"CoalPowerPlant", sf::Color(255, 255, 0, 255), 100},       // Yellow
        {"IronSmelter", sf::Color(183, 65, 14, 255), 100},          // Rusty
        {"SteelFoundry", sf::Color(192, 192, 192, 255), 100},       // Steel
        {"Storage", sf::Color(0, 128, 255, 255), 100}               // Steel
    };

    // Create the grid Manager, Generate grid coordinates, Create the graph, filter largest connected component and get the keep_node vector
    GraphManager graphManager(grid_size, nodes_per_cell, field_size);
    vector<pair<float, float>> coords = graphManager.generate_coordinates();
    Graph g = graphManager.create_graph(coords);
    Graph filtered_g = graphManager.filter_largest_component(g, coords);
    const vector<bool>& keep_node = graphManager.get_keep_node();

    // Create structures
    vector<std::unique_ptr<Structure>> structures = createStructures(structureConfigs, graphManager);

    // Create ships
    vector<Ship> ships = createShips(ships_amount, coords, filtered_g, graphManager, ship_speed);

    // Create and run the renderer
    Renderer renderer(viewport_width, viewport_height, field_size, coords, filtered_g, keep_node, graphManager, ships, structures);
    renderer.run();

    return 0;
}
