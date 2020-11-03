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
	/// Clients parcourus (de 0 à nb_noeud-1)
	/// </summary>
	int clients[MAX_CLIENT];

	/// <summary>
	/// Type de camion affecté à la tournée
	/// </summary>
	int camion;

	/// <summary>
	/// Volume de la tournée
	/// </summary>
	int volume;

	/// <summary>
	/// Cout total de la tournée
	/// </summary>
	float cout;

	/// <summary>
	/// Constructeur par défaut de tournée
	/// </summary>
	Tournee();

	/// <summary>
	/// Insére un noeud dans la tournée
	/// </summary>
	/// <param name="i">Emplacement d'insertion dans la tournée</param>
	/// <param name="noeud">Numéro du noeud</param>
	/// <param name="inst">Instance de référence</param>
	void inserer_noeud(int i, int noeud, Instance inst);
};

