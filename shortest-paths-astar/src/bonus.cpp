#include "bonus.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <LEDA/graph/shortest_path.h>

void boostToLeda(const Graph& boostG, leda::graph& ledaG, edge_array<int>& cost, std::vector<leda::node>& nodeMap)
{
    // Βήμα 1: αντιστοιχία Boost κόμβων σε LEDA κόμβων
    int n = boost::num_vertices(boostG);
    nodeMap.resize(n);

    // για κάθε Boost κόμβο, δημιούργησε LEDA κόμβο
    VertexIterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(boostG); vi != vi_end; ++vi)
    {
        nodeMap[*vi] = ledaG.new_node();
    }

    // Βήμα 2: προσθήκη ακμών
    EdgeIterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::edges(boostG); ei != ei_end; ++ei)
    {
        Vertex u = boost::source(*ei, boostG);  // αρχή ακμής
        Vertex v = boost::target(*ei, boostG);  // τέλος ακμής
        int w = boostG[*ei].weight;             // βάρος

        //LEDA ακμή
        leda::node lu = nodeMap[u];  // = A
        leda::node lv = nodeMap[v]; // = B
        leda::edge le = ledaG.new_edge(lu, lv);  // A σε B

    }
    // αρχικοποίηση cost
    cost.init(ledaG);

    // και ξαναδιατρέχουμε για να βάλουμε τα βάρη
    EdgeIterator ei2, ei2_end;
    leda::edge le2 = ledaG.first_edge();
    for(boost::tie(ei2, ei2_end) = boost::edges(boostG); ei2 != ei2_end; ++ei2)
    {
        cost[le2] = boostG[*ei2].weight;
        le2 = ledaG.succ_edge(le2);
    }
}

void runLedaDijkstra(leda::graph& ledaG, const edge_array<int>& cost, 
                     leda::node s, leda::node t)
{
    node_array<int> dist(ledaG);
    node_array<edge> pred(ledaG);

    // μέτρηση χρόνου
    auto start = std::chrono::high_resolution_clock::now();
    DIJKSTRA_T(ledaG, s, t, cost, dist, pred);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "LEDA NT_DIJKSTRA_T" << std::endl;
    std::cout << "  Απόσταση: " << dist[t] << std::endl;
    std::cout << "  Χρόνος: " << time << " ms" << std::endl;
}