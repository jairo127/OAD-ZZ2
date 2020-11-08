#include "pch.h"
#include "BierwithVector.h"
#include <chrono>
//#include <iostream>

BierwithVector::BierwithVector() : nb(0), cout(0)
{
	for (int i = 0; i <= nmax * mmax - 1; i++)
		V[i] = -1; // si c'est moins 1, il y a un pb

	for (int i = 0; i < nmax; i++) {
		for (int j = 0; j < mmax; j++) {
			St[i][j] = 0;
			Pere[i][j] = Tuple();
		}
	}
}

void BierwithVector::Generer_Aleatoirement(Instance& inst)
{
	nb = inst.n * inst.m;	// taille vecteur
	int mach_r[mmax];		// nb occurence machine restante
	int val[mmax];			// valeurs insérables (1, lim)

	int lim = inst.m-1;		// m machines actives au début

	int cour = 0;			//index d'insertion dans le vecteur.

	for (int i = 0 ; i < inst.m; i++) {
		mach_r[i] = inst.n;
		val[i] = i;
	}

	//nombre non fixe de valeurs non générées......

	default_random_engine generator;

	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	// fixed seed
	//generator.seed(0);

	uniform_int_distribution<int> distrib(0, lim); // Génére le i de val[i]

	// Tant qu'il reste une piece à insérer
	while (lim >= 0) {

		int i = distrib(generator); // gen aleatoire

		//attention warning visual ici. je pense qu'il est attardé mais warning qd même
		mach_r[val[i]]--; // decr nb occurence machine i
		V[cour] = val[i];

		if (mach_r[val[i]] == 0) // si nb occurence mach i = 0 => suppr machine i
		{
			// décaler à gauche(i+1, lim)
			for (int j = i; j < lim; j++)
				val[j] = val[j + 1];
			//val[lim] = -666; //pourquoi ?  inutile

			lim--; // réduire le nb de machines restantes

			// actualiser la distrib si il reste des machines (sinon crash)
			if (lim >= 0)
				distrib = uniform_int_distribution<int>(0, lim);
		}

		cour++;
	}

}

void BierwithVector::Evaluer(Instance& inst)
{
	int N = inst.n * inst.m; // déjà stocké dans le vecteur
	if (N == nb) std::cout << "N est redondant " << std::endl;
	cout = 0;
	int np[nmax]; //compteur d'appartion du job
	Tuple mp[nmax * mmax]; //initialisé à -1 -1 : opération précédente (j = identifient job ; i = numéro opération pour job j)

	for (int i = 0; i < nmax; i++) // De 1 à N inclus!
	{
		np[i] = -1; //compteur d'appartion du job à 0
		mp[i] = Tuple(); //n° de l'opération passée avant sur la machine i
	}

	for (int i = 0; i < nmax; i++)
		for (int j = 0; j < mmax; j++)
			St[i][j] = -infinite; // mise à 0 des st

	St[0][0] = 0;

	//////////////////////////////////////
	//main loop for eval
	//LIMITES : plages d'index autorisées 
	//instance.M :	[0][0]	-> [nmax-1][mmax-1] //machines utilisées pour les op
	//instance.P :	[0][0]	-> [nmax-1][mmax-1] //durées des op
	//V :			[0]		-> [nb-1] == [nmax*mmax -1]
	//St :			[0][0]	-> [nmax-1][mmax-1]
	//Pere :		[0][0]	-> [nmax-1][mmax-1]
	//np :			[0]		-> [nb-1]
	//mp :			[0]		-> [nb-1]

	for (int i = 0; i < N; i++)
	{

		int job = V[i]; // j = Lambda[i] = id du job traité dans le vecteur

		np[job]++; //increm compteur opé pour job 

		if (np[job] == 5)
			int aa = 4;
		//err : np populé avec les valeurs trop élevées
		int machine_courante = inst.M[job][np[job]]; //machine utilisée par le job

		St[job][np[job]] = 0;

		//partie conjonctive du graph
		if (np[job] > 0) // si ce n'est pas la prem op du job
		{
			int deb_prec = St[job][np[job] - 1]; // St de opé préc du job //ok, il y aura tj une op préc
			int fin_prec = deb_prec + inst.P[job][np[job]-1]; //date fin opé précédente

			if (fin_prec > St[job][np[job]]) // on regarde si la fin de l'opé prec est sup au ST de ce job
			{
				St[job][np[job]] = fin_prec; // on corrige le st pour ce job
				Pere[job][np[job]] = Tuple(job, np[job] - 1);

				if (np[job] == inst.m - 1) //si c'est la dernière opération du job
				{
					if (St[job][np[job]] + inst.P[job][np[job]] > cout)
					{
						cout = St[job][np[job]] + inst.P[job][np[job]];
						Pere[job][inst.m] = Tuple(job, inst.m - 1);
						Pere[inst.n + 1][0] = Tuple(job, inst.m);
					}
				}
			}
		}

		//partie disjonctive
		//pas besoin de 2 tests : On affectera jamais que une des valeurs
		//if (mp[machine_courante].i != -1 && mp[machine_courante].j != -1) 
		if (mp[machine_courante].i != -1)
		{
			Tuple t_cour = mp[machine_courante];

			if (St[t_cour.j][t_cour.i] + inst.P[t_cour.j][t_cour.i] > St[job][np[job]])
			{
				St[job][np[job]] = St[t_cour.j][t_cour.i] + inst.P[t_cour.j][t_cour.i];
				Pere[job][np[job]] = t_cour;

				if (np[job] == inst.m - 1)
				{
					if (St[job][np[job]] + inst.P[job][np[job]] > cout)
					{
						cout = St[job][np[job]] + inst.P[job][np[job]];
						Pere[inst.n][inst.m] = t_cour;
					}
				}
			}
		}
		mp[machine_courante] = Tuple(job, np[job]);
	}
}

void BierwithVector::Recherche_Locale(Instance& inst, int iter_max)
{
	int iter = 0;
	Evaluer(inst);
	std::cout << "cout pre-recherche locale = " << cout << std::endl;

	Tuple last = Pere[inst.m + 1][0]; // dernière ope tout à droite (fictive)
	Tuple cour = Pere[last.j][last.i]; //dernière opération réelle

	//while (iter <= iter_max && (cour.i != -1 && cour.j != -1))
	while ((iter <= iter_max) && (last.j != -1) && (Pere[cour.j][cour.i].i != -1))
	{
		// Copie du vecteur actuel
		BierwithVector v_prim;
		std::copy(std::begin(V), std::end(V), v_prim.V);
		v_prim.nb = nb;
		v_prim.cout = infinite;

		// Vérifier si arc disjonctif -> Job prédécesseur != job successeur
		if (last.j != cour.j)
		{
			std::cout << "IF Modif" << std::endl;
			
			// Recherche des index à permuter
			int i_cour = v_prim.Recherche(cour.j, cour.i, inst.n * inst.m);
			int i_last = v_prim.Recherche(last.j, last.i, inst.n * inst.m);
			std::cout << "i_cour = " << i_cour << ", i_last = " << i_last << std::endl;

			// Permutation des index
			int tmp = v_prim.V[i_cour];
			v_prim.V[i_cour] = v_prim.V[i_last];
			v_prim.V[i_last] = tmp;

			// Réévaluation
			v_prim.Evaluer(inst);
			v_prim.AfficherVecteur();
			v_prim.AfficherCout();
		}
		if(v_prim.cout < cout)
		{
			std::cout << "IF Better" << std::endl;
			*this = v_prim; //passage en hardcopy
			std::cout << "maj" << std::endl;
			//std::copy(std::begin(v_prim.V), std::end(v_prim.V), V);
			
			last = v_prim.Pere[inst.n + 1][0]; // dernière ope tout à droite (fictive)
			cour = v_prim.Pere[last.j][last.i]; //dernière opération réelle
		}
		else
		{
			std::cout << "ELSE Better" << std::endl;
			last = cour;
			cour = Pere[cour.j][cour.i]; // et on descend, yeaaaaah
		}
		iter++;
		//std::cout << "iterating"<< std::endl;
	}
	std::cout << "cout post-recherche locale = " << cout<< std::endl;
}

int BierwithVector::Recherche(int j, int i, int N)
{
	int cpt = 0; // compteur
	int index = 0;
	for (int k = 0; k < N; k++)
	{
		if (V[k] == j)
		{
			if (cpt == i)
			{
				index = k;
				break;
			}
			else
			{
				cpt++;
			}
		}
	}
	return index;
}

void BierwithVector::AfficherVecteur()
{
	for (int i = 0; i < nb; i++)
		std::cout << V[i] << " ";
	std::cout << std::endl;
	
}

void BierwithVector::AfficherCout()
{
	std::cout << "Cout : " << cout << std::endl;
}