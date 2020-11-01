#pragma once
#include "Constantes.h"
#include "Instance.h"
#include "Tuple.h"
#include <random>

class BierwithVector
{
public:
	int V[nmax * mmax];
	int St[nmax][mmax];
	Tuple Pere[nmax][mmax];
	int nb;
	int cout;

	// Constructeur par défaut
	BierwithVector();
	// Génération d'un vecteur aléatoire
	void Generer_Aleatoirement(Instance &inst);
	// Evaluation de l'instance pour ce vecteur
	void Evaluer(Instance& inst);
	// Recherche index job j et np i
	int Recherche(int j, int i, int N);
	// Procédure de recherche locale
	void Recherche_Locale(Instance& inst, int iter_max);
	// Affichage d'un vecteur de Bierwith
	void AfficherVecteur();
	// Afficher Cout après avoir évalué
	void AfficherCout();
};

