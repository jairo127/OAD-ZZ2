// TP1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.

#include <iostream>
#include "Graph.hpp"
#include "Solution.hpp"
#include "Operations.hpp"

using namespace std;

int main(int, char**)
{
    /*
    TGRAPHE G;
    TSOLUTION sol;
    inputGraph(G);
    processGraph(G, 1, 9, sol);
    displaySolution(1, 9, sol);
    cout << "done!" << endl;
    */

    int ordre[nmax_sommets];
    ordre[1] = 1; ordre[2] = 3; ordre[3] = 5;
    ordre[4] = 7; ordre[5] = 9; ordre[6] = 2;
    ordre[7] = 4; ordre[8] = 6; ordre[9] = 8;
    Graph G = Graph("graph_p2");
    Solution sol;
    //createGraph(G);
    //applyBellman(G, ordre, sol);
    applyDijkstra(G, 1, 210, sol);
    //applyLevel(G, 1, 9, sol); // WIP
    displaySolution(1, 210, sol, false);
    cout << "done!" << endl;

    return 0;
}
