#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <utility>
#include <boost/graph/adjacency_list.hpp>

/** Typedef for a Boost adjacency list graph. */
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, boost::property<boost::edge_weight_t, float>> Graph;

/** Typedef for a pair of integers representing an edge. */
typedef std::pair<int, int> Edge;

/** Manages the creation and manipulation of graphs. */
class GraphManager {
public:
    /** Constructs a GraphManager object. */
    GraphManager(int grid_size, int nodes_per_cell, float field_size);

    /** Generates coordinates for the nodes in the graph. */
    std::vector<std::pair<float, float>> generate_coordinates();

    /** Creates a graph from the given coordinates. */
    Graph create_graph(const std::vector<std::pair<float, float>>& coords);

    /** Filters the largest connected component from the graph. */
    Graph filter_largest_component(const Graph& g, const std::vector<std::pair<float, float>>& coords);

    /** Computes the shortest path in the graph. */
    std::vector<int> compute_shortest_path(const Graph& graph, int start, int goal);

    /** Gets the vector of nodes to keep. */
    const std::vector<bool>& get_keep_node() const;

    /** Gets the coordinates of the nodes. */
    const std::vector<std::pair<float, float>>& get_coords() const;

    /** Gets the valid coordinates of the nodes. */
    std::vector<std::pair<float, float>> get_valid_coords() const;

private:
    int grid_size; ///< The size of the grid.
    int nodes_per_cell; ///< The number of nodes per cell.
    float field_size; ///< The size of the field.
    std::vector<bool> keep_node; ///< Nodes to keep.
    std::vector<std::pair<float, float>> coords; ///< Node coordinates.
};

#endif // GRAPH_HPP




