#pragma once
#include "Constantes.h"
#include "Instance.h"
#include <random>

class BierwithVector
{
public:
	int V[nmax * mmax];
	int St[nmax + 1][mmax + 1];
	int Pere[nmax + 1][mmax + 1];
	int nb;
	int cout;

	// Constructeur par d�faut
	BierwithVector();
	// G�n�ration d'un vecteur al�atoire
	void Generer_Aleatoirement(Instance &inst);
	// Evaluation de l'instance pour ce vecteur
	void Evaluer(Instance& inst);
	// Affichage d'un vecteur de Bierwith
	void AfficherVecteur();
};

