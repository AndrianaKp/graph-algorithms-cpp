#include "graph_generator.hpp"

void generateGrid(Graph& g, int r, int c, int minW, int maxW)
{
    //δημιουργία γεννήτριας τυχαίων αριθμών
    srand(42);

    //προσθήκη κόμβων
    for(int i=0; i < r; i++)
    {
        for(int j=0; j < c; j++)
        {
            Vertex v = boost::add_vertex(g);
            g[v].x = i;
            g[v].y = j;
        }
    }

    //προσθήκη ακμών

    int di[] = {-1, 1,  0, 0};
    int dj[] = { 0, 0, -1, 1};

    for(int i=0; i < r; i++)
    {
        for(int j=0; j < c; j++)
        {
            for(int k=0; k < 4; k++)
            {
                
                int ni = i + di[k];
                int nj = j + dj[k];

                if(ni >=0 && ni < r && nj >= 0 && nj < c)
                {
                    int u = i*c + j;
                    int v = ni*c + nj;

                    Edge e = boost::add_edge(u, v, g).first;
                    g[e].weight = minW + rand() % (maxW - minW + 1);
                }
            }
        }
    }
}

void generateRandom(Graph& g, int n, int m, int minW, int maxW)
{
    // γεννήτρια
    srand(47);

    // προσθήκη n κόμβων
    for(int i = 0; i < n; i++)
    {
        Vertex v = boost::add_vertex(g);
        g[v].x = rand() % 10001;  // τυχαία συντεταγμένη x
        g[v].y = rand() % 10001;  // τυχαία συντεταγμένη y
    }

    //προσθήκη m ακμών
    for(int j=0; j < m; j++)
    {
        Vertex u = rand() % n;  // τυχαίος source
        Vertex v = rand() % n;  // τυχαίος target
        Edge e = boost::add_edge(u, v, g).first;
        g[e].weight = minW + rand() % (maxW - minW + 1);
    }
}