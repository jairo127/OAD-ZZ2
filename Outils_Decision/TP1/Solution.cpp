#include "Solution.hpp"

// Methods
void Solution::insertM(int i, int val)
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

int Solution::getM(int i)
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