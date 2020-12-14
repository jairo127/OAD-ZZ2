#include "pch.h"
#include "Solution.h"

Solution::Solution() : nb_tournee(0), cout(0), dist(0)
{
}

// Fonction pour g�n�rer un tour g�ant de mani�re al�atoire
// R�sultat al�atoire
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

    // init d�p�t
    tour_geant.push_back(0);

    //cass�, ne g�n�re pas le dernier noeud
    for (int i = 1; i <= inst.nb_noeud; i++)
    {
        std::uniform_int_distribution<int> distrib(0, index_max_val);
        // obtenir la position tir�e  
        int x = distrib(generator);

        int sommet = sommets[x];
        sommets.erase(sommets.begin() + x);
        index_max_val--;
        // ajouter le sommet au tour g�ant
        tour_geant.push_back(sommet);
    }
    tour_geant.push_back(0);
}


// Fonction pour g�n�rer un tour g�ant
//resultat doit �tre tj le m�me
void Solution::gen_tg_voisin(Instance& inst)
{
    //une seule alloc dyn �vite des montagnes de debug
    //liste de bools pour savoir si le sommmet a �t� trait�
    bool* s_parcourus = new bool[inst.nb_noeud+1];
    for (int i = 0; i < inst.nb_noeud+1; i++)
        s_parcourus[i] = false;

    tour_geant.push_back(0); //Ajouter le d�pot au tour g�ant

    //parcourir la liste des sommmets pour �tablir les plus proches
    int iter = 0; //il faut faire le calcul du voisin 1x par sommet
    while (iter < inst.nb_noeud) 
    {
        int cur = 0;                //Sommet en cours de ttt
        int best_id = -1;          //numero du sommet le plus proche de cur, init � -1
        float best_dist = INF;    //distance du sommet le plus proche de cur, init � INF

        for (int j = 1; j < inst.nb_noeud+1; j++) //pas besoin de tester 0 � chaque fois
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
    tour_geant.push_back(0); //Ajouter le d�pot au tour g�ant
}

// Fonction pour g�n�rer un tour g�ant
//resultats al�atoires avec peu de variation
void Solution::gen_tg_voisin_random(Instance& inst)
{
    //une seule alloc dyn �vite des montagnes de debug
    //liste de bools pour savoir si le sommmet a �t� trait�
    bool* s_parcourus = new bool[inst.nb_noeud + 1];
    for (int i = 0; i < inst.nb_noeud + 1; i++)
    {
        s_parcourus[i] = false;
    }

    tour_geant.push_back(0); //Ajouter le d�pot au tour g�ant

    std::vector<int> id_candidats;       //identifiants des 5 candidats les plus proches
    std::vector<float> dist_candidats;  //distance des 5 candidats les plus proches


    //parcourir la liste des sommmets pour �tablir les plus proches
    int iter = 0; //il faut faire le calcul du voisin 1x par sommet
    int cur = 0; //Sommet en cours de ttt
    while (iter < inst.nb_noeud)
    {
        id_candidats.clear();
        dist_candidats.clear();

        for (int j = 1; j < inst.nb_noeud + 1; j++) //pas besoin de tester 0 � chaque fois
        {
            if (!s_parcourus[j]) //on ne regarde que les sommmets non-parcourus
            {
                if (dist_candidats.empty()) //cas o� le vecteur est vide
                {
                    id_candidats.push_back(j);
                    dist_candidats.push_back(inst.D[cur][j]);
                }
                else //vecteurs pas vides
                {
                    //parcourir le vecteur de candidats en partant du back() avec la valeur la plus grande
                    for (int k = (int(dist_candidats.size())-1); k >= 0; k--) //la conv en int est obligatoire
                    {
                        if (dist_candidats[k] > inst.D[cur][j]) //tester si plus petit. si oui it�rer.
                        {
                            continue; //decrem K. la val sera ins�r�e
                        }
                        else if (dist_candidats.size() < 5) //il manque des candidats; ajouter
                        {
                            id_candidats.push_back(j);
                            dist_candidats.push_back(inst.D[cur][j]);
                        }
                        else //il faut break car dist_candidats[k] < inst.D[cur][j] && dist_candidats.size() = 5
                        { //il faut tester si on �crit. 
                            if (k<4) //ins�rer en position k+1 et break
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
        //fin boucle qui it�re sur les ddestinations possibles. 
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
    tour_geant.push_back(0); //Ajouter le d�pot au tour g�ant
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
    // verif si on d�passe pas le nombre de camion d'un type
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
    if (dist == 0) //si la distance n'est pas calcul�e
    {
        dist = dist_tg(inst);
    }

    //init du generateur al�atoire
    std::default_random_engine generator;

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(1, int(tour_geant.size()) - 2);

    float newdist = dist + 1;
    int loop = 0; 

    while (loop < itermax)
    {
        int x = distrib(generator);
        int y = distrib(generator);

        int tries = 0;
        while (y >=x-1 && y<= x+1 && tries <20) //eviter de prendre 2 points n et n+1
        {
            int y = distrib(generator);
            tries++; //evite les boucles infinies pour les petits tg
        }
       
        float newdist = dist 
                        - inst.D[tour_geant[x - 1]][tour_geant[x]] 
                        - inst.D[tour_geant[x]][tour_geant[x + 1]]
                        - inst.D[tour_geant[y - 1]][tour_geant[y]]
                        - inst.D[tour_geant[y]][tour_geant[y + 1]]
                        + inst.D[tour_geant[x - 1]][tour_geant[y]]
                        + inst.D[tour_geant[y - 1]][tour_geant[x]]
                        + inst.D[tour_geant[x]][tour_geant[y + 1]]
                        + inst.D[tour_geant[y]][tour_geant[x + 1]];

        if (newdist < dist) //evite la regresssion du score
        {
            //�change :
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
    if (dist == 0) //si la distance n'est pas calculee
    {
        dist = dist_tg(inst);
    }

    //trouver le sommet avec le detour maximal
    float max = 0;
    int imax = 1;

    for (int i = 1; i < tour_geant.size(); i++)
    {
        float detour = inst.D[i - 1][i] + inst.D[i][i + 1];

        if (detour > max)
        {
            max = detour;
            imax = i;
        }
    }
    int val_max = tour_geant[imax];

    //init du generateur aleatoire
    std::default_random_engine generator;

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(1, int(tour_geant.size()) - 2);

    float newdist = dist + 1;
    int iter = 0;
    int  itermax = 200;
    int x = distrib(generator);

    while (newdist > dist&& iter < itermax)
    {
        while (imax == x || imax+1 == x)
        {
            x = distrib(generator);
        }

        float newdist = dist
                            - inst.D[tour_geant[imax - 1]][val_max]
                            - inst.D[val_max][tour_geant[imax + 1]]
                            - inst.D[tour_geant[x - 1]][tour_geant[x]]
                            + inst.D[tour_geant[x - 1]][val_max]
                            + inst.D[val_max][tour_geant[x]]
                            + inst.D[tour_geant[imax - 1]][tour_geant[imax + 1]];
        iter++;
    }

    tour_geant.erase(tour_geant.begin() + imax);
    if (x > imax)
        tour_geant.insert(tour_geant.begin() + x - 1, val_max);
    else
        tour_geant.insert(tour_geant.begin() + x, val_max);

    dist = newdist;
}


void Solution::opt3(Instance& inst, int itermax) //pas demand� dans le TP
{
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
    // START Algorithme SPLIT (avec les labels)
    labels[0].push_back(Label(inst)); 
    for (int i = 0; i < inst.nb_noeud; i++)
    {
        int j = i + 1; // prochain saut
        bool stop = false;
        
        while (!stop) {
            float distance = -1;
            int charge = -1;
            
            if (i + 1 == j)
            {
                distance = inst.D[0][tour_geant[j]] + inst.D[tour_geant[j]][0];
                charge = inst.Q[j];
            }
            else
            {
                distance = distance - inst.D[tour_geant[j-1]][0] + inst.D[tour_geant[j-1]][tour_geant[j]] + inst.D[tour_geant[j]][0];
                charge += inst.Q[j];
            }
            
            bool echec = true;
            for (int k = 0; k < labels[i].size(); k++)
            {
                bool trop = false;
                for (int l = inst.nb_type_camion; l > 0; l--)
                {
                    if (trop) break; // sortir de la boucle
                    if (labels[i][k].nb_camion_restant[l] > 0)
                    {
                        if (inst.cap_camion[l] > charge)
                        {
                            echec = false;
                            Label label_temp = labels[i][k]; // Attention au constructeur de copie
                            float cout = distance * inst.cout_variable_camion[l] + inst.cout_fixe_camion[l]; // cout = distance * Vl + Fl
                            label_temp.cout_total += cout;
                            label_temp.nb_camion_restant[l]--;
                            label_temp.label_pere = k;
                            label_temp.sommet_pere = i;

                            // retourne 1 si gauche meilleur, 0 si incomparable et -1 si droit meilleur -2 si labels identiques
                            bool insert_at_end = true;
                            bool inserted = false;
                            for (int m = 0; m < labels[j].size(); m++)
                            {
                                int cmp = label_temp.compare(labels[j][m]);
                                if (cmp == 1)
                                {
                                    insert_at_end = false;
                                    inserted = true;
                                    labels[j][m] = label_temp;
                                    break;
                                }
                                if (cmp == 0)
                                {
                                    insert_at_end = true;
                                }
                            }
                            if (!inserted && insert_at_end && labels[j].size() < 20)
                            {
                                inserted = true;
                                labels[j].push_back(label_temp);
                            }
                            if (!inserted)
                                trop = true;

                        }
                    }
                }
            }
            j++;
            if (j > inst.nb_noeud || echec)
            {
                stop = true;
            }
                
        }
    }
    // END
}

Label Solution::find_best_label(Instance& inst)
{
    int index = -1;
    float min = INF;
    for (int i = 0; i < labels[inst.nb_noeud].size(); i++)
    {
        if (labels[inst.nb_noeud][i].cout_total < min)
        {
            index = i;
            min = labels[inst.nb_noeud][i].cout_total;
        }
    }
    if (index != -1)
        return labels[inst.nb_noeud][index];
    else
        return Label();
}

void Solution::r_locale(Instance& inst, int itermax)
{
    std::default_random_engine generator;

    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(0, 10000);

    int iter = 0;

    while (iter < itermax)
    {
        int x = distrib(generator);

        if (x == 0)
        {
            //inserer(inst);
        }
        else
        {
            opt2(inst, 95);
        }
        iter++;
    }
    //afficher_tg();
    
    //std::cout << std::endl << dist_tg(inst) << std::endl;

}

unsigned int Solution::hash_solution(Instance& inst, int Hashmax)
{
    unsigned int hash = 0;
    float dist = dist_tg(inst);
    for (int i = 1; i <= inst.nb_noeud; i++)
    {
        hash += dist * tour_geant[i];
    }
    return hash % Hashmax;
}
