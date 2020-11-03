#include "pch.h"
#include "Label.h"

Label::Label() : cout_total(0)
{
}

Label::Label(Instance inst) : cout_total(0)
{
	for (int i = 1; i <= inst.nb_type_camion; i++)
		nb_camion_restant[i] = inst.nb_camion[i];
}

int Label::compare(Label l)
{
	int h1 = 1; // hyp this < l
	int h2 = 2; // hyp this > l
	int cmp_camion = 1; // 1 si this < l sinon -1 et 0 si incomparable
	// Comparaison des camions restants
	for (int i = 1; i <= nb_camion_restant.size(); i++)
	{
		if (cmp_camion == 1 && nb_camion_restant[i] > l.nb_camion_restant[i])
			cmp_camion = -1;
		if (cmp_camion == -1 && nb_camion_restant[i] < l.nb_camion_restant[i])
			cmp_camion = 0;
	}
	// si this.n < l.n ou l.cout < this.cout
	if (cmp_camion == 1 || l.cout_total < cout_total)
		h1 = 0; // casse hyp 1
	// si this.n > l.n ou l.cout > this.cout
	if (cmp_camion == -1 || l.cout_total > cout_total)
		h2 = 0; // casse hyp 2
	return h1 + h2;
}
