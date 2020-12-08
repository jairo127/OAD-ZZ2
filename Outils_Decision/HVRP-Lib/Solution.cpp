#include "pch.h"
#include "Solution.h"

Solution::Solution() : nb_tournee(0), cout(0)
{
}

// Fonction pour générer un tour géant de manière aléatoire
// Résultat aléatoire
//A CORRIGER NE GEN PAS LE DERNIER SOMMET
void Solution::gen_tg_random(Instance& inst)
{
    // vecteur des noeuds (pour pouvoir les supprimer)
    std::vector<int> sommets;
    for (int i = 1; i <= inst.nb_noeud; i++)
        sommets.push_back(i);


    std::default_random_engine generator;
    // random seed
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    // fixed seed
    //generator.seed(0);

    int index_max_val = inst.nb_noeud - 1;

    // init dépôt
    tour_geant.push_back(0);

    //cassé, ne génère pas le dernier noeud
    for (int i = 1; i <= inst.nb_noeud; i++)
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
    //une seule alloc dyn évite des montagnes de debug
    //liste de bools pour savoir si le sommmet a été traité
    bool* s_parcourus = new bool[inst.nb_noeud+1];
    for (int i = 0; i < inst.nb_noeud+1; i++)
        s_parcourus[i] = false;

    tour_geant.push_back(0); //Ajouter le dépot au tour géant

    //parcourir la liste des sommmets pour établir les plus proches
    int iter = 0; //il faut faire le calcul du voisin 1x par sommet
    while (iter < inst.nb_noeud) 
    {
        int cur = 0;                //Sommet en cours de ttt
        int best_id = -1;          //numero du sommet le plus proche de cur, init à -1
        float best_dist = INF;    //distance du sommet le plus proche de cur, init à INF

        for (int j = 1; j < inst.nb_noeud+1; j++) //pas besoin de tester 0 à chaque fois
        {
            if (!s_parcourus[j] && inst.D[cur][j]< best_dist) //si sommmet non ttt et distance plus basse
            {
                  best_id = j;
                  best_dist = inst.D[cur][j];
            }
        }
        s_parcourus[best_id] = true;    //Marquer le sommet le plus proche comme ttt
        tour_geant.push_back(best_id); //Ajouter le sommet le plus proche au tg
        cur = best_id;
        iter++;                      //increm itercount
    }
    
}

// Fonction pour générer un tour géant
//resultats aléatoires avec peu de variation
void Solution::gen_tg_voisin_random(Instance& inst)
{
    //une seule alloc dyn évite des montagnes de debug
    //liste de bools pour savoir si le sommmet a été traité
    bool* s_parcourus = new bool[inst.nb_noeud + 1];
    for (int i = 0; i < inst.nb_noeud + 1; i++)
    {
        s_parcourus[i] = false;
    }

    tour_geant.push_back(0); //Ajouter le dépot au tour géant

    std::vector<int> id_candidats;       //identifiants des 5 candidats les plus proches
    std::vector<float> dist_candidats;  //distance des 5 candidats les plus proches


    //parcourir la liste des sommmets pour établir les plus proches
    int iter = 0; //il faut faire le calcul du voisin 1x par sommet
    int cur = 0; //Sommet en cours de ttt
    while (iter < inst.nb_noeud)
    {
        int cur = 0; //Sommet en cours de ttt

        for (int j = 1; j < inst.nb_noeud + 1; j++) //pas besoin de tester 0 à chaque fois
        {
            if (!s_parcourus[j]) //on ne regarde que les sommmets non-parcourus
            {
                if (dist_candidats.empty()) //cas où le vecteur est vide
                {
                    id_candidats.push_back(j);
                    dist_candidats.push_back(inst.D[cur][j]);
                }
                else //vecteurs pas vides
                {
                    //parcourir le vecteur de candidats en partant du back() avec la valeur la plus grande
                    for (auto k = dist_candidats.size() - 1; k >= 0; k--)
                    {
                        if (dist_candidats[k] > inst.D[cur][j])
                        {


                        }
                        else if (dist_candidats.size() < 5) //il manque des candidats
                        {
                            id_candidats.push_back(j);
                            dist_candidats.push_back(inst.D[cur][j]);
                        }
                        else



                            if (k = !dist_candidats.size() - 1)
                            {
                                id_candidats.insert(id_candidats.begin() + k + 1, j);
                                dist_candidats.insert(dist_candidats.begin() + k + 1, inst.D[cur][j]);

                                if (dist_candidats.size() > 5)
                                {
                                    id_candidats.pop_back();
                                    dist_candidats.pop_back();
                                }
                            }
                        break;
                    }
                    //else
                    {

                    }

                }

            }
            //s_parcourus[best_id] = true;    //Marquer le sommet le plus proche comme ttt
            //tour_geant.push_back(best_id); //Ajouter le sommet le plus proche au tg
            //cur = best_id;
            iter++;                      //increm itercount
        }


        //std::default_random_engine generator;
        //// random seed
        //generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        //// fixed seed
        ////generator.seed(0);
        //std::uniform_int_distribution<int> distrib(0, 5);



    }
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
