#include <iostream>
#include "../incl/bipartite.hpp"

using namespace std;

/*
 * my_bipar_checker: Ελεγκτής διμερότητας (certifying algorithm).
 *
 * Φάση Α: Καλεί my_BFS για χρωματισμό GREEN/BLUE ανά επίπεδο.
 *
 * Φάση Β: Ελέγχει κάθε ακμή (u, w).
 *   - Αν color[u] == color[w]: το γράφημα δεν είναι διμερές.
 *     Κατασκευάζει περιττό κύκλο βρίσκοντας τον LCA των u, w
 *     στο BFS-δέντρο, και επιστρέφει false.
 *   - Αλλιώς: γεμίζει V1 (GREEN) και V2 (BLUE) και επιστρέφει true.
 *
 * Πολυπλοκότητα: O(n + m)
 */
bool my_bipar_checker(const graph& G, list<node>& V1, list<node>& V2,
                      node_array<int>& color, list<node>& cycle)
{
    // Φάση Α: BFS χρωματισμός
    node s = G.first_node();
    node_array<int>  dist(G, -1);
    node_array<edge> pred(G, nil);

    my_BFS(G, s, dist, pred, color);

    //Φάση Β: Έλεγχος για ακμή με άκρα ίδιου χρώματος
    edge e;
    forall_edges(e, G)
    {
        node u = G.source(e);
        node w = G.target(e);

        if (color[u] == color[w])
        {
            /*
             * Βρέθηκε ακμή (u, w) με color[u] == color[w].
             * Αυτή η ακμή μαζί με τα μονοπάτια u→χαμηλότερος γείτονας και w→χγ
             * στο BFS-δέντρο σχηματίζουν περιττό κύκλο.
             *
             * Αλγόριθμος εύρεσης χαμηλότερου γείτονα:
             *   1. Φέρνουμε u και w στο ίδιο επίπεδο ανεβαίνοντας
             *      τον βαθύτερο.
             *   2. Ανεβαίνουμε και τους δύο παράλληλα μέχρι να
             *      συναντηθούν (LCA).
             */

            list<node> path_u, path_w;
            node x = u;
            node y = w;

            // Συλλογή μονοπατιών: ανεβαίνουμε στο ίδιο επίπεδο
            while (dist[x] > dist[y])
            {
                path_u.append(x);
                x = G.opposite(x, pred[x]);   // προκάτοχος του x
            }
            while (dist[y] > dist[x])
            {
                path_w.append(y);
                y = G.opposite(y, pred[y]);   // προκάτοχος του y
            }

            // Ανεβαίνουμε παράλληλα μέχρι τον χαμηλότερο γείτονα
            while (x != y)
            {
                path_u.append(x);
                x = G.opposite(x, pred[x]);
                path_w.append(y);
                y = G.opposite(y, pred[y]);
            }
            // Εδώ x==y χαμηλότερος γείτονας
            path_u.append(x);  // προσθήκη χαμηλότερου γείτονα

            // Κατασκευή κύκλου: path_u + αντίστροφο path_w
            cycle = path_u;
            path_w.reverse();
            node n;
            forall(n, path_w)
                cycle.append(n);

            return false;
        }
    }

    // Φάση Γ: Γέμισμα V1 (GREEN) και V2 (BLUE) 
    node v;
    forall_nodes(v, G)
    {
        if (color[v] == GREEN)
            V1.append(v);
        else
            V2.append(v);
    }
    return true;
}

