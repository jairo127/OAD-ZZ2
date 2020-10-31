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
	// Affichage d'un vecteur de Bierwith
	void AfficherVecteur();
	// Afficher Cout après avoir évalué
	void AfficherCout();
};

