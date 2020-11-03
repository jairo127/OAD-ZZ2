#pragma once

#include "Constantes.h"
#include "Tournee.h"
#include <vector>

class Solution
{
public:
	/// <summary>
	/// Tour Geant d�crivant la solution au HVRP
	/// </summary>
	std::vector<int> tour_geant; 

	/// <summary>
	/// Nombre de tourn�e dans la solution
	/// </summary>
	int nb_tournee;

	/// <summary>
	/// Tourn�es de la solution de 0 � nb_tournee-1
	/// </summary>
	Tournee tournees[MAX_TOURNEE];

	/// <summary>
	/// Cout total de la solution (CF + CV de chaque tourn�e)
	/// </summary>
	float cout;

	/// <summary>
	/// Constructeur par d�faut de la solution
	/// </summary>
	Solution();

	/// <summary>
	/// V�rifie si la solution est coh�rente
	/// </summary>
	/// <param name="inst">Instance de r�f�rence</param>
	/// <returns>true si la solution est correcte sinon false</returns>
	bool check_solution(Instance inst);
};