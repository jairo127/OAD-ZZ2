#ifndef HEADER
#define HEADER

// WARNING : OBSOLETE FILE

// constantes
const int nmax_sommets = 20;
const int nmax_succ = 4;

typedef struct TGRAPHE {
    int n;                              // nb de sommets
    int S[nmax_sommets + 1][nmax_succ]; // successeurs
    int l[nmax_sommets + 1][nmax_succ]; // poids
    int ns[nmax_sommets + 1];           // nb de successeurs
} TGRAPHE;

typedef struct TSOLUTION {
    int m[nmax_sommets + 1]; // marques
    int pere[nmax_sommets + 1]; // pères
} TSOLUTION;

void inputGraph(TGRAPHE&);
void processGraph(TGRAPHE& G, const int start, const int end, TSOLUTION& sol);
void displaySolution(const int start, const int end, TSOLUTION& sol);
#endif
