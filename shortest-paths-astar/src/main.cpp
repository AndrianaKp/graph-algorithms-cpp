#include "graph.hpp"
#include "experiments.hpp"
#include <iostream>

int main()
{
    std::cout << "Πειράματα Grid: " << std::endl;

    runGridExperiment(30, 1000, 1, 2);
    runGridExperiment(60, 1000, 1, 2);
    runGridExperiment(80, 1000, 1, 2);
    runGridExperiment(30, 1000, 1, 100);
    runGridExperiment(60, 1000, 1, 100);
    runGridExperiment(80, 1000, 1, 100);
    runGridExperiment(30, 1000, 1, 10000);
    runGridExperiment(60, 1000, 1, 10000);
    runGridExperiment(80, 1000, 1, 10000);

    std::cout << "Πειράματα τυχαίοι" << std::endl;

    runRandomExperiment(10000, 20000, 1, 100);
    runRandomExperiment(20000, 40000, 1, 100);
    runRandomExperiment(60000, 120000, 1, 100);
    runRandomExperiment(10000, 20000, 1, 10000);
    runRandomExperiment(20000, 40000, 1, 10000);
    runRandomExperiment(60000, 120000, 1, 10000);

    return 0;
}