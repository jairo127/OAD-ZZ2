#pragma once
#include "Constantes.h"
#include <iostream>
#include <string>

using namespace std;

class Instance
{
public:
	int n; // NB pièces
	int m; // NB machines
	int M[nmax][mmax]; // Ordre de passage de chaque pièce par machine
	int P[nmax][mmax]; // Temps de passage de chaque pièce sur machine
	string name; // Nom de l'instance

	// Constructeur par défaut
	Instance();
	// Fonction de lecture d'un fichier LaXXX
	void Lecture(std::string nom_fichier);
	// Fonction d'affichage d'un instance LaXXX
	void Afficher();

	// GRASP
	void Grasp(int iterMax);

};

