#pragma once
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
using namespace leda;

const int UNCOLORED = -1;
const int GREEN     =  0;
const int BLUE      =  1;

list<node> my_BFS(const graph& G, node s, node_array<int>& dist,
                  node_array<edge>& pred, node_array<int>& color);
