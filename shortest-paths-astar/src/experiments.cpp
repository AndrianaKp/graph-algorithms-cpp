#include "experiments.hpp"
#include <limits>

void runGridExperiment(int r, int c, int minW, int maxW)
{
    // Δημιουργία grid
    Graph g;
    generateGrid(g, r, c, minW, maxW);

    // Επιλογή τυχαίων s, t
    srand(42);
    int row_s = rand() % r;
    int row_t = rand() % r;
    Vertex s = row_s * c;
    Vertex t = row_t * c + (c-1);

    std::cout << "Grid " << r << "x" << c 
              << " βάρη [" << minW << "," << maxW << "]" << std::endl;
    std::cout << "s=" << s << " t=" << t << std::endl;

    // Εκτέλεση Dijkstra
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<int,int> resD = dijkstra(g, s, t);
    int distD = resD.first;
    int countD = resD.second;
    auto end = std::chrono::high_resolution_clock::now();
    auto timeD = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Dijkstra" << std::endl;
    std::cout << "  Απόσταση: " << distD << std::endl;
    std::cout << "  Κόμβοι: " << countD << std::endl;
    std::cout << "  Χρόνος: " << timeD << " ms" << std::endl;   

    if(minW == 1 && maxW == 2)
{
    // A* με ευκλείδεια
    EuclideanHeuristic heuristic(g, t);

    auto start2 = std::chrono::high_resolution_clock::now();
    std::pair<int,int> resA = astar(g, s, t, heuristic);
    int distA = resA.first;
    int countA = resA.second;
    auto end2 = std::chrono::high_resolution_clock::now();
    auto timeA = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "A* (Ευκλείδεια)" << std::endl;
    std::cout << "  Απόσταση: " << distA << std::endl;
    std::cout << "  Κόμβοι: " << countA << std::endl;
    std::cout << "  Χρόνος: " << timeA << " ms" << std::endl;
}
else
{
    // Προεπεξεργασία landmarks
    Vertex L1 = 0;
    Vertex L2 = r*c - 1;
    std::vector<int> distFromL1 = dijkstraAll(g, L1);
    std::vector<int> distToL2 = dijkstraAllReverse(g, L2);
    LandmarkHeuristic heuristic(distFromL1, distToL2, t);

    auto start2 = std::chrono::high_resolution_clock::now();
    std::pair<int,int> resA = astar(g, s, t, heuristic);
    int distA = resA.first;
    int countA = resA.second;
    auto end2 = std::chrono::high_resolution_clock::now();
    auto timeA = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "A* (Landmarks)" << std::endl;
    std::cout << "  Απόσταση: " << distA << std::endl;
    std::cout << "  Κόμβοι: " << countA << std::endl;
    std::cout << "  Χρόνος: " << timeA << " ms" << std::endl;
}

// Bonus: LEDA DIJKSTRA_T
leda::graph ledaG;
edge_array<int> ledaCost;
std::vector<leda::node> nodeMap;
boostToLeda(g, ledaG, ledaCost, nodeMap);

leda::node ledaS = nodeMap[s];
leda::node ledaT = nodeMap[t];
runLedaDijkstra(ledaG, ledaCost, ledaS, ledaT);

}

void runRandomExperiment(int n, int m, int minW, int maxW)
{
    // Δημιουργία τυχαίου γραφήματος
    Graph g;
    generateRandom(g, n, m, minW, maxW);

    // Επιλογή τυχαίων s, t από ΟΛΟΥΣ τους κόμβους
    srand(42);
    int INF = std::numeric_limits<int>::max();
    Vertex s, t;

    // δοκίμασε μέχρι να βρεις έγκυρο ζεύγος
    int attempts = 0;
    do {
        s = rand() % n;
        t = rand() % n;
        if(s == t) continue;
        std::pair<int,int> test = dijkstra(g, s, t);
        if(test.first != INF) break;
        attempts++;
        if(attempts > 100) {
            std::cout << "Δεν βρέθηκε έγκυρο ζεύγος!" << std::endl;
            return;
        }
    } while(true);

    std::cout << "Τυχαίο γράφημα " << n << " κόμβοι, " << m << " ακμές"
              << " βάρη [" << minW << "," << maxW << "]" << std::endl;

    // Εκτέλεση Dijkstra
    auto start = std::chrono::high_resolution_clock::now();
    std::pair<int,int> resD = dijkstra(g, s, t);
    int distD = resD.first;
    int countD = resD.second;
    auto end = std::chrono::high_resolution_clock::now();
    auto timeD = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Dijkstra" << std::endl;
    std::cout << "  Απόσταση: " << distD << std::endl;
    std::cout << "  Κόμβοι: " << countD << std::endl;
    std::cout << "  Χρόνος: " << timeD << " ms" << std::endl;   

    
    // Προεπεξεργασία landmarks
    Vertex L1 = 0;
    Vertex L2 = n - 1;
    std::vector<int> distFromL1 = dijkstraAll(g, L1);
    std::vector<int> distToL2 = dijkstraAllReverse(g, L2);
    LandmarkHeuristic heuristic(distFromL1, distToL2, t);

    auto start2 = std::chrono::high_resolution_clock::now();
    std::pair<int,int> resA = astar(g, s, t, heuristic);
    int distA = resA.first;
    int countA = resA.second;
    auto end2 = std::chrono::high_resolution_clock::now();
    auto timeA = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();

    std::cout << "A* (Landmarks)" << std::endl;
    std::cout << "  Απόσταση: " << distA << std::endl;
    std::cout << "  Κόμβοι: " << countA << std::endl;
    std::cout << "  Χρόνος: " << timeA << " ms" << std::endl;

    // Bonus: LEDA DIJKSTRA_T
    leda::graph ledaG;
    edge_array<int> ledaCost;
    std::vector<leda::node> nodeMap;
    boostToLeda(g, ledaG, ledaCost, nodeMap);

    leda::node ledaS = nodeMap[s];
    leda::node ledaT = nodeMap[t];
    runLedaDijkstra(ledaG, ledaCost, ledaS, ledaT);

}