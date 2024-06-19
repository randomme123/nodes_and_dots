#include "Structures.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

std::unique_ptr<Structure> createStructure(const std::string& type, const sf::Vector2f& position, const sf::Color& color) {
    if (type == "CoalMine") {
        return std::make_unique<CoalMine>(position, color);
    } else if (type == "IronMine") {
        return std::make_unique<IronMine>(position, color);
    } else if (type == "CoalPowerPlant") {
        return std::make_unique<CoalPowerPlant>(position, color);
    } else if (type == "IronSmelter") {
        return std::make_unique<IronSmelter>(position, color);
    } else if (type == "SteelFoundry") {
        return std::make_unique<SteelFoundry>(position, color);
    } else if (type == "Storage") {
        return std::make_unique<Storage>(position, color);
    } else {
        return nullptr;
    }
}

std::vector<std::unique_ptr<Structure>> createStructures(const std::vector<StructureConfig>& configs, const GraphManager& graphManager) {
    std::vector<std::unique_ptr<Structure>> structures;
    const auto& coords = graphManager.get_coords();
    const auto& keep_node = graphManager.get_keep_node();

    for (const auto& config : configs) {
        for (int i = 0; i < config.count; ++i) {
            size_t index;
            do {
                index = std::rand() % coords.size();
            } while (!keep_node[index]);

            auto structure = createStructure(config.type, sf::Vector2f(coords[index].first, coords[index].second), config.color);
            if (structure) {
                structures.push_back(std::move(structure));
            }
        }
    }

    return structures;
}

