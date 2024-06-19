// Graph.hpp

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, float>> Graph;
typedef std::pair<int, int> Edge;

class GraphManager {
public:
    GraphManager(int grid_size, int nodes_per_cell, float field_size);
    std::vector<std::pair<float, float>> generate_coordinates();
    Graph create_graph(const std::vector<std::pair<float, float>>& coords);
    Graph filter_largest_component(const Graph& g, const std::vector<std::pair<float, float>>& coords);
    std::vector<int> compute_shortest_path(const Graph& graph, int start, int goal);
    const std::vector<bool>& get_keep_node() const;
    const std::vector<std::pair<float, float>>& get_coords() const;
    std::vector<std::pair<float, float>> get_valid_coords() const;

private:
    int grid_size;
    int nodes_per_cell;
    float field_size;
    std::vector<bool> keep_node;
    std::vector<std::pair<float, float>> coords;
};

#endif // GRAPH_HPP



