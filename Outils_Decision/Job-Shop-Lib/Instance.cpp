#include "pch.h"
#include "Instance.h"
#include <fstream>



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
