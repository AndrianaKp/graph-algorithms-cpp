#include "a_star.hpp"
#include <limits>
#include <vector>

std::pair<int,int> astar(const Graph& g, Vertex s, Vertex t, std::function<int(Vertex)> h)
{
    int n = boost::num_vertices(g);
    int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);
    std::vector<handle_t> handles(n);
    std::vector<bool> inHeap(n, false);
    int count = 0;

    PriorityQueue pq;
    dist[s] = 0;
    handles[s] = pq.push({s, h(s)});
    inHeap[s] = true;

    while(!pq.empty())
{
    Vertex u = pq.top().first;
    int d = pq.top().second;
    pq.pop();
    count++;

    if(u == t) break;  // βρήκαμε τον στόχο

    if(visited[u]) continue;  // αν είναι ήδη οριστικοποιημένος, παράλειψε
    visited[u] = true;

    // για κάθε εξερχόμενη ακμή του u
    OutEdgeIterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::out_edges(u, g); ei != ei_end; ++ei)
    {
        Vertex v = boost::target(*ei, g);  // ο γείτονας
        int w = g[*ei].weight;             // το βάρος της ακμής

        if(dist[u] + w < dist[v])
        {
            dist[v] = dist[u] + w;

            if(inHeap[v])
            {
                //αν ο v είναι ήδη στο heap, μείωσε την τιμή του
                pq.decrease(handles[v], {v, dist[v] + h(v)});
            }
            else
            {
                //αν ο v δεν είναι στο heap, πρόσθεσέ τον
                handles[v] = pq.push({v, dist[v]+ h(v)});
                inHeap[v] = true;
            }
            
        }
    }
}

return {dist[t], count};
}