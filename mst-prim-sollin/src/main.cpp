#include "../incl/algorithms.hpp"
#include "../incl/experiments.hpp"
#include <iostream>

int main()
{
    // Test στο Figure 13.7

    ugraph G;
    node v1=G.new_node(), v2=G.new_node(), v3=G.new_node(),
         v4=G.new_node(), v5=G.new_node();
    edge e1=G.new_edge(v1,v2), e2=G.new_edge(v1,v3),
         e3=G.new_edge(v2,v4), e4=G.new_edge(v2,v3),
         e5=G.new_edge(v3,v5), e6=G.new_edge(v4,v3),
         e7=G.new_edge(v4,v5);
    edge_array<int> cost(G);
    cost[e1]=35; cost[e2]=40; cost[e3]=10; cost[e4]=25;
    cost[e5]=15; cost[e6]=20; cost[e7]=30;
    edge e;

    // Test my_prim 
    std::cout << " Test: my_prim sto grafhma Figure 13.7 " << std::endl;
    std::cout << "Komvoi: " << G.number_of_nodes()
               << " | Akmes: " << G.number_of_edges() << std::endl;
    list<edge> mst_prim;
    my_prim(G, cost, mst_prim);
    int total_prim = 0;
    std::cout << "Akmes tou EGD (Prim):" << std::endl;
    forall(e, mst_prim) {
        node a=G.source(e), b=G.target(e);
        std::cout << "  (" << G.index(a)+1 << "," << G.index(b)+1
                   << ") cost = " << cost[e] << std::endl;
        total_prim += cost[e];
    }
    std::cout << "Plithos akmwn = " << mst_prim.length()
               << "  (anamenomeno: " << G.number_of_nodes()-1 << ")" << std::endl;
    std::cout << "Synoliko kostos = " << total_prim
               << "  (anamenomeno: 80)" << std::endl;

    // Test my_sollin 
    std::cout << std::endl;
    std::cout << " Test: my_sollin sto grafhma Figure 13.7 " << std::endl;
    list<edge> mst_sollin;
    my_sollin(G, cost, mst_sollin);
    int total_sollin = 0;
    std::cout << "Akmes tou EGD (Sollin):" << std::endl;
    forall(e, mst_sollin) {
        node a=G.source(e), b=G.target(e);
        std::cout << "  (" << G.index(a)+1 << "," << G.index(b)+1
                   << ") cost = " << cost[e] << std::endl;
        total_sollin += cost[e];
    }
    std::cout << "Plithos akmwn = " << mst_sollin.length()
               << "  (anamenomeno: " << G.number_of_nodes()-1 << ")" << std::endl;
    std::cout << "Synoliko kostos = " << total_sollin
               << "  (anamenomeno: 80)" << std::endl;

    // Test LEDA MIN_SPANNING_TREE 
    std::cout << std::endl;
    std::cout << " Test: LEDA MIN_SPANNING_TREE " << std::endl;
    list<edge> mst_leda = MIN_SPANNING_TREE(G, cost);
    int total_leda = 0;
    std::cout << "Akmes tou EGD (LEDA):" << std::endl;
    forall(e, mst_leda) {
        node a=G.source(e), b=G.target(e);
        std::cout << "  (" << G.index(a)+1 << "," << G.index(b)+1
                   << ") cost = " << cost[e] << std::endl;
        total_leda += cost[e];
    }
    std::cout << "Plithos akmwn = " << mst_leda.length()
               << "  (anamenomeno: " << G.number_of_nodes()-1 << ")" << std::endl;
    std::cout << "Synoliko kostos = " << total_leda
               << "  (anamenomeno: 80)" << std::endl;

    // Πειράματα (K=5 επαναλήψεις, μέσος χρόνος)

    srand(42); //κάθε φορά που τρέχει το πρόγραμμα, παίρνουμε την ίδια ακολουθία αριθμών
    int K = 5;
    int sollin_max = 1000; //κατώφλι

    // Τυχαία αραιά (m=5n)
    std::cout << std::endl;
    std::cout << " TYXAIA ARAIA GRAFHIMATA (m=5n, mesος K=" << K << ") " << std::endl;
    std::cout << "n\tm\tPrim(s)\t\tSollin(s)\tLEDA(s)" << std::endl;
    int sparse_n[] = {100, 1000, 5000, 10000, 100000};
    for (int i = 0; i < 5; i++) {
        std::cerr << "Sparse n=" << sparse_n[i] << std::endl;
        run_experiment_random_sparse(sparse_n[i], K, sparse_n[i] <= sollin_max);
    }

    // Τυχαία πυκνά (m=n²/4) 
    std::cout << std::endl;
    std::cout << " TYXAIA PYKNA GRAFHIMATA (m=n^2/4, mesos K=" << K << ") " << std::endl;
    std::cout << "n\tm\tPrim(s)\t\tSollin(s)\tLEDA(s)" << std::endl;
    int dense_n[] = {100, 500, 1000, 2000};
    for (int i = 0; i < 4; i++) {
        std::cerr << "Dense n=" << dense_n[i] << std::endl;
        run_experiment_random_dense(dense_n[i], K, dense_n[i] <= sollin_max);
    }

    // Τυχαία επίπεδα 
    std::cout << std::endl;
    std::cout << " TYXAIA EPIPEDA GRAFHIMATA (mesos K=" << K << ") " << std::endl;
    std::cout << "n\tm\tPrim(s)\t\tSollin(s)\tLEDA(s)" << std::endl;
    int planar_n[] = {100, 1000, 5000, 10000, 100000};
    for (int i = 0; i < 5; i++) {
        std::cerr << "Planar n=" << planar_n[i] << std::endl;
        run_experiment_planar(planar_n[i], K, planar_n[i] <= sollin_max);
    }

    // Πλήρη γραφήματα 
    std::cout << std::endl;
    std::cout << " MH TYXAIA: PLIRES GRAFHIMA (mesos K=" << K << ") " << std::endl;
    std::cout << "n\tm\tPrim(s)\t\tSollin(s)\tLEDA(s)" << std::endl;
    int complete_n[] = {100, 500, 1000, 2000};
    for (int i = 0; i < 4; i++) {
        std::cerr << "Complete n=" << complete_n[i] << std::endl;
        run_experiment_complete(complete_n[i], K, complete_n[i] <= sollin_max);
    }

    // Grid γραφήματα 
    std::cout << std::endl;
    std::cout << " MH TYXAIA: GRID GRAFHIMA (mesos K=" << K << ") " << std::endl;
    std::cout << "n(NxN)\tm\tPrim(s)\t\tSollin(s)\tLEDA(s)" << std::endl;
    int grid_n[] = {10, 30, 50, 100};
    for (int i = 0; i < 4; i++) {
        std::cerr << "Grid " << grid_n[i] << "x" << grid_n[i] << std::endl;
        run_experiment_grid(grid_n[i], K, true);
    }

    return 0;
}