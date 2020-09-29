#ifndef SOLUTION
#define SOLUTION

#include <iostream>
#include "Constants.hpp"

/**
* Name : Solution
* Desc : Represente la solution des opérations effectués sur un graphe
*		 (Dijkstra, Niveaux...)
*/
class Solution
{
private:
	float m[nmax_sommets + 1]; // marques
	int pere[nmax_sommets + 1]; // pères
	int niv[nmax_sommets + 1]; // niveaux

public:
	// Methods
	void insertM(int i, float val);
	void insertPere(int i, int val);
	void insertNiv(int i, int val);
	float getM(int i);
	int getPere(int i);
	int getNiv(int i);
	float chemin_le_plus_court(int deb, int fin, bool display);
};

#endif;

