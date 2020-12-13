#pragma once
#include <random>
#include <chrono>
#include <iostream>
#include <vector>
//#include <iterator>
#include "Constantes.h"
#include "Tournee.h"
#include "Label.h"

class Solution
{
public:
	/// <summary>
	/// Tour Geant décrivant la solution au HVRP
	/// </summary>
	std::vector<int> tour_geant; 

	/// <summary>
	/// Nombre de tournée dans la solution
	/// </summary>
	int nb_tournee;

	/// <summary>
	/// Tournées de la solution de 0 à nb_tournee-1
	/// </summary>
	Tournee tournees[MAX_TOURNEE];

	/// <summary>
	/// Cout total de la solution (CF + CV de chaque tournée)
	/// </summary>
	float cout;

	/// <summary>
	/// Distance totale du tour géant (= cout TSP)
	/// </summary>
	float dist;

	std::vector<Label> labels[MAX_NOEUD];

	/// <summary>
	/// Constructeur par défaut de la solution
	/// </summary>
	Solution();

	/// <summary>
	/// Fonction pour generer un tour geant
	/// </summary>
	void gen_tg_voisin(Instance& inst);

	/// <summary>
	/// Affiche le tour geant
	/// </summary>
	void afficher_tg() const;

	/// <summary>
	/// Fonction pour generer un tour geant
	/// </summary>
	void gen_tg_voisin_random(Instance& inst);

	/// <summary>
	/// Fonction pour generer un tour geant
	/// </summary>
	void gen_tg_random(Instance& inst);

	/// <summary>
	/// Vérifie si la solution est cohérente
	/// </summary>
	/// <param name="inst">Instance de référence</param>
	/// <returns>true si la solution est correcte sinon false</returns>
	bool check_solution(Instance inst);

	//calcul cout d'un tour géant
	float dist_tg(Instance& inst);

	void opt2(Instance& inst, int iter);

	void inserer(Instance& inst);

	void opt3(Instance& inst, int iter);

	void split(Instance& inst);

	void r_locale(Instance& inst);
};