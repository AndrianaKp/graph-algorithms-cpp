#include <iostream>
#include "../incl/graphs.hpp"
#include <cstdlib>

using namespace std;
using namespace leda;

void build_nested_squares(graph& G, int n)
{
    node* v = new node[n];
    for (int i = 0; i < n; i++)
        v[i] = G.new_node();

    for (int i = 1; i <= n/4; i++)
    {
        int a = 4*(i-1);
        int b = 4*(i-1) + 1;
        int c = 4*(i-1) + 2;
        int d = 4*(i-1) + 3;
 
	//ακμές τετραγώνου i (αμφίδρομες)
        G.new_edge(v[a], v[b]); G.new_edge(v[b], v[a]);
        G.new_edge(v[b], v[c]); G.new_edge(v[c], v[b]);
        G.new_edge(v[c], v[d]); G.new_edge(v[d], v[c]);
        G.new_edge(v[d], v[a]); G.new_edge(v[a], v[d]);

	//ακμές σύνδεσης με τα προηγούμενα τετράγωνα
        if (i > 1)
        {
            int pa = 4*(i-2);
            int pb = 4*(i-2) + 1;
            int pc = 4*(i-2) + 2;
            int pd = 4*(i-2) + 3;

            G.new_edge(v[a], v[pa]); G.new_edge(v[pa], v[a]);
            G.new_edge(v[b], v[pb]); G.new_edge(v[pb], v[b]);
            G.new_edge(v[c], v[pc]); G.new_edge(v[pc], v[c]);
            G.new_edge(v[d], v[pd]); G.new_edge(v[pd], v[d]);
        }
    }
    delete[] v;
}


void build_ring(graph& G, int n)
{
    node* v = new node[n];
    for (int i = 0; i < n; i++)
        v[i] = G.new_node();

    // ακμές δακτυλίου
    for (int i = 0; i < n-1; i++)
    {
        G.new_edge(v[i], v[i+1]);
        G.new_edge(v[i+1], v[i]);
    }
    // ακμή που κλείνει τον κύκλο
    G.new_edge(v[n-1], v[0]);
    G.new_edge(v[0], v[n-1]);

    delete[] v;
}

void build_4levels(graph& G, int k)
{
    // Δημιουργία 4k κορυφών σε 4 επίπεδα
    node* L1 = new node[k];
    node* L2 = new node[k];
    node* L3 = new node[k];
    node* L4 = new node[k];

    for (int i = 0; i < k; i++) L1[i] = G.new_node();
    for (int i = 0; i < k; i++) L2[i] = G.new_node();
    for (int i = 0; i < k; i++) L3[i] = G.new_node();
    for (int i = 0; i < k; i++) L4[i] = G.new_node();

    // Ακμές L1-L2
    int u_idx = rand() % k;
    for (int j = 0; j < k; j++)
    {
        // k κανονικές ακμές
        G.new_edge(L1[j], L2[j]); G.new_edge(L2[j], L1[j]);
        // k ακμές από τυχαία κορυφή του L1
        G.new_edge(L1[u_idx], L2[j]); G.new_edge(L2[j], L1[u_idx]);
    }

    // Ακμές L2-L3
    u_idx = rand() % k;
    for (int j = 0; j < k; j++)
    {
        G.new_edge(L2[j], L3[j]); G.new_edge(L3[j], L2[j]);
        G.new_edge(L2[u_idx], L3[j]); G.new_edge(L3[j], L2[u_idx]);
    }

    // Ακμές L3-L4
    u_idx = rand() % k;
    for (int j = 0; j < k; j++)
    {
        G.new_edge(L3[j], L4[j]); G.new_edge(L4[j], L3[j]);
        G.new_edge(L3[u_idx], L4[j]); G.new_edge(L4[j], L3[u_idx]);
    }

    // Τυχαία ακμή L1-L3
    int u1 = rand() % k;
    int v1 = rand() % k;
    G.new_edge(L1[u1], L3[v1]); G.new_edge(L3[v1], L1[u1]);

    // Τυχαία ακμή L2-L4
    int u2 = rand() % k;
    int v2 = rand() % k;
    G.new_edge(L2[u2], L4[v2]); G.new_edge(L4[v2], L2[u2]);

    delete[] L1; delete[] L2; delete[] L3; delete[] L4;
}

//bomus: πλέγμα kxk

void build_grid_with_diagonals(graph& G, int k, int extra_edges)
{
    int n = k * k;
    node* v = new node[n];

    // Δημιουργία n κορυφών
    for (int i = 0; i < n; i++)
        v[i] = G.new_node();

    // Οριζόντιες ακμές (αμφίδρομες)
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k - 1; j++)
        {
            G.new_edge(v[i*k + j],     v[i*k + j + 1]);
            G.new_edge(v[i*k + j + 1], v[i*k + j]);
        }

    // Κατακόρυφες ακμές (αμφίδρομες)
    for (int i = 0; i < k - 1; i++)
        for (int j = 0; j < k; j++)
        {
            G.new_edge(v[i*k + j],     v[(i+1)*k + j]);
            G.new_edge(v[(i+1)*k + j], v[i*k + j]);
        }

    // Τυχαίες διαγώνιες ακμές (αμφίδρομες)
    // Αυτές κάνουν τη διμερότητα μη προφανή
    int added = 0;
    while (added < extra_edges)
    {
        int u = rand() % n;
        int w = rand() % n;
        if (u != w)
        {
            G.new_edge(v[u], v[w]);
            G.new_edge(v[w], v[u]);
            added++;
        }
    }

    delete[] v;
}
