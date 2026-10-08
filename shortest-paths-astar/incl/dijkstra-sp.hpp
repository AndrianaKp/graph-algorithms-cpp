#pragma once

#include "graph.hpp"
#include <utility> 

std::pair<int,int> dijkstra(const Graph& g, Vertex s, Vertex t);
std::vector<int> dijkstraAll(const Graph& g, Vertex s);
std::vector<int> dijkstraAllReverse(const Graph& g, Vertex s);