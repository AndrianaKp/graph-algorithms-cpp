#pragma once
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include "bfs.hpp"

using namespace leda;

bool my_bipar_checker(const graph& G, list<node>& V1, list<node>& V2, node_array<int>& color, list<node>& cycle);
