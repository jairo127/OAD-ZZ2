#pragma once

#include "Constantes.h"
#include "Instance.h"

class Tournee
{
public:
	/// <summary>
	/// Nombre de noeuds parcouru
	/// </summary>
	int nb_noeud; 

	/// <summary>
	/// Clients parcourus (de 0 � nb_noeud-1)
	/// </summary>
	int clients[MAX_CLIENT];

	/// <summary>
	/// Type de camion affect� � la tourn�e
	/// </summary>
	int camion;

	/// <summary>
	/// Volume de la tourn�e
	/// </summary>
	int volume;

	/// <summary>
	/// Cout total de la tourn�e
	/// </summary>
	float cout;

	/// <summary>
	/// Constructeur par d�faut de tourn�e
	/// </summary>
	Tournee();

	/// <summary>
	/// Ins�re un noeud dans la tourn�e
	/// </summary>
	/// <param name="i">Emplacement d'insertion dans la tourn�e</param>
	/// <param name="noeud">Num�ro du noeud</param>
	/// <param name="inst">Instance de r�f�rence</param>
	void inserer_noeud(int i, int noeud, Instance inst);
};

