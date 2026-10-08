#include <iostream>
#include "../incl/experiments.hpp"

using namespace std;
using namespace leda;

void run_experiments()
{
    // ΠΕΙΡΑΜΑ 1: Εμφωλιασμένα Τετράγωνα 
    cout << "ΠΕΙΡΑΜΑ 1: Εμφωλιασμένα Τετράγωνα " << endl;

    int sizes1[] = {12000, 48000, 100000};

    for (int s = 0; s < 3; s++)
    {
        int n = sizes1[s];
        cout << "n=" << n << endl;

        graph G;
        build_nested_squares(G, n);

        list<node> V1, V2, cycle;
        node_array<int> color(G, UNCOLORED);
        node v;

        // Μία φορά για αποτέλεσμα
        bool result = my_bipar_checker(G, V1, V2, color, cycle);
        cout << "my_checker: " << (result ? "Διμερές" : "Μη διμερές") << endl;
        list<node> A, B;
        bool leda_result = Is_Bipartite(G, A, B);
        cout << "Is_Bipartite: " << (leda_result ? "Διμερές" : "Μη διμερές") << endl;

        // Loop μέτρησης my_bipar_checker
        float total_my = 0;
        for (int rep = 0; rep < 10; rep++)
        {
            forall_nodes(v, G) color[v] = UNCOLORED;
            V1.clear(); V2.clear(); cycle.clear();
            float T = leda::used_time();
            my_bipar_checker(G, V1, V2, color, cycle);
            total_my += leda::used_time(T);
        }
        cout << "my_bipar_checker μέσος χρόνος: " << total_my/10 << " sec" << endl;

        // Loop μέτρησης Is_Bipartite
        float total_leda = 0;
        for (int rep = 0; rep < 10; rep++)
        {
            A.clear(); B.clear();
            float T = leda::used_time();
            Is_Bipartite(G, A, B);
            total_leda += leda::used_time(T);
        }
        cout << "Is_Bipartite μέσος χρόνος: " << total_leda/10 << " sec" << endl;
        cout << endl;
    }

    //  ΠΕΙΡΑΜΑ 2: Δακτύλιοι 
    cout << "ΠΕΙΡΑΜΑ 2: Δακτύλιοι " << endl;

    int sizes2[] = {20001, 50001, 100001};

    for (int s = 0; s < 3; s++)
    {
        int n = sizes2[s];
        cout << "n=" << n << endl;

        graph G;
        build_ring(G, n);

        list<node> V1, V2, cycle;
        node_array<int> color(G, UNCOLORED);
        node v;

        bool result = my_bipar_checker(G, V1, V2, color, cycle);
        cout << "my_checker: " << (result ? "Διμερές" : "Μη διμερές") << endl;
        list<node> A, B;
        bool leda_result = Is_Bipartite(G, A, B);
        cout << "Is_Bipartite: " << (leda_result ? "Διμερές" : "Μη διμερές") << endl;

        float total_my = 0;
        for (int rep = 0; rep < 10; rep++)
        {
            forall_nodes(v, G) color[v] = UNCOLORED;
            V1.clear(); V2.clear(); cycle.clear();
            float T = leda::used_time();
            my_bipar_checker(G, V1, V2, color, cycle);
            total_my += leda::used_time(T);
        }
        cout << "my_bipar_checker μέσος χρόνος: " << total_my/10 << " sec" << endl;

        float total_leda = 0;
        for (int rep = 0; rep < 10; rep++)
        {
            A.clear(); B.clear();
            float T = leda::used_time();
            Is_Bipartite(G, A, B);
            total_leda += leda::used_time(T);
        }
        cout << "Is_Bipartite μέσος χρόνος: " << total_leda/10 << " sec" << endl;
        cout << endl;
    }

    // ΠΕΙΡΑΜΑ 3: 4 Επίπεδα 
    cout << "ΠΕΙΡΑΜΑ 3: 4 Επίπεδα " << endl;

    int sizes3[] = {600, 1200, 1800};

    for (int s = 0; s < 3; s++)
    {
        int k = sizes3[s];
        cout << "k=" << k << endl;

        float total_my = 0;
        float total_leda = 0;
        bool last_result_my = false;
        bool last_result_leda = false;

        for (int rep = 0; rep < 100; rep++)
        {
            // Νέο γράφημα σε κάθε επανάληψη
            graph G;
            build_4levels(G, k);

            list<node> V1, V2, cycle;
            node_array<int> color(G, UNCOLORED);

            float T = leda::used_time();
            last_result_my = my_bipar_checker(G, V1, V2, color, cycle);
            total_my += leda::used_time(T);

            list<node> A, B;
            T = leda::used_time();
            last_result_leda = Is_Bipartite(G, A, B);
            total_leda += leda::used_time(T);
        }

        cout << "my_checker: " << (last_result_my ? "Διμερές" : "Μη διμερές") << endl;
        cout << "Is_Bipartite: " << (last_result_leda ? "Διμερές" : "Μη διμερές") << endl;
        cout << "my_bipar_checker μέσος χρόνος: " << total_my/100 << " sec" << endl;
        cout << "Is_Bipartite μέσος χρόνος: " << total_leda/100 << " sec" << endl;
        cout << endl;
    }

  // Πείραμα Bonus: Πλέγμα k×k με τυχαίες διαγώνιες ακμές
    cout << "Πείραμα Bonus: Πλέγμα k×k με τυχαίες διαγώνιες ακμές" << endl;
    cout << "Το βασικό πλέγμα είναι διμερές, αλλά οι τυχαίες ακμές" << endl;
    cout << "μπορεί να το κάνουν μη διμερές" << endl;

    // k = πλευρά πλέγματος, n = k*k κορυφές
    int sizes_bonus[] = {30, 60, 100};
    int extra_edges   = 5; // αριθμός τυχαίων διαγώνιων ακμών

    for (int s = 0; s < 3; s++)
    {
        int k = sizes_bonus[s];
        int n = k * k;

        cout << "k=" << k << " | n=" << n
             << " | extra_edges=" << extra_edges << endl;

        float total_my   = 0;
        float total_leda = 0;
        bool last_result_my   = false;
        bool last_result_leda = false;
        int  bipartite_count  = 0; // πόσες φορές βγήκε διμερές

        for (int rep = 0; rep < 100; rep++)
        {
            // Νέο γράφημα σε κάθε επανάληψη (λόγω τυχαίων ακμών)
            graph G;
            build_grid_with_diagonals(G, k, extra_edges);

            list<node> V1, V2, cycle;
            node_array<int> color(G, UNCOLORED);

            float T = leda::used_time();
            last_result_my = my_bipar_checker(G, V1, V2, color, cycle);
            total_my += leda::used_time(T);

            if (last_result_my) bipartite_count++;

            list<node> A, B;
            T = leda::used_time();
            last_result_leda = Is_Bipartite(G, A, B);
            total_leda += leda::used_time(T);
        }

        cout << "Διμερές σε " << bipartite_count << "/100 επαναλήψεις" << endl;
        cout << "my_bipar_checker μέσος χρόνος: " << total_my/100  << " sec" << endl;
        cout << "Is_Bipartite μέσος χρόνος:     " << total_leda/100 << " sec" << endl;
        cout << endl;
    }
}



