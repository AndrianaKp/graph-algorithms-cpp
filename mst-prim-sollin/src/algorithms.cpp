#include "../incl/algorithms.hpp"
#include <vector>   // (χρησιμοποιείται στον my_sollin)

/*
 * my_prim
 * Ξεκινάει από έναν κόμβο (start) και μεγαλώνει το δένδρο S προσθέτοντας
 * κάθε φορά την ελάχιστη ακμή που συνδέει το S με κόμβο εκτός S.
 * Χρησιμοποιεί node_pq για να βρίσκει σε O(log n) τον επόμενο κόμβο.
 */
void my_prim(ugraph& G, edge_array<int>& cost, list<edge>& mst_edges)
{
    node_array<bool>   in_S(G, false);
    node_array<int>    mincost(G);
    node_array<edge>   minedge(G, nil);
    node_pq<int>       PQ(G);

    node v;
    node start = G.first_node(); //αυθαίρετη επιλογή κόμβου 

    // Αρχικοποίηση: ο start έχει κόστος 0, όλοι οι άλλοι άπειρο
    forall_nodes(v, G) {
        mincost[v] = (v == start) ? 0 : MAXINT;
        PQ.insert(v, mincost[v]);
    }

    while (!PQ.empty())
    {
        node u = PQ.del_min();
        in_S[u] = true;

        // ο start δεν έχει εισερχόμενη ακμή στο ΕΓΔ
        if (minedge[u] != nil)
            mst_edges.append(minedge[u]);

        edge e;
        forall_adj_edges(e, u)
        {
            node w = G.opposite(u, e); //επιστροφή του άλλου κόμβου της ακμής
            if (!in_S[w] && cost[e] < mincost[w])
            {
                mincost[w] = cost[e];
                minedge[w] = e;
                PQ.decrease_p(w, cost[e]);
            }
        }
    }
}

/*
 * my_sollin
 * Κάθε κόμβος ξεκινά ως δικό του δένδρο. Σε κάθε γύρο, κάθε δένδρο
 * βρίσκει την ελάχιστη ακμή που το συνδέει με άλλο δένδρο και ενώνονται.
 * Επαναλαμβάνει μέχρι να μείνει ένα δένδρο (n-1 ακμές στο ΕΓΔ).
 */
void my_sollin(ugraph& G, edge_array<int>& cost, list<edge>& mst_edges)
{
    int n = G.number_of_nodes();
    node_array<int> comp(G);
    node v;

    // Αρχικοποίηση: κάθε κόμβος είναι δικό του δένδρο
    forall_nodes(v, G)
        comp[v] = G.index(v);

    while (mst_edges.length() < n - 1)
    {
        // Φάση 1: βρίσκουμε την ελάχιστη ακμή για κάθε δένδρο 

        std::vector<edge> best_edge(n, (edge)nil);  

        forall_nodes(v, G)
        {
            edge e;
            forall_adj_edges(e, v)
            {
                node w = G.opposite(v, e);
                if (comp[v] != comp[w])
                {
                    int c = comp[v];
                    if (best_edge[c] == nil || cost[e] < cost[best_edge[c]])
                        best_edge[c] = e;
                }
            }
        }

        // Φάση 2: ένωσε τα δένδρα μέσω των best_edge

        for (int c = 0; c < n; c++)
        {
            if (best_edge[c] != nil)
            {
                node v = G.source(best_edge[c]);
                node w = G.target(best_edge[c]);

                if (comp[v] != comp[w])
                {
                    mst_edges.append(best_edge[c]);

                    int old_comp = comp[w];
                    int new_comp = comp[v];
                    node u;
                    forall_nodes(u, G)
                        if (comp[u] == old_comp)
                            comp[u] = new_comp;
                }
            }
        }
    }
}