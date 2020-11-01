#include "pch.h"
#include "BierwithVector.h"
#include <chrono>

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
	nb = inst.n * inst.m; // taille vecteur
	int mach_r[mmax + 1]; // nb occurence machine restante
	int val[mmax + 1]; // valeurs ins�rables (1, lim)
	int lim = inst.m; // m machines actives au d�but
	int cour = 0;
	for (int i = 1; i <= lim; i++) {
		mach_r[i] = inst.n;
		val[i] = i;
	}

	default_random_engine generator;
	// random seed
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> distrib(1, lim); // G�n�re le i de val[i]

	// Tant qu'il reste une piece � ins�rer
	while (lim > 0) {
		int i = distrib(generator); // gen aleatoire
		mach_r[val[i]]--; // decr nb occurence machine i
		V[cour] = val[i];
		if (mach_r[val[i]] == 0) // si nb occurence mach i = 0 => suppr machine i
		{
			// d�caler � gauche(i+1, lim)
			for (int j = i; j < lim; j++)
				val[j] = val[j + 1];
			val[lim] = -1;
			lim--; // r�duire le nb de machines restantes
			// actualiser la distrib ssi il reste des machines (sinon crash)
			if (lim > 0)
				distrib = uniform_int_distribution<int>(1, lim);
		}
		cour++;
	}

}

void BierwithVector::Evaluer(Instance& inst)
{
	int N = inst.n * inst.m;
	int np[nmax]; //compteur d'appartion du job
	Tuple mp[nmax * mmax]; //initialis� � -1 -1 : op�ration pr�c�dente (j = identifient job ; i = num�ro op�ration pour job j)

	for (int i = 0; i < nmax; i++) // De 1 � N inclus!
	{
		np[i] = 0; //compteur d'appartion du job � 0
		mp[i] = Tuple(); //n� de l'op�ration pass�e avant sur la machine i
	}

	for (int i = 0; i < nmax; i++)
		for (int j = 0; j < mmax; j++)
			St[i][j] = -infinite; // mise � 0 des st

	St[0][0] = 0;

	//////////////////////////////////////<<init>>
	//main loop for eval
	for (int i = 0; i < N; i++)
	{
		int job = V[i]; // j = Lambda[i] = id du job trait� dans le vecteur
		np[job]++; //increm compteur op� pour job 
		int machine_courante = inst.M[job][np[job]]; //machine utilis�e par le job

		St[job][np[job]] = 0;

		//partie conjonctive du graph
		if (np[job] > 1) // si ce n'est pas la prem op du job
		{
			int deb_prec = St[job][np[job] - 1]; // St de op� pr�c du job
			int fin_prec = deb_prec + inst.P[job][np[job]-1]; //date fin op� pr�c�dente

			if (fin_prec > St[job][np[job]])
			{
				St[job][np[job]] = fin_prec;
				Pere[job][np[job]] = Tuple(job, np[job] - 1);

				if (np[job] == inst.m) //si c'est la derni�re op�ration du job
				{
					if (St[job][np[job]] + inst.P[job][np[job]] > cout)
					{
						cout = St[job][np[job]] + inst.P[job][np[job]];
						Pere[inst.n][inst.m] = Tuple(job, inst.m - 1);
					}
				}
			}
		}

		//partie disjonctive
		if (mp[machine_courante].i != -1 && mp[machine_courante].j != -1) // r��crire pour un tuple
		{
			Tuple t_cour = mp[machine_courante];

			if (St[t_cour.j][t_cour.i] + inst.P[t_cour.j][t_cour.i] > St[job][np[job]])
			{
				St[job][np[job]] = St[t_cour.j][t_cour.i] + inst.P[t_cour.j][t_cour.i];
				Pere[job][np[job]] = t_cour;

				if (np[job] == inst.m)
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
	Tuple last = Pere[inst.m + 1][0]; // derni�re ope tout � droite (fictive)
	Tuple cour = Pere[last.j][last.i]; //derni�re op�ration r�elle

	//while (iter <= iter_max && (cour.i != -1 && cour.j != -1))
	while ((iter <= iter_max) && (last.j != -1) && (Pere[cour.j][cour.i].i != -1))
	{
		BierwithVector v_prim = *this; //copie du vecteur actuel
		//v�rifier si arc disjonctif == Job pr�d�cesseur != job successeur
		if (last.j != cour.j)
		{
			int cpt = 0; // compteur
			int i_cour = 0, i_last = 0;
			for (int i = 0; i < inst.n*inst.m; i++) // find job cour.j et iter cour.i
			{
				if (v_prim.V[i] == cour.j)
				{
					if (cpt == cour.i)
						i_cour = i;
					else
						cpt++;
				}
			}
			for (int i = 0; i < inst.n*inst.m; i++) // find job last.j et iter last.i
			{
				if (v_prim.V[i] == last.j)
				{
					if (cpt == last.i)
						i_last = i;
					else
						cpt++;
				}
			}

			int tmp = v_prim.V[i_cour];
			v_prim.V[i_cour] = v_prim.V[i_last];
			v_prim.V[i_last] = tmp;
			// permutation cases c1 et c2 [cour et last]
			v_prim.Evaluer(inst);
		}
		if(v_prim.cout > cout)
		{
			*this = v_prim; //passage en hardcopy
			//std::copy(std::begin(v_prim.V), std::end(v_prim.V), V);
			
			last = v_prim.Pere[inst.n + 1][0]; // derni�re ope tout � droite (fictive)
			cour = v_prim.Pere[last.j][last.i]; //derni�re op�ration r�elle
		}
		else
		{

			last = cour;
			cour = Pere[cour.j][cour.i]; // et on descend, yeaaaaah
		}
		//std::cout << "iterating"<< std::endl;
	}
	std::cout << "cout post-recherche locale = " << cout<< std::endl;
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