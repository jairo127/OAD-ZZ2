#pragma once

#include <iostream>
#include "Constantes.h"

// à instancier dans le main (new)
class Instance
{
public:
	int nb_noeud; // nombre de noeuds total (92 noeuds, 91 clients)
	int nb_type_camion; // nombre de type de camion différents
	float D[MAX_NOEUD + 1][MAX_NOEUD + 1]; // distance de i vers j (de 0 à 91)
	int Q[MAX_NOEUD + 1]; // quantité de demandé par le noeud i (de 1 à 91)
	int nb_camion[MAX_TYPE + 1]; // nombre de camion pour le type i
	int cap_camion[MAX_TYPE + 1]; // capacité des camions de type i
	float cout_fixe_camion[MAX_TYPE + 1]; // cout fixe des camions de type i
	float cout_variable_camion[MAX_TYPE + 1]; // cout fixe des camions de type i

	void lecture(std::string file_name);
};

