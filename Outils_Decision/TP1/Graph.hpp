#ifndef GRAPH
#define GRAPH

#include <iostream>
#include "Constants.hpp"

using namespace std;

/**
* Name : Graph
* Desc : Décrit un graphe avec son nombre de sommets,
*        les successeurs de chaque sommet, le poids de
*        chaque arc et le nombre de successeur de chaque sommet.
*/
class Graph
{
private:
    int n;                              // nb de sommets
    int S[nmax_sommets + 1][nmax_succ]; // successeurs
    int l[nmax_sommets + 1][nmax_succ]; // poids
    int ns[nmax_sommets + 1];           // nb de successeurs

public:
    // Constructors
    Graph(int n);
    Graph(string file_path);

    // Methods
    int getN();
    void setN(int new_n);
    void insertS(int i, int j, int val);
    void insertL(int i, int j, int val);
    void insertNS(int i, int val);
    int getS(int i, int j);
    int getL(int i, int j);
    int getNS(int i);
};

#endif

