#pragma once

#include "Constantes.h"
#include "Tournee.h"
#include <vector>

class Solution
{
public:
	/// <summary>
	/// Tour Geant décrivant la solution au HVRP
	/// </summary>
	std::vector<int> tour_geant; 

	/// <summary>
	/// Nombre de tournée dans la solution
	/// </summary>
	int nb_tournee;

	/// <summary>
	/// Tournées de la solution de 0 à nb_tournee-1
	/// </summary>
	Tournee tournees[MAX_TOURNEE];

	/// <summary>
	/// Cout total de la solution (CF + CV de chaque tournée)
	/// </summary>
	float cout;

	/// <summary>
	/// Constructeur par défaut de la solution
	/// </summary>
	Solution();

	/// <summary>
	/// Vérifie si la solution est cohérente
	/// </summary>
	/// <param name="inst">Instance de référence</param>
	/// <returns>true si la solution est correcte sinon false</returns>
	bool check_solution(Instance inst);
};