/*
 * experiments.cpp
 * Υλοποίηση πειραματικής αξιολόγησης με K=5 επαναλήψεις σε
 * διαφορετικά τυχαία γραφήματα για κάθε μέγεθος n.
 * Αναφέρεται ο ΜΕΣΟΣ χρόνος εκτέλεσης για αξιοπιστία.
 */

#include "../incl/experiments.hpp"
#include <iomanip> //για σταθερό αριθμό δεκαδικών ψηφίων

void assign_random_costs(ugraph& G, edge_array<int>& cost)
{
    edge e;
    forall_edges(e, G)
        cost[e] = rand() % 1000 + 1; // απο 1 ως 1000
}

/* μετράει χρόνο εκτέλεσης και των 3 αλγορίθμων
 * σε ένα γράφημα G με βάρη cost. Επιστρέφει τους χρόνους μέσω
 * παραμέτρων αναφοράς t_prim, t_sollin, t_leda.
 * Αν run_sollin=false, το t_sollin τίθεται σε -1.
 */
void measure_times(ugraph& G, edge_array<int>& cost, bool run_sollin,
                   float& t_prim, float& t_sollin, float& t_leda)
{
    float T; // για την used_time
    list<edge> mst; //αποθηκεύεται προσωρινά το αποτέλεσμα κάθε αλγορίθμου

    // Prim
    used_time(T); //ξεκινάει να μετράει
    my_prim(G, cost, mst); // τρέχουμε τον αλγόριθμο
    t_prim = used_time(T); // σταματάει να μετράει και αποθηκεύουμε τη διάρκεια στο t_prim
    mst.clear(); //αδειάζει η λίστα για τον επόμενο αλγόριθμο

    // Sollin
    t_sollin = -1;
    if (run_sollin) {
        used_time(T);
        my_sollin(G, cost, mst);
        t_sollin = used_time(T);
        mst.clear();
    }

    // LEDA MIN_SPANNING_TREE
    used_time(T);
    mst = MIN_SPANNING_TREE(G, cost); // επιστρέφει τη λίστα ως return value
    t_leda = used_time(T);
    mst.clear();
}

void print_result(int n, int m, float t_prim, float t_sollin, float t_leda,
                  bool run_sollin)
{
    std::cout << std::fixed << std::setprecision(6)
               << n << "\t" << m << "\t"
               << t_prim << "\t";
    if (run_sollin)
        std::cout << t_sollin << "\t";
    else
        std::cout << "N/A\t\t";
    std::cout << t_leda << std::endl;
}

// Τυχαία αραιά γραφήματα (m = 5n)
// K διαφορετικά γραφήματα, μέσος χρόνος

void run_experiment_random_sparse(int n, int K, bool run_sollin)
{
    int m = 5 * n; //πλήθος ακμών γραμμικό ως προς τους κόμβους
    float sum_prim=0, sum_sollin=0, sum_leda=0;

    for (int k = 0; k < K; k++)
    {
        graph G_tmp;
        random_simple_undirected_graph(G_tmp, n, m);
        ugraph G(G_tmp);
        edge_array<int> cost(G);
        assign_random_costs(G, cost);

        float t_prim, t_sollin, t_leda;
        measure_times(G, cost, run_sollin, t_prim, t_sollin, t_leda);

        sum_prim  += t_prim;
        sum_leda  += t_leda;
        if (run_sollin) sum_sollin += t_sollin;
    }

    print_result(n, m,
                 sum_prim/K,
                 run_sollin ? sum_sollin/K : -1,
                 sum_leda/K,
                 run_sollin);
}

// Τυχαία πυκνά γραφήματα (m = n²/4)
// K διαφορετικά γραφήματα, μέσος χρόνος

void run_experiment_random_dense(int n, int K, bool run_sollin)
{
    int m = n * n / 4; //τετραγωνικό πλήθος ακμών 
    float sum_prim=0, sum_sollin=0, sum_leda=0;

    for (int k = 0; k < K; k++)
    {
        graph G_tmp;
        random_simple_undirected_graph(G_tmp, n, m);
        ugraph G(G_tmp);
        edge_array<int> cost(G);
        assign_random_costs(G, cost);

        float t_prim, t_sollin, t_leda;
        measure_times(G, cost, run_sollin, t_prim, t_sollin, t_leda);

        sum_prim  += t_prim;
        sum_leda  += t_leda;
        if (run_sollin) sum_sollin += t_sollin;
    }

    print_result(n, m,
                 sum_prim/K,
                 run_sollin ? sum_sollin/K : -1,
                 sum_leda/K,
                 run_sollin);
}

// Τυχαία επίπεδα γραφήματα 
// K διαφορετικά γραφήματα, μέσος χρόνος

void run_experiment_planar(int n, int K, bool run_sollin)
{
    float sum_prim=0, sum_sollin=0, sum_leda=0;
    int last_m = 0; //μετά από κάθε επανάληψη ενημερώνεται με το πραγματικό G.number_of_edges()

    for (int k = 0; k < K; k++)
    {
        graph G_tmp;
        random_planar_graph(G_tmp, n);
        ugraph G(G_tmp);
        last_m = G.number_of_edges();
        edge_array<int> cost(G);
        assign_random_costs(G, cost);

        float t_prim, t_sollin, t_leda;
        measure_times(G, cost, run_sollin, t_prim, t_sollin, t_leda);

        sum_prim  += t_prim;
        sum_leda  += t_leda;
        if (run_sollin) sum_sollin += t_sollin;
    }

    // για επίπεδα το m ποικίλει, τυπώνουμε το τελευταίο ως ενδεικτικό
    print_result(n, last_m,
                 sum_prim/K,
                 run_sollin ? sum_sollin/K : -1,
                 sum_leda/K,
                 run_sollin);
}

// Πλήρη γραφήματα 
// Ντετερμινιστικό γράφημα, K διαφορετικά τυχαία βάρη

void run_experiment_complete(int n, int K, bool run_sollin)
{
    graph G_tmp;
    complete_graph(G_tmp, n);
    ugraph G(G_tmp);
    int m = G.number_of_edges();

    float sum_prim=0, sum_sollin=0, sum_leda=0;

    for (int k = 0; k < K; k++)
    {
        edge_array<int> cost(G);
        assign_random_costs(G, cost);   // διαφορετικά βάρη κάθε φορά

        float t_prim, t_sollin, t_leda;
        measure_times(G, cost, run_sollin, t_prim, t_sollin, t_leda);

        sum_prim  += t_prim;
        sum_leda  += t_leda;
        if (run_sollin) sum_sollin += t_sollin;
    }

    print_result(n, m,
                 sum_prim/K,
                 run_sollin ? sum_sollin/K : -1,
                 sum_leda/K,
                 run_sollin);
}

// Grid γραφήματα n×n 
// Ντετερμινιστικό γράφημα, K διαφορετικά τυχαία βάρη

void run_experiment_grid(int n, int K, bool run_sollin)
{
    graph G_tmp;
    grid_graph(G_tmp, n);
    ugraph G(G_tmp);
    int m = G.number_of_edges();

    float sum_prim=0, sum_sollin=0, sum_leda=0;

    for (int k = 0; k < K; k++)
    {
        edge_array<int> cost(G);
        assign_random_costs(G, cost);   // διαφορετικά βάρη κάθε φορά

        float t_prim, t_sollin, t_leda;
        measure_times(G, cost, run_sollin, t_prim, t_sollin, t_leda);

        sum_prim  += t_prim;
        sum_leda  += t_leda;
        if (run_sollin) sum_sollin += t_sollin;
    }

    print_result(n, m,
                 sum_prim/K,
                 run_sollin ? sum_sollin/K : -1,
                 sum_leda/K,
                 run_sollin);
}