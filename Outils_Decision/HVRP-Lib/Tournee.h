#pragma once

#include "Constantes.h"
#include "Instance.h"

class Tournee
{
public:
	int nb_noeud; // nombre de noeuds parcouru
	int clients[MAX_CLIENT]; // de 0 � nb_noeud-1
	int camion; // camion affect� � la tourn�e
	int volume; // volume max de la tourn�e
	float cout; // cout total de la tourn�e
	Tournee();
	void inserer_noeud(int i, int noeud, Instance inst);
};

