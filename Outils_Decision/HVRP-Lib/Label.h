#pragma once
#include <vector>

class Label
{
public:
	/// <summary>
	/// Nombre de camion restant de chaque type i
	/// </summary>
	std::vector<int> nb_camion_restant;

	/// <summary>
	/// Cout de la tourn�e actuelle
	/// </summary>
	int cout_total;

	/// <summary>
	/// Constructeur par d�faut
	/// </summary>
	Label();

	/// <summary>
	/// Compare ce label � un label l
	/// </summary>
	/// <param name="l">Label auquel on compare</param>
	/// <returns>(this < l)=1, (this > l)=2, (this ? l)=0</returns>
	int compare(Label l); 
};

