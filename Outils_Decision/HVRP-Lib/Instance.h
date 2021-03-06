#pragma once

#include <iostream>
#include "Constantes.h"

// � instancier dans le main (new, astuce r�f�rence)
class Instance
{
public:
	/// <summary>
	/// Nombre de noeuds total (92 noeuds -> d�p�t compris, 91 clients -> d�p�t exclus)
	/// </summary>
	int nb_noeud; 

	/// <summary>
	/// Nombre de type de camion diff�rents
	/// </summary>
	int nb_type_camion;

	/// <summary>
	/// Distance de i vers j (de 0 � 91)
	/// </summary>
	float D[MAX_NOEUD + 1][MAX_NOEUD + 1]; 

	/// <summary>
	/// Quantit� demand� par le noeud i (de 1 � 91)
	/// </summary>
	int Q[MAX_NOEUD + 1];

	/// <summary>
	/// Nombre de camion pour le type i (de 1 � nb_type_camion)
	/// </summary>
	int nb_camion[MAX_TYPE + 1];

	/// <summary>
	/// Capacit� des camions de type i (de 1 � nb_type_camion)
	/// </summary>
	int cap_camion[MAX_TYPE + 1];

	/// <summary>
	/// Cout fixe des camions de type i (de 1 � nb_type_camion)
	/// </summary>
	float cout_fixe_camion[MAX_TYPE + 1];

	/// <summary>
	/// Cout fixe des camions de type i (de 1 � nb_type_camion)
	/// </summary>
	float cout_variable_camion[MAX_TYPE + 1];

	/// <summary>
	/// Lecture d'un fichier d'instance
	/// </summary>
	/// <param name="file_name">Chemin du fichier</param>
	void lecture(std::string file_name);
};

