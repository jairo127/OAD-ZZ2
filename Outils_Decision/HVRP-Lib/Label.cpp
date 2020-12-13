#include "pch.h"
#include "Label.h"

Label::Label() : cout_total(0), sommet_pere(-1), label_pere(-1)
{
}

Label::Label(Instance inst) : cout_total(0)
{
	for (int i = 1; i <= inst.nb_type_camion; i++)
		nb_camion_restant[i] = inst.nb_camion[i];
}

int Label::compare(Label l)
{
	// retourne 1 si gauche meilleur, 0 si incomparable et -1 si droit meilleur -2 si labels identiques 

	// label gauche (= celui qui apelle la méthode) = g , label droit = d
	//comaration des labels : couts et camion restants :
	// CAMIONS RESTANTS : 
	// - identiques -> cmp_camion = 0 (la verif se joue sur le cout total)

	// - identique sauf g[i] < d[i] -> cmp_camion = 1 (gauche est plus petit droit pour les camions restants)
	// - identique sauf g[i] < d[i] et g[j] > d[i] -> incomparables !!!
	//si meme  nombre de camions restants : compa cout
	

	bool left = false; //passent true si un des labels est meilleur 
	bool right = false;

	for (int i = 1; i < nb_camion_restant.size(); i++)
	{
		if (nb_camion_restant[i] > l.nb_camion_restant[i])
		{
			left = true;
		}
		if (nb_camion_restant[i] < l.nb_camion_restant[i])
		{
			right = true;
		}
	}

	if (left && right) //incomparables
	{
		return 0;
	}

	if (left)
	{
		return 1;
	}

	if (right)
	{
		return -1;
	}

	if (!left && !right) //peuvent êtres identiques
	{
		if (cout_total < l.cout_total)
		{
			return 1;
		}
		else if(cout_total > l.cout_total)
		{
			return -1;
		}
		else //labels identiques
		{
			return -2;
		}

	}


	/*
	int h1 = 1; // hyp this < l
	int h2 = 2; // hyp this > l

	int cmp_camion = 1; // 1 si this < l sinon -1 et 0 si incomparable
	bool identique = false;
	// Comparaison des camions restants
	for (int i = 1; i < nb_camion_restant.size(); i++)
	{
		if (cmp_camion == 1 && nb_camion_restant[i] > l.nb_camion_restant[i])
			cmp_camion = -1;

		if (cmp_camion == -1 || nb_camion_restant[i] < l.nb_camion_restant[i])
			cmp_camion = 0;
	}

	if (nb_camion_restant == l.nb_camion_restant)
		identique = true;

	// si this.n < l.n ou l.cout < this.cout
	if (cmp_camion == -1 || l.cout_total < cout_total || cmp_camion == 0)
		h1 = 0; // casse hyp 1

	// si this.n > l.n ou l.cout > this.cout
	if ((cmp_camion == 1 && !identique) || l.cout_total > cout_total || cmp_camion == 0)
		h2 = 0; // casse hyp 2

	return h1 + h2;
	*/
}
