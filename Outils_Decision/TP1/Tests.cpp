#include "Tests.hpp"

void test_src_dijkstra()
{
    Graph G = Graph(9);
    Solution sol;
    createGraph(G);
    applyDijkstra(G, 1, 9, sol);
    displaySolution(1, 9, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}

void test_src_bellman()
{
    Graph G = Graph(9);
    Solution sol;
    int ordre[nmax_sommets];
    ordre[1] = 1; ordre[2] = 3; ordre[3] = 5;
    ordre[4] = 7; ordre[5] = 9; ordre[6] = 2;
    ordre[7] = 4; ordre[8] = 6; ordre[9] = 8;
    createGraph(G);
    applyBellman(G, ordre, sol);
    displaySolution(1, 9, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}

void test_file_dijkstra()
{
    Graph G = Graph("graph_p2");
    Solution sol;
    applyDijkstra(G, 1, 210, sol);
    displaySolution(1, 210, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}

void test_file_bellman_standard()
{
    Graph G = Graph("graph_p2");
    Solution sol;
    int ordre[nmax_sommets];
    for (int i = 1; i <= 210; i++)
        ordre[i] = i;
    applyBellman(G, ordre, sol);
    displaySolution(1, 210, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}

void test_file_bellman_special()
{
    Graph G = Graph("graph_p2");
    Solution sol;
    int ordre[nmax_sommets];
    int cpt = 2;
    ordre[1] = 1; ordre[210] = 210;
    for (int i = 209; i >= 2; i--)
    {
        ordre[cpt] = i;
        cpt++;
    }
    applyBellman(G, ordre, sol);
    displaySolution(1, 210, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}