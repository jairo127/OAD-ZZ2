#include "pch.h"
#include "BierwithVector.h"
#include <chrono>
#include "Tuple.h"

BierwithVector::BierwithVector() : nb(0), cout(0)
{
	for (int i = 0; i <= nmax * mmax - 1; i++)
		V[i] = 0;
	for (int i = 0; i <= nmax; i++) {
		for (int j = 0; j <= mmax; j++) {
			St[i][j] = 0;
			Pere[i][j] = 0;
		}
	}
}

void BierwithVector::Generer_Aleatoirement(Instance& inst)
{
	nb = inst.n * inst.m; // taille vecteur
	int mach_r[mmax + 1]; // nb occurence machine restante
	int val[mmax + 1]; // valeurs insérables (1, lim)
	int lim = inst.m; // m machines actives au début
	int cour = 0;
	for (int i = 1; i <= lim; i++) {
		mach_r[i] = inst.n;
		val[i] = i;
	}

	default_random_engine generator;
	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distrib(1, lim); // Génére le i de val[i]

	// Tant qu'il reste une piece à insérer
	while (lim > 0) {
		int i = distrib(generator); // gen aleatoire
		mach_r[val[i]]--; // decr nb occurence machine i
		V[cour] = val[i];
		if (mach_r[val[i]] == 0) // si nb occurence mach i = 0 => suppr machine i
		{
			// décaler à gauche(i+1, lim)
			for (int j = i; j < lim; j++)
				val[j] = val[j + 1];
			val[lim] = -1;
			lim--; // réduire le nb de machines restantes
			// actualiser la distrib ssi il reste des machines (sinon crash)
			if (lim > 0)
				distrib = uniform_int_distribution<int>(1, lim);
		}
		cour++;
	}

}

void BierwithVector::Evaluer(Instance& inst)
{
	const int n = inst.n * inst.m; 
	int np[nmax*mmax +1];
	Tuple mp[nmax*mmax +1];

	for (int i = 1; i <= n; i++) // parcourir le vecteur
	{
		np[i] = 0; //compteur pièce
		mp[i] = Tuple(); //n° de l'opération passée avant sur la machine i
	}
	for (int i = 0; i <= nmax; i++)
		for (int j = 0; j <= mmax; j++)
			St[i][j] = infinite;

	St[0][0] = 0;
	// cout = 0; (fait en auto dans le constructeur)

	for (int i = 1; i < n; i++)
	{
		int j = V[i]; // j = Lambda[i]
		np[j]++;
		int mc = inst.M[j][np[j]]; //
		// ... cas première lecture lambda ?

		if (np[j] > 1)
		{
			int deb_prec = St[j][np[j] - 1];
			int fin_prec = deb_prec + inst.P[j][np[j] - 1];
			if (fin_prec > St[j][np[j]])
				St[j][np[j]] = fin_prec; // maj père ?
		}
		else // premère lecture de la piece ? DE LA BITE OSKOUR ALED SI grzgsdgfsdgfrzgswgfdsw :-)

		{
			int deb_prec = 0;
			int fin_prec = inst.P[j][np[j] - 1];
			if (fin_prec > St[j][np[j]])
				St[j][np[j]] = fin_prec; // maj père ?
		}
		if (mp[mc].i > -1 && mp[mc].j > -1)
		{
			int pc = mp[mc].i;
			int rc = mp[mc].j;
			if (St[pc][rc] + inst.P[pc][rc] > St[j][np[j]]) // ça gueule mais c'est normal... ça explose au final
			{
				St[j][np[j]] = St[pc][rc] + inst.P[pc][rc];
				// Pere[j][np[j]] =  maj père ?
				if (St[j][np[j]] > cout)
					cout = St[j][np[j]];
			}
		}
		mp[mc] = Tuple(j, np[j]);
	}
}

void BierwithVector::AfficherVecteur()
{
	for (int i = 0; i < nb; i++)
		std::cout << V[i] << " ";
	std::cout << std::endl;
	std::cout << "Cout : " << cout << std::endl;
}
