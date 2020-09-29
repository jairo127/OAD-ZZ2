#include "Solution.hpp"

// Methods
void Solution::insertM(int i, float val)
{
	m[i] = val;
}

void Solution::insertPere(int i, int val)
{
	pere[i] = val;
}

void Solution::insertNiv(int i, int val)
{
	niv[i] = val;
}

float Solution::getM(int i)
{
	return m[i];
}

int Solution::getPere(int i)
{
	return pere[i];
}

int Solution::getNiv(int i)
{
	return niv[i];
}

float Solution::chemin_le_plus_court(int deb, int fin, bool display)
{
	// On suppose que l'algorithme à bien été évaluer de 'deb' à 'fin'
	// Sinon ca ne marche pas
	if (display)
	{
		int pere = fin;
		while (pere != deb)
		{
			std::cout << pere << std::endl;
			pere = getPere(pere);
		}
		std::cout << pere << std::endl;
	}
	return getM(fin);
}