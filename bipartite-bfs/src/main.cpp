#include <iostream>
#include <LEDA/graph/graph.h>
#include <LEDA/core/list.h>
#include <LEDA/graph/graph_alg.h>
#include <LEDA/system/basic.h>
#include "../incl/bfs.hpp"
#include "../incl/bipartite.hpp"
#include "../incl/graphs.hpp"
#include "../incl/experiments.hpp"

using namespace leda;
using namespace std;

void print_results(const graph& G, node_array<int>& dist, node_array<int>& color)
{
    node v;
    forall_nodes(v, G)
    {
        const char* col = (color[v] == GREEN) ? "GREEN" : "BLUE";
        cout << "Node " << G.index(v) 
             << " | Level: " << dist[v] 
             << " | Color: " << col << endl;
    }
}

int main()
{
    float T;
    bool leda_result;

    // TEST 1: Διμερές γράφημα (τετράγωνο)
    cout << "TEST 1: Τετράγωνο (διμερές)" << endl;

    graph G1;
    node v1 = G1.new_node();
    node v2 = G1.new_node();
    node v3 = G1.new_node();
    node v4 = G1.new_node();

    G1.new_edge(v1, v2); G1.new_edge(v2, v1);
    G1.new_edge(v2, v3); G1.new_edge(v3, v2);
    G1.new_edge(v3, v4); G1.new_edge(v4, v3);
    G1.new_edge(v4, v1); G1.new_edge(v1, v4);

    list<node> V1_1, V2_1, cycle1;
    node_array<int> color1(G1, UNCOLORED);

    T = leda::used_time();
    if (my_bipar_checker(G1, V1_1, V2_1, color1, cycle1))
        cout << "my_checker: Διμερές | V1=" << V1_1.size() << " V2=" << V2_1.size() << endl;
    else
        cout << "my_checker: Μη διμερές" << endl;
    cout << "my_bipar_checker χρόνος: " << leda::used_time(T) << " sec" << endl;

    list<node> A1, B1;
    T = leda::used_time();
    leda_result = Is_Bipartite(G1, A1, B1);
    cout << "Is_Bipartite χρόνος: " << leda::used_time(T) << " sec" << endl;
    if (leda_result)
        cout << "LEDA: Διμερές | A=" << A1.size() << " B=" << B1.size() << endl;
    else
        cout << "LEDA: Μη διμερές" << endl;

    cout << endl;

    // TEST 2: Μη διμερές γράφημα (τρίγωνο)
    cout << "TEST 2: Τρίγωνο (μη διμερές)" << endl;

    graph G2;
    node u1 = G2.new_node();
    node u2 = G2.new_node();
    node u3 = G2.new_node();

    G2.new_edge(u1, u2); G2.new_edge(u2, u1);
    G2.new_edge(u2, u3); G2.new_edge(u3, u2);
    G2.new_edge(u3, u1); G2.new_edge(u1, u3);

    list<node> V1_2, V2_2, cycle2;
    node_array<int> color2(G2, UNCOLORED);

    T = leda::used_time();
    if (my_bipar_checker(G2, V1_2, V2_2, color2, cycle2))
        cout << "my_checker: Διμερές" << endl;
    else
    {
        cout << "Περιττός κύκλος: ";
        node n;
        forall(n, cycle2)
            cout << G2.index(n) << " ";
        cout << endl;
        cout << "my_checker: Μη διμερές" << endl;
    }
    cout << "my_bipar_checker χρόνος: " << leda::used_time(T) << " sec" << endl;

    list<node> A2, B2;
    T = leda::used_time();
    leda_result = Is_Bipartite(G2, A2, B2);
    cout << "Is_Bipartite χρόνος: " << leda::used_time(T) << " sec" << endl;
    if (leda_result)
        cout << "LEDA: Διμερές" << endl;
    else
        cout << "LEDA: Μη διμερές" << endl;

    cout << endl;

    run_experiments();

    return 0;
}
