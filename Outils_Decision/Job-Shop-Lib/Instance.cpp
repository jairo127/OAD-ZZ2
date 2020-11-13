#include "pch.h"
#include "Instance.h"
#include "BierwithVector.h"
#include <fstream>
#include <chrono>



// Permet de créer une instance vide. 
//Bien en théorie, mais surface supplém pour les bugs.
//+ init tout à 0  peut rendre silencieux des bugs !
Instance::Instance() : n(0), m(0) 
{
	name = "NAME_NULL"; 
	//for (int i = 0; i < nmax; i++) {
	//	for (int j = 0; j < mmax; j++) {
	//		M[i][j] = -1;
	//		P[i][j] = -1;
	//	}
	//}	
}

void Instance::Lecture(std::string nom_fichier)
{
	ifstream file(nom_fichier.c_str());
	if (!file.fail())
	{
		name = nom_fichier;
		file >> n; // lecture NB pièces
		file >> m; // lecture NB machine
		
		// Parcours des pièces à insérer
		for (int i = 0; i < n; i++)
		{
			// Parcours des machines parcourus 
			for (int j = 0; j < m; j++)
			{
				string lectureM, lectureP;
				file >> lectureM;
				file >> lectureP;
				M[i][j] = atoi(lectureM.c_str()); //pas de +1 ici bordel de cul
				P[i][j] = atoi(lectureP.c_str());
			}
		}
		file.close();
	}
}

void Instance::Afficher()
{
	cout << name << endl;
	cout << "n = " << n << endl;
	cout << "m = " << m << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << M[i][j] << " " << P[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}


//recherche globale : GRASP (Greedy randomized adaptive search procedure

//on choisit une solution et on l'évalue + on applique la recheche locale dessus

//on génére 10 solutions similaires (une seule permutation pour chacune)
//on applique la recherche locale aux 10 solutions
//on s'assure que les solutions similaires sont différentes du père avec un HASH

//on garde la meilleure des solutions générées (même si elle est moins bonne que le père

int Instance::Grasp(int iterMax,int iterLoc)
{
	// Création et initialisation de la table de hachage
	int MaxRetry = 100;
	int * hashtable = new int[HashMax];
	for (int i = 0; i < HashMax; i++)
		hashtable[i] = 0;
	
	int iter = 0;
	BierwithVector vector; //premier vecteur
	vector.Generer_Aleatoirement(*this); // génération aléatoire
	vector.Evaluer(*this);
	vector.Recherche_Locale(*this, 100);
	std::cout << "Cout avant la recherche Globale : ";
	//vector.AfficherCout();
	hashtable[vector.CalcHash(*this)] = 1;

	//génération des vecteurs fils :
	default_random_engine generator;
	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distrib(0, n*m-1);

	while(iter < iterMax)
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
			fils.Recherche_Locale(*this, iterLoc);

			// Si hash pas présent, ajout aux hash et aux 10 fils sinon i--
			if(hashtable[fils.CalcHash(*this)] != 1 && retry < MaxRetry)
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
		// Itération sur le meilleur fils
		vector = t_fils[jmax];
		iter++;
	}

	// Affichage du résultat
	vector.AfficherVecteur();
	std::cout << "Résulat final :" << std::endl;
	vector.AfficherCout();
	return vector.cout;

}