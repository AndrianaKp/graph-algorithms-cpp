#include "dijkstra-sp.hpp"
#include <limits>
#include <vector>

std::pair<int,int> dijkstra(const Graph& g, Vertex s, Vertex t)
{
    int n = boost::num_vertices(g);
    int INF = std::numeric_limits<int>::max(); //για το άπειρο

    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);
    std::vector<handle_t> handles(n);
    std::vector<bool> inHeap(n, false);
    int count = 0;

    PriorityQueue pq;
    dist[s] = 0;
    handles[s] = pq.push({s, 0});
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
                pq.decrease(handles[v], {v, dist[v]});
            }
            else
            {
                //αν ο v δεν είναι στο heap, πρόσθεσέ τον
                handles[v] = pq.push({v, dist[v]});
                inHeap[v] = true;
            }
            
        }
    }
}

return {dist[t], count};

}


//Dijkstra απο L2 προς ολους τους κόμβους
std::vector<int> dijkstraAll(const Graph& g, Vertex s)
{
    int n = boost::num_vertices(g);
    int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);
    std::vector<handle_t> handles(n);
    std::vector<bool> inHeap(n, false);

    PriorityQueue pq;
    dist[s] = 0;
    handles[s] = pq.push({s, 0});
    inHeap[s] = true;

    while(!pq.empty())
{
    Vertex u = pq.top().first;
    int d = pq.top().second;
    pq.pop();
   

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
                // ο v είναι ήδη στο heap -> μείωσε την τιμή του
                pq.decrease(handles[v], {v, dist[v]});
            }
            else
            {
                // ο v δεν είναι στο heap -> πρόσθεσέ τον
                handles[v] = pq.push({v, dist[v]});
                inHeap[v] = true;
            }
            
        }
    }
}

return dist;
}

std::vector<int> dijkstraAllReverse(const Graph& g, Vertex s)
{
    int n = boost::num_vertices(g);
    int INF = std::numeric_limits<int>::max();

    std::vector<int> dist(n, INF);
    std::vector<bool> visited(n, false);
    std::vector<handle_t> handles(n);
    std::vector<bool> inHeap(n, false);

    PriorityQueue pq;
    dist[s] = 0;
    handles[s] = pq.push({s, 0});
    inHeap[s] = true;

    while(!pq.empty())
{
    Vertex u = pq.top().first;
    int d = pq.top().second;
    pq.pop();
   

    if(visited[u]) continue;  // αν είναι ήδη οριστικοποιημένος, παράλειψε
    visited[u] = true;

    // για κάθε εξερχόμενη ακμή του u
    InEdgeIterator ei, ei_end;
    for(boost::tie(ei, ei_end) = boost::in_edges(u, g); ei != ei_end; ++ei)
    {
        Vertex v = boost::source(*ei, g);  // ο γείτονας
        int w = g[*ei].weight;             // το βάρος της ακμής

        if(dist[u] + w < dist[v])
        {
            dist[v] = dist[u] + w;

            if(inHeap[v])
            {
                // ο v είναι ήδη στο heap -> μείωσε την τιμή του
                pq.decrease(handles[v], {v, dist[v]});
            }
            else
            {
                // ο v δεν είναι στο heap -> πρόσθεσέ τον
                handles[v] = pq.push({v, dist[v]});
                inHeap[v] = true;
            }
            
        }
    }
}

return dist;

}