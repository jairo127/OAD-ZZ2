#include "pch.h"
#include "Label.h"

Label::Label() : cout_total(0), sommet_pere(-1), label_pere(-1)
{
}

Label::Label(Instance & inst) : cout_total(0), sommet_pere(-1), label_pere(-1)
{
	nb_camion_restant.push_back(0);
	for (int i = 1; i <= inst.nb_type_camion; i++)
		nb_camion_restant.push_back(inst.nb_camion[i]);
}

int Label::compare(Label l)
{
	// retourne 1 si gauche meilleur, 0 si incomparable et -1 si droit meilleur -2 si labels identiques 

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
}
