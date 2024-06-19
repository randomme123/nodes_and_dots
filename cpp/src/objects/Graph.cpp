// Graph.cpp

#include "Graph.hpp"
#include "utils/Distance.hpp"
#include <algorithm>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

GraphManager::GraphManager(int grid_size, int nodes_per_cell, float field_size)
    : grid_size(grid_size), nodes_per_cell(nodes_per_cell), field_size(field_size) {}

std::vector<std::pair<float, float>> GraphManager::generate_coordinates() {
    coords.clear();
    float cell_size = field_size / grid_size;
    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            float cell_x = i * cell_size;
            float cell_y = j * cell_size;
            for (int k = 0; k < nodes_per_cell; ++k) {
                float x = cell_x + static_cast<float>(rand()) / RAND_MAX * cell_size;
                float y = cell_y + static_cast<float>(rand()) / RAND_MAX * cell_size;
                coords.emplace_back(x, y);
            }
        }
    }
    return coords;
}

Graph GraphManager::create_graph(const std::vector<std::pair<float, float>>& coords) {
    std::vector<Edge> edge_array;
    std::vector<float> weights;
    float cell_size = field_size / grid_size;

    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            size_t cell_start = static_cast<size_t>(i * grid_size + j) * nodes_per_cell;
            size_t cell_end = cell_start + nodes_per_cell;
            for (size_t k = cell_start; k < cell_end; ++k) {
                std::vector<std::pair<float, size_t>> distances;
                for (size_t l = cell_start; l < cell_end; ++l) {
                    if (k != l) {
                        float distance = euclidean_distance(coords[k], coords[l]);
                        distances.emplace_back(distance, l);
                    }
                }
                std::sort(distances.begin(), distances.end());
                for (size_t m = 0; m < 3; ++m) {
                    edge_array.emplace_back(static_cast<int>(k), static_cast<int>(distances[m].second));
                    weights.push_back(distances[m].first);
                }
            }
        }
    }

    for (int i = 0; i < grid_size; ++i) {
        for (int j = 0; j < grid_size; ++j) {
            size_t cell_start = static_cast<size_t>(i * grid_size + j) * nodes_per_cell;
            size_t cell_end = cell_start + nodes_per_cell;
            if (j + 1 < grid_size) {
                size_t neighbor_start = static_cast<size_t>(i * grid_size + (j + 1)) * nodes_per_cell;
                size_t neighbor_end = neighbor_start + nodes_per_cell;
                float min_distance = std::numeric_limits<float>::max();
                size_t min_u = -1, min_v = -1;
                for (size_t u = cell_start; u < cell_end; ++u) {
                    for (size_t v = neighbor_start; v < neighbor_end; ++v) {
                        float distance = euclidean_distance(coords[u], coords[v]);
                        if (distance < min_distance) {
                            min_distance = distance;
                            min_u = u;
                            min_v = v;
                        }
                    }
                }
                if (min_u != static_cast<size_t>(-1) && min_v != static_cast<size_t>(-1)) {
                    edge_array.emplace_back(static_cast<int>(min_u), static_cast<int>(min_v));
                    weights.push_back(min_distance);
                }
            }
            if (i + 1 < grid_size) {
                size_t neighbor_start = static_cast<size_t>((i + 1) * grid_size + j) * nodes_per_cell;
                size_t neighbor_end = neighbor_start + nodes_per_cell;
                float min_distance = std::numeric_limits<float>::max();
                size_t min_u = -1, min_v = -1;
                for (size_t u = cell_start; u < cell_end; ++u) {
                    for (size_t v = neighbor_start; v < neighbor_end; ++v) {
                        float distance = euclidean_distance(coords[u], coords[v]);
                        if (distance < min_distance) {
                            min_distance = distance;
                            min_u = u;
                            min_v = v;
                        }
                    }
                }
                if (min_u != static_cast<size_t>(-1) && min_v != static_cast<size_t>(-1)) {
                    edge_array.emplace_back(static_cast<int>(min_u), static_cast<int>(min_v));
                    weights.push_back(min_distance);
                }
            }
        }
    }

    return Graph(edge_array.begin(), edge_array.end(), weights.begin(), coords.size());
}

Graph GraphManager::filter_largest_component(const Graph& g, const std::vector<std::pair<float, float>>& coords) {
    std::vector<int> component(boost::num_vertices(g));
    int num_components = boost::connected_components(g, &component[0]);

    std::vector<int> component_size(num_components, 0);
    for (int i = 0; i < component.size(); ++i) {
        component_size[component[i]]++;
    }

    size_t largest_component = std::distance(component_size.begin(), std::max_element(component_size.begin(), component_size.end()));

    keep_node.assign(coords.size(), false);
    for (size_t i = 0; i < component.size(); ++i) {
        if (component[i] == static_cast<int>(largest_component)) {
            keep_node[i] = true;
        }
    }

    std::vector<Edge> filtered_edges;
    std::vector<float> filtered_weights;
    auto edge_pairs = boost::edges(g);
    for (auto it = edge_pairs.first; it != edge_pairs.second; ++it) {
        auto u = boost::source(*it, g);
        auto v = boost::target(*it, g);
        if (keep_node[u] && keep_node[v]) {
            filtered_edges.push_back(std::make_pair(static_cast<int>(u), static_cast<int>(v)));
            filtered_weights.push_back(boost::get(boost::edge_weight, g, *it));
        }
    }

    return Graph(filtered_edges.begin(), filtered_edges.end(), filtered_weights.begin(), coords.size());
}

std::vector<int> GraphManager::compute_shortest_path(const Graph& graph, int start, int goal) {
    std::vector<int> predecessors(boost::num_vertices(graph), -1);
    std::vector<float> distances(boost::num_vertices(graph), std::numeric_limits<float>::max());
    predecessors[start] = start;
    distances[start] = 0.0f;
    boost::dijkstra_shortest_paths(graph, start,
                                   boost::predecessor_map(&predecessors[0]).
                                   distance_map(&distances[0]));

    std::vector<int> path;
    if (distances[goal] == std::numeric_limits<float>::max()) {
        return path; // No path found
    }

    for (int v = goal; v != start; v = predecessors[v]) {
        if (predecessors[v] == -1 || predecessors[v] >= static_cast<int>(predecessors.size())) {
            return {}; // Invalid predecessor
        }
        path.push_back(v);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

const std::vector<bool>& GraphManager::get_keep_node() const {
    return keep_node;
}

const std::vector<std::pair<float, float>>& GraphManager::get_coords() const {
    return coords;
}

std::vector<std::pair<float, float>> GraphManager::get_valid_coords() const {
    std::vector<std::pair<float, float>> valid_coords;
    for (size_t i = 0; i < coords.size(); ++i) {
        if (keep_node[i]) {
            valid_coords.push_back(coords[i]);
        }
    }
    return valid_coords;
}
