#pragma once

#include "Constantes.h"
#include "Instance.h"

class Tournee
{
public:
	int nb_noeud; // nombre de noeuds parcouru
	int clients[MAX_CLIENT]; // de 0 à nb_noeud-1
	int camion; // camion affecté à la tournée
	int volume; // volume max de la tournée
	float cout; // cout total de la tournée
	Tournee();
	void inserer_noeud(int i, int noeud, Instance inst);
};

