#include "pch.h"
#include "Solution.h"

bool Solution::check_solution(Instance inst)
{
    bool ret = true;
    bool v_noeuds[MAX_NOEUD];
    int v_camions[MAX_TYPE+1];
    for (int i = 1; i <= inst.nb_noeud; i++)
        v_noeuds[i] = false;
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

    }
    return ret;
}
