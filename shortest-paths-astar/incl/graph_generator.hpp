#pragma once

#include "graph.hpp"
#include <random>
#include <utility>

void generateGrid(Graph& g, int r, int c, int minW, int maxW);
void generateRandom(Graph& g, int n, int m, int minW, int maxW);