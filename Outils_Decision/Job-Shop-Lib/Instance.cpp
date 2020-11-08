#include "pch.h"
#include "Instance.h"
#include <fstream>



// Permet de cr�er une instance vide. 
//Bien en th�orie, mais surface suppl�m pour les bugs.
//+ init tout � 0  peut rendre silencieux des bugs !
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
		file >> n; // lecture NB pi�ces
		file >> m; // lecture NB machine
		
		// Parcours des pi�ces � ins�rer
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


//void 
//recherche globale : GRASP (Greedy randomized adaptive search procedure

//on choisit une solution et on l'�value + on applique la recheche locale dessus

//on g�n�re 10 solutions similaires (une seule permutation pour chacune)
//on applique la recherche locale aux 10 solutions
//on s'assure que les solutions similaires sont diff�rentes du p�re avec un HASH

//on garde la meilleure des solutions g�n�r�es (m�me si elle est moins bonne que le p�re