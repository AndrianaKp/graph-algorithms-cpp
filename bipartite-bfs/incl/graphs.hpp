#pragma once
#include <LEDA/graph/graph.h>
using namespace leda;

void build_nested_squares(graph& G, int n);
void build_ring(graph& G, int n);
void build_4levels(graph& G, int k);
void build_grid_with_diagonals(graph& G, int k, int extra_edges);
