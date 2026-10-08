#pragma once

#include "graph.hpp"
#include "dijkstra-sp.hpp"
#include <functional> //για να δέχεται ο Α* την heuristic ως παράμετρο

std::pair<int,int> astar(const Graph& g, Vertex s, Vertex t, 
    std::function<int(Vertex)> h);

// Δομή για να περνάνε δεδομένα στην heuristic
struct EuclideanHeuristic {
    const Graph& g;
    Vertex t;
    
    EuclideanHeuristic(const Graph& g, Vertex t) : g(g), t(t) {}
    
    int operator()(Vertex u) const {
        int dx = g[u].x - g[t].x;
        int dy = g[u].y - g[t].y;
        return (int)sqrt(dx*dx + dy*dy);
    }
};

struct LandmarkHeuristic {
    const std::vector<int>& distFromL1;
    const std::vector<int>& distToL2;
    Vertex t;
    int INF;

    LandmarkHeuristic(const std::vector<int>& d1, 
                      const std::vector<int>& d2, 
                      Vertex t) 
        : distFromL1(d1), distToL2(d2), t(t), 
          INF(std::numeric_limits<int>::max()) {}

    int operator()(Vertex u) const {
        int h1 = 0, h2 = 0;
        
        // ελέγχουμε ότι οι αποστάσεις δεν είναι INF
        if(distFromL1[u] != INF && distFromL1[t] != INF)
            h1 = distFromL1[t] - distFromL1[u];
            
        if(distToL2[u] != INF && distToL2[t] != INF)
            h2 = distToL2[u] - distToL2[t];
        
        int h = std::max(h1, h2);
        return std::max(h, 0); 
    }
};