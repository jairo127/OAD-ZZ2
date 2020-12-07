#include "pch.h"
#include "Solution.h"

Solution::Solution() : nb_tournee(0), cout(0)
{
}

// Fonction pour générer un tour géant de manière aléatoire
// Résultat aléatoire
void Solution::gen_tg_random(Instance& inst)
{
    // vecteur des noeuds (pour pouvoir les supprimer)
    std::vector<int> sommets;
    for (int i = 1; i < inst.nb_noeud; i++)
        sommets.push_back(i);


    std::default_random_engine generator;
    // random seed
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    // fixed seed
    //generator.seed(0);

    int index_max_val = inst.nb_noeud - 2;

    // init dépôt
    tour_geant.push_back(0);

    //sommets.erase(sommets.begin());

    for (int i = 1; i < inst.nb_noeud; i++)
    {
        std::uniform_int_distribution<int> distrib(0, index_max_val);
        // obtenir la position tirée  
        int x = distrib(generator);
        int sommet = sommets[x];
        sommets.erase(sommets.begin() + x);
        index_max_val--;
        // ajouter le sommet au tour géant
        tour_geant.push_back(sommet);
    }
}

// Fonction pour générer un tour géant
//resultat doit être tj le même
void Solution::gen_tg_voisin(Instance& inst)
{
    std::vector<bool> sommets;
    for(int i = 0; i < inst.nb_noeud; i++)
        sommets.push_back(false);

    sommets[0] = true;

    //for(int i = 0; int i)



}

// Fonction pour générer un tour géant
//resultat aléatoires avec peu de variations
void Solution::gen_tg_voisin_random(Instance& inst)
{
    //std::default_random_engine generator;
    //// random seed
    //generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    //// fixed seed
    ////generator.seed(0);
    //std::uniform_int_distribution<int> distrib(0, 5);



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

/// <summary>
/// Affiche le tour geant
/// </summary>
void Solution::afficher_tg()  const
{
    if (!tour_geant.empty())
    {
        for (auto elem : tour_geant)
        {
            std::cout << elem << "  ";
        }
        std::cout << std::endl;
    }
}
