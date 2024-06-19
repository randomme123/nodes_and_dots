#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <string>
#include <map>
#include <memory>
#include <utility>
#include <chrono>
#include <random>
#include <iostream>
#include "Graph.hpp"
#include "StructureConfig.hpp"
#include <SFML/Graphics.hpp>

// Resource type
using Resource = std::string;

class Structure {
public:
    virtual ~Structure() {}
    virtual void update() = 0;
    virtual std::string type() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual sf::Color getColor() const = 0;

protected:
    std::chrono::time_point<std::chrono::steady_clock> nextUpdateTime;
    std::mt19937 rng;

    bool isTimeToUpdate() {
        return std::chrono::steady_clock::now() >= nextUpdateTime;
    }

    void setNextUpdateTime() {
        std::uniform_int_distribution<int> dist(0, 12);
        int seconds = dist(rng);
        nextUpdateTime = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
    }

    Structure() {
        rng.seed(std::random_device{}());
        setNextUpdateTime();
    }
};

class BaseStructure : public Structure {
public:
    BaseStructure(const sf::Vector2f& pos, const sf::Color& col, std::map<Resource, int> input, std::map<Resource, int> output)
        : position(pos), color(col), inputResources(input), outputResources(output) {}

    sf::Vector2f getPosition() const override { return position; }
    sf::Color getColor() const override { return color; }

protected:
    sf::Vector2f position;
    sf::Color color;
    std::map<Resource, int> inputResources;
    std::map<Resource, int> outputResources;

    bool processResources(const std::map<Resource, int>& requiredInput, const std::map<Resource, int>& producedOutput) {
        bool canProduce = true;
        for (const auto& [resource, amount] : requiredInput) {
            if (inputResources[resource] < amount) {
                canProduce = false;
                break;
            }
        }

        if (canProduce) {
            for (const auto& [resource, amount] : requiredInput) {
                inputResources[resource] -= amount;
            }
            for (const auto& [resource, amount] : producedOutput) {
                outputResources[resource] += amount;
            }
            return true;
        }
        return false;
    }

    void printResources() const {
        std::cout << "Input Resources: ";
        for (const auto& [resource, amount] : inputResources) {
            std::cout << resource << ": " << amount << " ";
        }
        std::cout << "| Output Resources: ";
        for (const auto& [resource, amount] : outputResources) {
            std::cout << resource << ": " << amount << " ";
        }
        std::cout << std::endl;
    }
};

// Derived structure implementations...
class CoalMine : public BaseStructure {
public:
    CoalMine(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {}, {{"coal", 0}}) {}

    void update() override {
        if (isTimeToUpdate()) {
            outputResources["coal"] += 100;  // Producing coal
            printResources();
            setNextUpdateTime();
        }
    }
    std::string type() const override { return "CoalMine"; }
};

class IronMine : public BaseStructure {
public:
    IronMine(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {}, {{"iron ore", 0}}) {}

    void update() override {
        if (isTimeToUpdate()) {
            outputResources["iron ore"] += 100;  // Producing iron ore
            printResources();
            setNextUpdateTime();
        }
    }
    std::string type() const override { return "IronMine"; }
};

class CoalPowerPlant : public BaseStructure {
public:
    CoalPowerPlant(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {{"coal", 0}}, {{"energy", 0}}) {}

    void update() override {
        if (isTimeToUpdate() && processResources({{"coal", 100}}, {{"energy", 100}})) {
            printResources();
            setNextUpdateTime();
        }
    }
    std::string type() const override { return "CoalPowerPlant"; }
};

class IronSmelter : public BaseStructure {
public:
    IronSmelter(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {{"iron ore", 0}}, {{"iron", 0}}) {}

    void update() override {
        if (isTimeToUpdate() && processResources({{"iron ore", 100}}, {{"iron", 100}})) {
            printResources();
            setNextUpdateTime();
        }
    }
    std::string type() const override { return "IronSmelter"; }
};

class SteelFoundry : public BaseStructure {
public:
    SteelFoundry(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {{"coal", 0}, {"iron", 0}}, {{"steel", 0}}) {}

    void update() override {
        if (isTimeToUpdate() && processResources({{"coal", 100}, {"iron", 100}}, {{"steel", 100}})) {
            printResources();
            setNextUpdateTime();
        }
    }
    std::string type() const override { return "SteelFoundry"; }
};

class Storage : public BaseStructure {
public:
    Storage(const sf::Vector2f& pos, const sf::Color& col)
        : BaseStructure(pos, col, {}, {{"coal", 0}, {"iron ore", 0}, {"iron", 0}, {"energy", 0}, {"steel", 0}}) {}

    void update() override {
        // No operation for storage
    }
    std::string type() const override { return "Storage"; }
};

std::unique_ptr<Structure> createStructure(const std::string& type, const sf::Vector2f& position, const sf::Color& color);
std::vector<std::unique_ptr<Structure>> createStructures(const std::vector<StructureConfig>& configs, const GraphManager& graphManager);

#endif // STRUCTURES_HPP
