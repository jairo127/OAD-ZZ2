#include "pch.h"
#include "Tournee.h"

Tournee::Tournee() : nb_noeud(0), camion(0), volume(0), cout(0)
{
	for (int i = 0; i < MAX_CLIENT; i++)
		clients[i] = -1;
}

void Tournee::inserer_noeud(int i, int noeud, Instance inst)
{
	int i_prec = 0, i_suiv = 0;
	for (int j = nb_noeud; j > i; j--) // décaler à droite
	{
		clients[j + 1] = clients[j];
	}
	clients[i] = noeud; // insertion noeud

	this->nb_noeud++; // incr nb noeud

	volume += inst.Q[noeud]; // ajout volume noeud

	if (i != 0) // si ce n'est pas le premier noeud visité
		i_prec = i - 1;

	if (i != nb_noeud - 1) // si ce n'est pas le dernier noeud
		i_suiv = i + 1;

	cout += inst.D[i_prec][i] + inst.D[i][i_suiv] - inst.D[i_prec][i_suiv]; // a -3- b -4- c | maj cout 
}
