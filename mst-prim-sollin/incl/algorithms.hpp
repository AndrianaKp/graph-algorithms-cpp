#pragma once
#include <LEDA/graph/ugraph.h>
#include <LEDA/graph/node_pq.h>
#include <LEDA/core/list.h>
#include <LEDA/graph/graph_alg.h>   // για MIN_SPANNING_TREE
using namespace leda;


void my_prim(ugraph& G, edge_array<int>& cost, list<edge>& mst_edges);

void my_sollin(ugraph& G, edge_array<int>& cost, list<edge>& mst_edges);