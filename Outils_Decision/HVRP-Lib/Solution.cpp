#include "pch.h"
#include "Solution.h"

Solution::Solution() : nb_tournee(0), cout(0)
{
}

bool Solution::check_solution(Instance inst)
{
    bool ret = true;
    int v_noeuds[MAX_NOEUD]; // nb de fois apparition noeud i
    int v_camions[MAX_TYPE+1]; // nb d'utilisation camion type i

    // init v_noeuds et v_camions
    for (int i = 1; i <= inst.nb_noeud; i++)
        v_noeuds[i] = 0;
    for (int i = 1; i <= inst.nb_type_camion; i++)
        v_camions[i] = 0;


    for (int i = 0; i < nb_tournee; i++)
    {
        int camion = tournees[i].camion;
        int volume = tournees[i].volume;
        // verif nombre de camions
        v_camions[camion] += 1;
        // verif volume camion
        if (tournees[i].volume > inst.cap_camion[tournees[i].camion])
            ret = false;
        for (int j = 0; j < tournees[i].nb_noeud; j++)
            v_noeuds[tournees[i].clients[j]]++;
    }
    // verif si on dépasse pas le nombre de camion d'un type
    // on a le droit d'en utiliser moins que le nb dispo
    for (int i = 1; i <= inst.nb_type_camion; i++)
        if (v_camions[i] > inst.nb_camion[i])
            ret = false;
    // verif si on a bien un et un seul exemplaire de chaque noeud
    for (int i = 1; i <= inst.nb_noeud; i++)
        if (v_noeuds[i] != 1)
            ret = false;
    return ret;
}
