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

	// Constructeur par d�faut
	BierwithVector();
	// G�n�ration d'un vecteur al�atoire
	void Generer_Aleatoirement(Instance &inst);
	// Evaluation de l'instance pour ce vecteur
	void Evaluer(Instance& inst);
	// Recherche index job j et np i
	int Recherche(int j, int i, int N);
	// Proc�dure de recherche locale
	void Recherche_Locale(Instance& inst, int iter_max);
	// Affichage d'un vecteur de Bierwith
	void AfficherVecteur();
	// Afficher Cout apr�s avoir �valu�
	void AfficherCout();
};

