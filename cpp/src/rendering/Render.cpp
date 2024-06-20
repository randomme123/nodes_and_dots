#include "Render.hpp"
#include "utils/InsideCircle.hpp"
#include <iostream>
#include <algorithm>

// Constructor
Renderer::Renderer(float viewport_width, float viewport_height, float field_size,
                   const std::vector<std::pair<float, float>>& coords,
                   const Graph& graph, const std::vector<bool>& keep_node,
                   GraphManager& graphManager, std::vector<Ship>& ships,
                   const std::vector<std::unique_ptr<Structure>>& structures)
    : viewport_width(viewport_width), viewport_height(viewport_height), field_size(field_size),
      coords(coords), graph(graph), keep_node(keep_node), graphManager(graphManager), ships(ships), structures(structures),
      window(sf::VideoMode(static_cast<int>(viewport_width), static_cast<int>(viewport_height)), "Graph Visualization"),
      view(sf::FloatRect((field_size - viewport_width) / 2, (field_size - viewport_height) / 2, viewport_width, viewport_height)),
      selected(coords.size(), false), selected_ship(nullptr), selected_structure(nullptr),
      renderEdges(graph, coords), renderNodes(coords, keep_node, selected), renderShips(ships, coords), renderStructures(structures) {
    window.setView(view);
}

// Run the Renderer
void Renderer::run() {
    while (window.isOpen()) {
        processEvents();

        for (auto& ship : ships) {
            ship.update();
        }

        for (auto& structure : structures) {
            structure->update();
        }

        render();
    }
}

// Process Events
void Renderer::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            handleMousePress(event.mouseButton);
        } else if (event.type == sf::Event::MouseWheelScrolled) {
            handleMouseWheelScroll(event.mouseWheelScroll);
        } else if (event.type == sf::Event::KeyPressed) {
            handleKeyPress(event.key);
        }
    }
}

// Handle Mouse Press
void Renderer::handleMousePress(sf::Event::MouseButtonEvent& mouseButton) {
    if (mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f world_pos = window.mapPixelToCoords(sf::Vector2i(mouseButton.x, mouseButton.y));
        float mouseX = world_pos.x;
        float mouseY = world_pos.y;

        // Node selection
        bool node_selected = false;
        for (size_t i = 0; i < coords.size(); ++i) {
            if (is_inside_circle(mouseX, mouseY, coords[i].first, coords[i].second, 25)) {
                selected[i] = !selected[i];
                if (selected[i]) {
                    selected_nodes.push_back(static_cast<int>(i));
                    if (selected_nodes.size() > 2) {
                        selected[selected_nodes[0]] = false;
                        selected_nodes.erase(selected_nodes.begin());
                    }
                } else {
                    selected_nodes.erase(std::remove(selected_nodes.begin(), selected_nodes.end(), static_cast<int>(i)), selected_nodes.end());
                }
                node_selected = true;
                break;
            }
        }

        // Ship selection
        if (!node_selected) {
            for (auto& ship : ships) {
                if (is_inside_circle(mouseX, mouseY, ship.getPosition().first, ship.getPosition().second, 25)) {
                    if (selected_ship) {
                        selected_ship->setSelected(false);
                    }
                    selected_ship = &ship;
                    selected_ship->setSelected(true);
                    break;
                }
            }
        }

        // Structure selection
        if (!node_selected && !selected_ship) {
            for (auto& structure : structures) {
                if (is_inside_circle(mouseX, mouseY, structure->getPosition().x, structure->getPosition().y, 25)) {
                    selected_structure = structure.get();
                    break;
                }
            }
        }

        // Compute shortest path if two nodes are selected
        if (selected_nodes.size() == 2) {
            path = graphManager.compute_shortest_path(graph, selected_nodes[0], selected_nodes[1]);
            if (path.empty()) {
                std::cout << "No path found between " << selected_nodes[0] << " and " << selected_nodes[1] << std::endl;
            }
        } else {
            path.clear();
        }
    }
}

// Handle Mouse Wheel Scroll
void Renderer::handleMouseWheelScroll(sf::Event::MouseWheelScrollEvent& mouseWheel) {
    if (mouseWheel.delta > 0) {
        view.zoom(0.9f);
    } else if (mouseWheel.delta < 0) {
        view.zoom(1.1f);
    }
    window.setView(view);
}

// Handle Key Press
void Renderer::handleKeyPress(sf::Event::KeyEvent& key) {
    if (key.code == sf::Keyboard::Left) {
        view.move(-50, 0);
    } else if (key.code == sf::Keyboard::Right) {
        view.move(50, 0);
    } else if (key.code == sf::Keyboard::Up) {
        view.move(0, -50);
    } else if (key.code == sf::Keyboard::Down) {
        view.move(0, 50);
    }
    window.setView(view);
}

// Render the Scene
void Renderer::render() {
    window.clear(sf::Color::Black);

    renderEdges.draw(window, path);
    renderNodes.draw(window, selected_nodes); // Pass selected nodes
    renderShips.draw(window, selected_ship); 
    renderStructures.draw(window, selected_structure); // Pass selected structure

    window.display();
}
