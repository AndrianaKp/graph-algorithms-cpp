#pragma once

#include "graph.hpp"
#include <LEDA/graph/graph.h>
#include <LEDA/graph/node_array.h>
#include <LEDA/graph/edge_array.h>
using namespace leda;

// Μετατροπή Boost γραφήματος σε LEDA
void boostToLeda(const Graph& boostG, leda::graph& ledaG, edge_array<int>& cost, std::vector<leda::node>& nodeMap);

// NT_DIJKSTRA_T με χρόνο
void runLedaDijkstra(leda::graph& ledaG, const edge_array<int>& cost, leda::node s, leda::node t);