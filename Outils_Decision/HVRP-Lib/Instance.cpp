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
	std::cout << "Nb noeuds : " << nb_noeud << " + dépot " << std::endl;
	std::cout << "Types de camions différents : " << nb_type_camion << std::endl;
}
