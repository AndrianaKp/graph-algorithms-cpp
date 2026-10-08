#include "../incl/bfs.hpp"
#include <LEDA/core/queue.h>

list<node> my_BFS(const graph& G, node s, node_array<int>& dist,
                  node_array<edge>& pred, node_array<int>& color)
{
    list<node> visited_nodes;
    queue<node> Q;
    node v;

    // Αρχικοποίηση όλων των κορυφών
    forall_nodes(v, G) {
        dist[v]  = -1;
        pred[v]  = nil;
        color[v] = UNCOLORED;
    }

    // Εισαγωγή ρίζας
    dist[s]  = 0;
    pred[s]  = nil;
    color[s] = GREEN;
    Q.append(s);
    visited_nodes.append(s);

    while (!Q.empty())
    {
        node t = Q.pop();
        edge e;
        forall_adj_edges(e, t)
        {
            node u = G.opposite(t, e);
            if (dist[u] == -1)  // αν δεν έχει επισκεφθεί
            {
                dist[u]  = dist[t] + 1;
                pred[u]  = e;
                color[u] = (color[t] == GREEN) ? BLUE : GREEN;
                Q.append(u);
                visited_nodes.append(u);
            }
        }
    }
    return visited_nodes;
}
