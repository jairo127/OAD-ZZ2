#include "pch.h"
#include "Instance.h"
#include <fstream>
#include <functional>
#include <vector>
#include "Solution.h"

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
	
	// Création et initialisation de la table de hachage
	int MaxRetry = 100;
	unsigned int HashMax = 9999999;
	int* hashtable = new int[HashMax];
	for (int i = 0; i < HashMax; i++)
		hashtable[i] = 0;

	int iter = 0;
	Solution sol; //premiere solution
	sol.gen_tg_voisin_random(*this);
	sol.r_locale(*this, 10000);
	std::cout << "Cout avant la recherche locale : " << sol.dist_tg(*this) << std::endl;
	int hash = sol.hash_solution(*this, HashMax);
	//std::cout << "HASH : " << hash << std::endl;
	hashtable[hash] = 1;

	//génération des vecteurs fils :
	std::default_random_engine generator;
	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distrib(1, nb_noeud); // risque de plantage ici

	while (iter < iterMax)
	{
		Solution t_fils[10]; // 10 fils
		int retry = 0;

		// Obtention des fils
		for (int i = 0; i < 10; i++)
		{
			Solution fils = sol;

			//tirer x et y (x != y) au hasard entre 0 et nb-1
			int x = distrib(generator);
			int y = distrib(generator);

			while (y == x)
				y = distrib(generator);

			//échanger V[x] et V[y]
			fils.tour_geant[y] = sol.tour_geant[x];
			fils.tour_geant[x] = sol.tour_geant[y];

			//recherche locale du fils, hash, évaluer
			fils.r_locale(*this, 50);
			
			hash = fils.hash_solution(*this, HashMax);
			//std::cout << "HASH : " << hash << std::endl;
			// Si hash pas présent, ajout aux hash et aux 10 fils sinon i--
			if (hashtable[hash] != 1 && retry < MaxRetry)
			{
				hashtable[hash] = 1;
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
			if (t_fils[j].dist_tg(*this) < t_fils[jmax].dist_tg(*this))
				jmax = j;

		// Réitération sur le meilleur fils
		sol = t_fils[jmax];

		iter++;
	}

	// Affichage du résultat
	sol.afficher_tg();
	std::cout << "Résulat final : " << sol.dist_tg(*this) << std::endl;
}
