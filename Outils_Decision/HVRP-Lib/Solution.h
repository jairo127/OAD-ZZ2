#pragma once

#include "Constantes.h"
#include "Tournee.h"

class Solution
{
	int nb_tournee; // nombre de tournée dans la solution
	Tournee tournees[MAX_TOURNEE]; // tournées de la solution de 0 à nb_tournee-1
	float cout; // cout total de la solution (CF + CV de chaque tournée)
	Solution();
	bool check_solution(Instance inst);
};

