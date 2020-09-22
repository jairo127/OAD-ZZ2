#include <iostream>
#include "Header.h"

// WARNING : OBSOLETE FILE

using namespace std;

void inputGraph(TGRAPHE& G) {
    G.n = 9;

    G.ns[1] = 2;
    G.S[1][1] = 4;
    G.l[1][1] = 4;
    G.S[1][2] = 2;
    G.l[1][2] = 10;

    G.ns[2] = 2;
    G.S[2][1] = 3;
    G.l[2][1] = 1;
    G.S[2][2] = 5;
    G.l[2][2] = 2;

    G.ns[3] = 2;
    G.S[3][1] = 6;
    G.l[3][1] = 4;
    G.S[3][2] = 8;
    G.l[3][2] = 2;

    G.ns[4] = 1;
    G.S[4][1] = 6;
    G.l[4][1] = 12;

    G.ns[5] = 2;
    G.S[5][1] = 3;
    G.l[5][1] = 9;
    G.S[5][2] = 8;
    G.l[5][2] = 3;

    G.ns[6] = 1;
    G.S[6][1] = 7;
    G.l[6][1] = 5;

    G.ns[7] = 2;
    G.S[7][1] = 9;
    G.l[7][1] = 3;
    G.S[7][2] = 8;
    G.l[7][2] = 3;

    G.ns[8] = 1;
    G.S[8][1] = 9;
    G.l[8][1] = 3;
}

void processGraph(TGRAPHE& G, const int start, const int end, TSOLUTION& sol) {
    int T[nmax_sommets + 1];
    sol.m[1] = 0;
    
    for (int k = 2; k <= nmax_sommets; k++)
        sol.m[k] = 10000; // infini
    for (int k = 0; k <= nmax_sommets; k++) {
        T[k] = 0;
        sol.pere[k] = 0;
    }
        

    for (int i = start; i <= end; i++) {
        // recherche sommet marque la plus petite
        int min = 10000, imin = -1;
        for (int j = 1; j <= G.n; j++)
        {
            if ((sol.m[j] < min) && (T[j] == 0))
            {
                min = sol.m[j];
                imin = j;
            }
        }

        // mettre à jour tous les successeurs de imin
        int nb_succ = G.ns[imin];
        for (int j = 1; j <= nb_succ; j++)
        {
            int k = G.S[imin][j];
            if (sol.m[imin] + G.l[imin][k] < sol.m[k])
            {
                sol.m[k] = sol.m[imin] + G.l[imin][k];
                sol.pere[k] = imin;
            }
        }
    }
}

void displaySolution(const int start, const int end, TSOLUTION& sol) {
    for (int i = start; i <= end; i++) {
        cout << i << " : PERE->" << sol.pere[i] << " MARQUE->" << sol.m[i] << endl;
    }
}