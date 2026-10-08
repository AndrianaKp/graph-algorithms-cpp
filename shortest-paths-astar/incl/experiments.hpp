#pragma once

#include "graph.hpp"
#include "graph_generator.hpp"
#include "dijkstra-sp.hpp"
#include "a_star.hpp"
#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "bonus.hpp"

void runGridExperiment(int r, int c, int minW, int maxW);
void runRandomExperiment(int n, int m, int minW, int maxW);