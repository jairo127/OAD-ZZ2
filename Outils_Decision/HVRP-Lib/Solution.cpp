#include "pch.h"
#include "Solution.h"

Solution::Solution() : nb_tournee(0), cout(0), dist(0)
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
    tour_geant.push_back(0);
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
    tour_geant.push_back(0); //Ajouter le dépot au tour géant
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
        id_candidats.clear();
        dist_candidats.clear();

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
                    for (int k = (int(dist_candidats.size())-1); k >= 0; k--) //la conv en int est obligatoire
                    {
                        if (dist_candidats[k] > inst.D[cur][j]) //tester si plus petit. si oui itérer.
                        {
                            continue; //decrem K. la val sera insérée
                        }
                        else if (dist_candidats.size() < 5) //il manque des candidats; ajouter
                        {
                            id_candidats.push_back(j);
                            dist_candidats.push_back(inst.D[cur][j]);
                        }
                        else //il faut break car dist_candidats[k] < inst.D[cur][j] && dist_candidats.size() = 5
                        { //il faut tester si on écrit. 
                            if (k<4) //insérer en position k+1 et break
                            {
                                id_candidats.insert(id_candidats.begin() + k + 1, j);
                                dist_candidats.insert(dist_candidats.begin() + k + 1, inst.D[cur][j]);
                                id_candidats.pop_back();
                                dist_candidats.pop_back();
                                break;
                            }
                            else //break sans insert
                            {
                                break;
                            }  
                        }
                    }
                }
            }
        }
        //fin boucle qui itère sur les ddestinations possibles. 
        //Les 5 candidats les plus proches sont dans les vecteurs :

        std::default_random_engine generator;
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> distrib(0, int(id_candidats.size())-1 );
        int x = distrib(generator);

        s_parcourus[id_candidats[x]] = true;    //Marquer le sommet le plus proche comme ttt
        tour_geant.push_back(id_candidats[x]); //Ajouter le sommet le plus proche au tg
        cur = id_candidats[x];

        iter++; //increm itercount, fin ttt d'un sommet
    }
    tour_geant.push_back(0); //Ajouter le dépot au tour géant
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


void Solution::afficher_tg()  const
{
    if (!tour_geant.empty())
    {
        for (auto elem : tour_geant)
        {
            std::cout << elem << "  ";
        }
    }
}

void Solution::opt2(Instance& inst, int itermax)
{
    if (dist == 0) //si la distance n'est pas calculée
    {
        dist = dist_tg(inst);
    }

    //init du générateur aléatoire
    std::default_random_engine generator;

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(1, int(tour_geant.size()) - 2);

    float newdist = dist + 1;
    int loop = 0; // je sais pas si le prof veut ça

    while (loop < itermax)
    {
        int x = distrib(generator);
        int y = distrib(generator);

        int tries = 0;
        while (y >=x-1 && y<= x+1 && tries <20) //éviter de prendre 2 points n et n+1
        {
            int y = distrib(generator);
            tries++; //évite les boucles infinies pour les petits tg
        }
       
        float newdist = dist //la magie se produit quand la coloration synthaxique jette l'éponge :)
                        - inst.D[tour_geant[x - 1]][tour_geant[x]] 
                        - inst.D[tour_geant[x]][tour_geant[x + 1]]
                        - inst.D[tour_geant[y - 1]][tour_geant[y]]
                        - inst.D[tour_geant[y]][tour_geant[y + 1]]
                        + inst.D[tour_geant[x - 1]][tour_geant[y]]
                        + inst.D[tour_geant[y - 1]][tour_geant[x]]
                        + inst.D[tour_geant[x]][tour_geant[y + 1]]
                        + inst.D[tour_geant[y]][tour_geant[x + 1]];

        if (newdist < dist) //évite la régresssion du score
        {
            //échange :
            int saving = tour_geant[x];
            tour_geant[x] = tour_geant[y];
            tour_geant[y] = saving;
            dist = newdist;
            break;
        }
    }
}

void Solution::inserer(Instance& inst)
{
    //trouver le sommet avec le détour maximal
    //index = 11; //placeholder

    //tour_geant.erase(vec.begin() + index);

}


void Solution::opt3(Instance& inst, int itermax) //pas demandé dans le TP
{
    ////init du générateur aléatoire
    //std::default_random_engine generator;
    //generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    //std::uniform_int_distribution<int> distrib(1, int(tour_geant.size()) - 2);

    //int x = distrib(generator);
    //int y = distrib(generator);
    //int z = distrib(generator);

    //int iter = 0;
    //while (y >= x - 1 && y <= x + 1 && iter < 20) //éviter de prendre 2 points n et n+1
    //{
    //    int y = distrib(generator);
    //    iter++; //évite les boucles infinies pour les petits tg
    //}

    //iter = 0;
    //while (((z >= x - 1 && z <= x + 1) || (z >= y - 1 && z <= y + 1)) && iter < 40) //éviter de prendre 2 points n et n+1
    //{
    //    int z = distrib(generator);
    //    iter++; //évite les boucles infinies pour les petits tg
    //}

    //int saving = tour_geant[x];
    //tour_geant[x] = tour_geant[y];
    //tour_geant[y] = tour_geant[z];
    //tour_geant[z] = saving;

}

float Solution::dist_tg(Instance& inst)
{
    float res = 0;
    for (int i= 0 ; i < tour_geant.size()-1 ; i++)
    {
        res += inst.D[tour_geant[i]][tour_geant[i + 1]];  
    }
    return res;
}


void Solution::split(Instance& inst)
{

}