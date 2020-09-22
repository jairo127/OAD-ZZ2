#ifndef SOLUTION
#define SOLUTION

#include "Constants.hpp"

/**
* Name : Solution
* Desc : Represente la solution des opérations effectués sur un graphe
*		 (Dijkstra, Niveaux...)
*/
class Solution
{
private:
	int m[nmax_sommets + 1]; // marques
	int pere[nmax_sommets + 1]; // pères
	int niv[nmax_sommets + 1]; // niveaux

public:
	// Methods
	void insertM(int i, int val);
	void insertPere(int i, int val);
	void insertNiv(int i, int val);
	int getM(int i);
	int getPere(int i);
	int getNiv(int i);
};

#endif;

