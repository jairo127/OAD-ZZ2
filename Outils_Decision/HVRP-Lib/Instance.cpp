#include "pch.h"
#include "Instance.h"
#include <fstream>

void Instance::lecture(std::string file_name)
{
	long lecture;
	std::ifstream file(file_name.c_str());
	if (!file.fail())
	{
		file >> nb_noeud; // lecture nombre de noeuds
		file >> nb_type_camion; // lecture nombre de types de camion

		for (int i = 1; i <= nb_type_camion; i++) // lecture types de camions
		{
			file >> nb_camion[i];
			file >> cap_camion[i];
			file >> cout_fixe_camion[i];
			file >> cout_variable_camion[i];
		}
		for (int i = 0; i <= nb_noeud; i++) // lecture de la matrice des distances
		{
			for (int j = 0; j <= nb_noeud; j++)
			{
				file >> D[i][j];
			}
		}
		for (int i = 1; i <= nb_noeud; i++) // lecture de la demande de chaque noeud
		{
			file >> lecture; // lecture numéro noeud (inutile)
			file >> Q[i];
		}
		file.close();
	}
}

void Instance::afficher()
{
	std::cout << "Nb noeuds : " << nb_noeud << " + depot " << std::endl;
	std::cout << "Types de camions differents : " << nb_type_camion << std::endl;
}

void Instance::GraspHVRP(int iterMax)
{
	/*
	// Création et initialisation de la table de hachage
	int MaxRetry = 100;
	int* hashtable = new int[HashMax];
	for (int i = 0; i < HashMax; i++)
		hashtable[i] = 0;

	int iter = 0;
	BierwithVector vector; //premier vecteur
	vector.Generer_Aleatoirement(*this); // génération aléatoire
	vector.Evaluer(*this);
	vector.Recherche_Locale(*this, 100);
	std::cout << "Cout avant la recherche Globale : ";
	vector.AfficherCout();
	hashtable[vector.CalcHash(*this)] = 1;

	//génération des vecteurs fils :
	default_random_engine generator;
	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distrib(0, n * m - 1);

	while (iter < iterMax)
	{
		BierwithVector t_fils[10]; // 10 fils
		int retry = 0;

		// Obtention des fils
		for (int i = 0; i < 10; i++)
		{
			BierwithVector fils = vector;

			//tirer x et y (x != y) au hasard entre 0 et nb-1
			int x = distrib(generator);
			int y = distrib(generator);
			while (y == x)
				y = distrib(generator);

			//échanger V[x] et V[y]
			fils.V[y] = vector.V[x];
			fils.V[x] = vector.V[y];

			//recherche locale du fils, hash, évaluer
			fils.Recherche_Locale(*this, 50);

			// Si hash pas présent, ajout aux hash et aux 10 fils sinon i--
			if (hashtable[fils.CalcHash(*this)] != 1 && retry < MaxRetry)
			{
				hashtable[fils.CalcHash(*this)] = 1;
				t_fils[i] = fils;
				retry = 0;
			}
			else
			{
				i--;
				retry++;
				// boucle infinie possible
				// éviter la bloucle infinie avec MaxRetry
			}

		}

		// Recherche du meilleur fils
		int jmax = 0;
		for (int j = 1; j < 10; j++)
			if (t_fils[j].cout < t_fils[jmax].cout)
				jmax = j;

		// Réitération sur le meilleur fils
		vector = t_fils[jmax];

		iter++;
	}

	// Affichage du résultat
	vector.AfficherVecteur();
	std::cout << "Résulat final :" << std::endl;
	vector.AfficherCout();

	// aller merci au revoir
	*/
}
