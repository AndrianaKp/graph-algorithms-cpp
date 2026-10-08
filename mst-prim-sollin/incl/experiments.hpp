#pragma once
#include "../incl/algorithms.hpp"
#include <LEDA/graph/graph_gen.h>   // random_simple_undirected_graph, complete_graph, grid_graph
#include <LEDA/system/misc.h>       // used_time()
#include <vector>                   // std::vector για αποθήκευση χρόνων
#include <iostream>                 // std::cout

void assign_random_costs(ugraph& G, edge_array<int>& cost);

// Κ=5 επαναλήψεις με διαφορετικά τυχαία γραφήματα και εκτύπωση μέσου χρόνου εκτέλεσης για κάθε αλγόριθμο
void run_experiment_random_sparse(int n, int K, bool run_sollin);
void run_experiment_random_dense(int n, int K, bool run_sollin);
void run_experiment_planar(int n, int K, bool run_sollin);
void run_experiment_complete(int n, int K, bool run_sollin);
void run_experiment_grid(int n, int K, bool run_sollin);