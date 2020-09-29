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

void test_plus_court_chemin()
{
    Graph G = Graph("graph_p2");
    Solution sol;
    applyDijkstra(G, 1, 210, sol);
    sol.chemin_le_plus_court(1, 210, true);
    cout << __FUNCTION__ << " done!" << endl;
}

void test_perf_dijkstra()
{
    int iter = 2000;
    long temps = 0;
    Graph G = Graph("graph_p2");
    Solution sol;
    for (int i = 0; i < iter; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        applyDijkstra(G, 1, 210, sol);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        temps += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); // [µs]
    }
    std::cout << "Temps moyen Dijkstra : " << temps / iter << " microsecondes" << std::endl;
    cout << __FUNCTION__ << " done!" << endl;
}

void test_perf_bellman()
{
    int iter = 2000;
    long temps = 0;
    Graph G = Graph("graph_p2");
    Solution sol;
    
    int ordre[nmax_sommets];
    // Ordre croissant
    for (int i = 1; i <= 210; i++)
        ordre[i] = i;
    
    // Test perf sur ordre croissant
    for (int i = 0; i < iter; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        applyBellman(G, ordre, sol);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        temps += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); // [µs]
    }
    std::cout << "Temps moyen Bellman (croissant) : " << temps / iter << " microsecondes" << std::endl;

    temps = 0;
    // Ordre décroissant
    for (int i = 1; i <= 210; i++)
        ordre[i] = 211 - i;
    
    // Test perf sur ordre décroissant
    for (int i = 0; i < iter; i++)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        applyBellman(G, ordre, sol);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        temps += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count(); // [µs]
    }
    std::cout << "Temps moyen Bellman (decroissant) : " << temps / iter << " microsecondes" << std::endl;
    cout << __FUNCTION__ << " done!" << endl;
}

void test_dates_plus_tot()
{
    Graph G = Graph("graph_travaux");
    Solution sol;
    applyPlusTard(G, 1, 14, sol);
    displaySolution(1, 14, sol, false);
    cout << __FUNCTION__ << " done!" << endl;
}