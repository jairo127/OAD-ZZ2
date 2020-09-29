#ifndef OPERATIONS
#define OPERATIONS

#include "Graph.hpp"
#include "Solution.hpp"

void createGraph(Graph& G);
void applyBellman(Graph& G, const int* ordre, Solution& sol);
void applyDijkstra(Graph& G, const int start, const int end, Solution& sol);
void applyPlusTard(Graph& G, const int start, const int end, Solution& sol);
void applyLevel(Graph& G, const int start, const int end, Solution& sol);
void displaySolution(const int start, const int end, Solution& sol, const bool niv);

#endif

