#pragma once

#include <iostream>
#include "Constantes.h"

// à instancier dans le main (new, astuce référence)
class Instance
{
public:
	/// <summary>
	/// Nombre de noeuds sans compter le dépot
	/// (92 noeuds -> dépôt compris, 91 clients -> dépôt exclus)
	/// le dernier noeud est numéroté 91!
	/// </summary>
	int nb_noeud; 

	/// <summary>
	/// Nombre de type de camion différents
	/// </summary>
	int nb_type_camion;

	/// <summary>
	/// Distance de i vers j (de 0 à 91) 
	/// -> 0 sera le dépot
	/// Dernier élément inséré à D[nb_noeud][nb_noeud]
	/// </summary>
	float D[MAX_NOEUD + 1][MAX_NOEUD + 1]; 

	/// <summary>
	/// Quantité demandé par le noeud i (de 1 à 91)
	/// Dernier élément inséré à Q[nb_noeud][nb_noeud]
	/// </summary>
	int Q[MAX_NOEUD + 1];

	/// <summary>
	/// Nombre de camion pour le type i (de 1 à nb_type_camion)
	/// </summary>
	int nb_camion[MAX_TYPE + 1];

	/// <summary>
	/// Capacité des camions de type i (de 1 à nb_type_camion)
	/// </summary>
	int cap_camion[MAX_TYPE + 1];

	/// <summary>
	/// Cout fixe des camions de type i (de 1 à nb_type_camion)
	/// </summary>
	float cout_fixe_camion[MAX_TYPE + 1];

	/// <summary>
	/// Cout fixe des camions de type i (de 1 à nb_type_camion)
	/// </summary>
	float cout_variable_camion[MAX_TYPE + 1];

	/// <summary>
	/// Lecture d'un fichier d'instance
	/// </summary>
	/// <param name="file_name">Chemin du fichier</param>
	void lecture(std::string file_name);

	/// <summary>
	/// Affichage du contenu de l'objet d'instance
	/// </summary>
	void afficher();

	void GraspHVRP(int iterMax);

};

