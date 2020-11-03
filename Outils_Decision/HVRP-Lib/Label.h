#pragma once
#include <vector>
#include "Instance.h"

class Label
{
public:
	/// <summary>
	/// Nombre de camion restant de chaque type i
	/// </summary>
	std::vector<int> nb_camion_restant;

	/// <summary>
	/// Cout de la tournée actuelle
	/// </summary>
	int cout_total;

	/// <summary>
	/// Constructeur par défaut
	/// </summary>
	Label();

	/// <summary>
	/// Constructeur de label en fonction d'une instance
	/// A utiliser de préférence !
	/// </summary>
	/// <param name="inst">Instance de référence</param>
	Label(Instance inst);

	/// <summary>
	/// Compare ce label à un label l
	/// </summary>
	/// <param name="l">Label auquel on compare</param>
	/// <returns>(this < l)=1, (this > l)=2, (this ? l)=0</returns>
	int compare(Label l); 
};

