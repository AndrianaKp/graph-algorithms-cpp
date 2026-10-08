#pragma once

#include <boost/graph/adjacency_list.hpp>
#include <boost/heap/fibonacci_heap.hpp>

struct myVertex;
struct myEdge;

// Γράφημα
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::bidirectionalS, myVertex, myEdge> Graph;

// Vertex descriptor 
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

// Edge descriptor 
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

// Vertex and Edge properties

struct myVertex
{
    int dist;
    Edge pred;
    int x,y; //συντεταγμένες για ευκλείδεια απόσταση
   
};

// Τα edge properties είναι απαραίτητα
struct myEdge
{
    int weight;
};

// Iterators 
typedef boost::graph_traits<Graph>::vertex_iterator VertexIterator;
typedef boost::graph_traits<Graph>::edge_iterator EdgeIterator;
typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator; //για dijkstra
typedef boost::graph_traits<Graph>::in_edge_iterator InEdgeIterator; // για landmarks

// Fibonacci Heap 
struct CompareVertices 
{
    bool operator()(const std::pair<Vertex, int>& p1, const std::pair<Vertex, int>& p2) const
    {
        return p1.second > p2.second; 
    }
};

typedef boost::heap::fibonacci_heap<std::pair<Vertex, int>, boost::heap::compare<CompareVertices> > PriorityQueue;

typedef PriorityQueue::handle_type handle_t;
