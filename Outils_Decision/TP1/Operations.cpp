#include <iostream>
#include "Operations.hpp"

using namespace std;

void createGraph(Graph& G)
{
    G.setN(9);

    //G.ns[1] = 2;
    //G.S[1][1] = 4;
    //G.l[1][1] = 4;
    //G.S[1][2] = 2;
    //G.l[1][2] = 10;

    G.insertNS(1, 2);
    G.insertS(1, 1, 4);
    G.insertS(1, 2, 2);
    G.insertL(1, 1, 4);
    G.insertL(1, 2, 10);

    //G.ns[2] = 2;
    //G.S[2][1] = 3;
    //G.l[2][1] = 1;
    //G.S[2][2] = 5;
    //G.l[2][2] = 2;

    G.insertNS(2, 2);
    G.insertS(2, 1, 3);
    G.insertS(2, 2, 5);
    G.insertL(2, 1, 1);
    G.insertL(2, 2, 2);

    //G.ns[3] = 2;
    //G.S[3][1] = 6;
    //G.l[3][1] = 4;
    //G.S[3][2] = 8;
    //G.l[3][2] = 2;

    G.insertNS(3, 2);
    G.insertS(3, 1, 6);
    G.insertS(3, 2, 8);
    G.insertL(3, 1, 4);
    G.insertL(3, 2, 2);

    //G.ns[4] = 1;
    //G.S[4][1] = 6;
    //G.l[4][1] = 12;

    G.insertNS(4, 1);
    G.insertS(4, 1, 6);
    G.insertL(4, 1, 12);

    //G.ns[5] = 2;
    //G.S[5][1] = 3;
    //G.l[5][1] = 9;
    //G.S[5][2] = 8;
    //G.l[5][2] = 3;

    G.insertNS(5, 2);
    G.insertS(5, 1, 3);
    G.insertS(5, 2, 8);
    G.insertL(5, 1, 9);
    G.insertL(5, 2, 3);

    //G.ns[6] = 1;
    //G.S[6][1] = 7;
    //G.l[6][1] = 5;

    G.insertNS(6, 1);
    G.insertS(6, 1, 7);
    G.insertL(6, 1, 5);

    //G.ns[7] = 2;
    //G.S[7][1] = 9;
    //G.l[7][1] = 3;
    //G.S[7][2] = 8;
    //G.l[7][2] = 3;

    G.insertNS(7, 2);
    G.insertS(7, 1, 9);
    G.insertS(7, 2, 8);
    G.insertL(7, 1, 3);
    G.insertL(7, 2, 3);

    //G.ns[8] = 1;
    //G.S[8][1] = 9;
    //G.l[8][1] = 3;

    G.insertNS(8, 1);
    G.insertS(8, 1, 9);
    G.insertL(8, 1, 3);

    G.insertNS(9, 0);
}

void applyBellman(Graph& G, const int* ordre, Solution& sol)
{
    bool stop = true;
    sol.insertM(ordre[1], 0);
    sol.insertPere(ordre[1], -1);
    for (int k = 2; k <= nmax_sommets; k++)
        sol.insertM(k, inf);
    while (stop)
    {
        stop = false;
        for (int i = 1; i <= G.getN(); i++)
        {
            int imin = ordre[i];

            // mettre à jour tous les successeurs de imin
            int nb_succ = G.getNS(imin);
            for (int j = 1; j <= nb_succ; j++)
            {
                int k = G.getS(imin, j);
                int m_dest = sol.getM(imin) + G.getL(imin, j);
                if (m_dest < sol.getM(k))
                {
                    sol.insertM(k, m_dest);
                    sol.insertPere(k, imin);
                    stop = true;
                }
            }
        }
    }
}


void applyDijkstra(Graph& G, const int start, const int end, Solution& sol)
{
    // Initialisation
    int T[nmax_sommets + 1];
    sol.insertM(start, 0);
    for (int k = 2; k <= nmax_sommets; k++)
        sol.insertM(k, inf);
    for (int k = 0; k <= nmax_sommets; k++) {
        T[k] = 0;
        sol.insertPere(k, 0);
    }


    for (int i = start; i <= end; i++) {
        // recherche sommet marque la plus petite
        int min = inf, imin = 0;
        for (int j = 1; j <= G.getN(); j++)
        {
            if ((sol.getM(j) <= min) && (T[j] == 0))
            {
                min = sol.getM(j);
                imin = j;
            }
        }
        
        // mettre à jour tous les successeurs de imin
        int nb_succ = G.getNS(imin);
        for (int j = 1; j <= nb_succ; j++)
        {
            int k = G.getS(imin, j);
            int m_dest = sol.getM(imin) + G.getL(imin, j);
            if ( m_dest < sol.getM(k))
            {
                sol.insertM(k, m_dest);
                sol.insertPere(k, imin);
            }
        }
        T[imin] = 1;
    }
}

void applyLevel(Graph& G, const int start, const int end, Solution& sol)
{
    int T[nmax_sommets + 1];
    for (int k = 0; k <= nmax_sommets; k++)
        T[k] = 0;
    sol.insertNiv(start, 0);
    for (int i = 1; i <= nmax_sommets; i++)
        sol.insertNiv(i, inf);

    while (T[end] == 0)
    {
        // recherche sommet niveau le plus petit non traité
        int imin = 0;
        for (int j = 1; j <= G.getN(); j++)
        {
            //cout << "boucle for " << j << endl;
            if (sol.getNiv(j) < inf && T[j] == 0)
            {
                cout << "j=" << j << endl;
                imin = j;
            }
        }
        cout << "imin=" << imin << endl;
        // mettre à jour les niveaux des successeurs de imin
        int nb_succ = G.getNS(imin);
        for (int j = 1; j <= nb_succ; j++)
        {
            int k = G.getS(imin, j);
            int niv_dest = sol.getNiv(imin) <444+ 1;
            if (niv_dest < sol.getNiv(k))
                sol.insertNiv(k, niv_dest);
        }
        T[imin] = 1;
    }
}

void displaySolution(const int start, const int end, Solution& sol, const bool niv)
{
    for (int i = start; i <= end; i++) {
        cout << i
            << " : PERE->" << sol.getPere(i)
            << " MARQUE->" << sol.getM(i);
        if (niv)
            cout << " NIVEAU->" << sol.getNiv(i);
        cout << endl;
    }
}