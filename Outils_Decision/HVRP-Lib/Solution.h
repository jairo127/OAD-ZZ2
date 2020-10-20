#pragma once

#include "Constantes.h"
#include "Tournee.h"

class Solution
{
	int nb_tournee; // nombre de tourn�e dans la solution
	Tournee tournees[MAX_TOURNEE]; // tourn�es de la solution de 0 � nb_tournee-1
	float cout; // cout total de la solution (CF + CV de chaque tourn�e)
	Solution();
	bool check_solution(Instance inst);
};

