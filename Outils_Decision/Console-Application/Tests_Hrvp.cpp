#include "Tests_Hrvp.h"
//#include "../HVRP-Lib/Instance.h"
//#include "../HVRP-Lib/Label.h"
//#include "../HVRP-Lib/Solution.h"


void H_test_lecture()
{
    Instance* ptr_instance = new Instance;
    Instance & moninstance =  *ptr_instance;
    moninstance.lecture("HFVRP/HVRP_DLP_01");
    moninstance.afficher();
    std::cout << "Fin test lecture" << std::endl;

}

void H_test_label()
{
    Label l1, l2, l3, l4;
    
    // L1 = (2,1,1,1,20)
    l1.nb_camion_restant.push_back(0); // valeur inutile
    l1.nb_camion_restant.push_back(2);
    l1.nb_camion_restant.push_back(1);
    l1.nb_camion_restant.push_back(1);
    l1.nb_camion_restant.push_back(1);
    l1.cout_total = 20;
    
    // L2 = (2,2,1,1,20)
    l2.nb_camion_restant.push_back(0); // valeur inutile
    l2.nb_camion_restant.push_back(2);
    l2.nb_camion_restant.push_back(2);
    l2.nb_camion_restant.push_back(1);
    l2.nb_camion_restant.push_back(1);
    l2.cout_total = 20;

    // L3 = (1,2,1,1,20)
    l3.nb_camion_restant.push_back(0); // valeur inutile
    l3.nb_camion_restant.push_back(1);
    l3.nb_camion_restant.push_back(2);
    l3.nb_camion_restant.push_back(1);
    l3.nb_camion_restant.push_back(1);
    l3.cout_total = 20;

    // L4 = (2,1,1,1,15)
    l4.nb_camion_restant.push_back(0); // valeur inutile
    l4.nb_camion_restant.push_back(2);
    l4.nb_camion_restant.push_back(1);
    l4.nb_camion_restant.push_back(1);
    l4.nb_camion_restant.push_back(1);
    l4.cout_total = 15;

    std::cout << "Compare l1 et l2 = " << l1.compare(l2) << std::endl; // Supposé = 1
    std::cout << "Compare l1 et l3 = " << l1.compare(l3) << std::endl; // Supposé = 0
    std::cout << "Compare l1 et l4 = " << l1.compare(l4) << std::endl; // Supposé = 2
    std::cout << "Compare l2 et l3 = " << l2.compare(l3) << std::endl; // Supposé = 2
    std::cout << "Compare l2 et l4 = " << l2.compare(l4) << std::endl; // Supposé = 2
    // l3.camions ? l4.camions => 3
    std::cout << "Compare l3 et l4 = " << l3.compare(l4) << std::endl; // Supposé = 0
}



void test_tg_random()
{
    std::cout << "EXECUTING : " << __func__ << std::endl;
    Instance* ptr_instance = new Instance;
    Instance& inst = *ptr_instance;
    inst.lecture("HFVRP/HVRP_DLP_01");

    Solution* ptr_sol = new Solution;
    Solution& sol = *ptr_sol;

    sol.gen_tg_random(inst);
    sol.afficher_tg();
   
    test_TG_SIZE(inst, sol);
    test_TG_UNIQUE(inst, sol);

    std::cout << "FINISHED : " << __func__ << std::endl << std::endl;

}

void test_tg_voisin()
{
    std::cout << "EXECUTING : " << __func__ << std::endl;
    Instance* ptr_instance = new Instance;
    Instance& inst = *ptr_instance;
    inst.lecture("HFVRP/HVRP_DLP_01");

    Solution* ptr_sol = new Solution;
    Solution& sol = *ptr_sol;

    sol.gen_tg_voisin(inst);
    sol.afficher_tg();

    test_TG_SIZE(inst, sol);
    test_TG_UNIQUE(inst, sol);

    std::cout << "FINISHED : " << __func__ << std::endl << std::endl;

}

void test_tg_voisin_random()
{
    std::cout << "EXECUTING : " << __func__ << std::endl;
    Instance* ptr_instance = new Instance;
    Instance& inst = *ptr_instance;
    inst.lecture("HFVRP/HVRP_DLP_01");

    Solution* ptr_sol = new Solution;
    Solution& sol = *ptr_sol;

    sol.gen_tg_voisin_random(inst);
    sol.afficher_tg();

    test_TG_SIZE(inst, sol);
    test_TG_UNIQUE(inst, sol);

    std::cout << "FINISHED : " << __func__ << std::endl << std::endl;
}

void test_opt2(int iter)
{
    std::cout << "EXECUTING : " << __func__ << std::endl;
    Instance* ptr_instance = new Instance;
    Instance& inst = *ptr_instance;
    inst.lecture("HFVRP/HVRP_DLP_01");

    Solution* ptr_sol = new Solution;
    Solution& sol = *ptr_sol;

    sol.gen_tg_voisin(inst); //voisin au lieu de voisin random pour plus de répétabilité
    float deb = sol.dist_tg(inst);
    sol.opt2(inst, iter);
    sol.dist_tg(inst);
    test_TG_SIZE(inst, sol);
    test_TG_UNIQUE(inst, sol);

    if (deb == sol.cout)
    {
        std::cout << "ERREUR : ";
    }
    std::cout << "Cout avant opt: " << deb << "    Cout post-opt: " << sol.dist_tg(inst) <<std::endl;

    std::cout << "FINISHED : " << __func__ << std::endl << std::endl;
}

void test_opt3(int iter)
{
    std::cout << "EXECUTING : " << __func__ << std::endl;
    Instance* ptr_instance = new Instance;
    Instance& inst = *ptr_instance;
    inst.lecture("HFVRP/HVRP_DLP_01");

    Solution* ptr_sol = new Solution;
    Solution& sol = *ptr_sol;

    sol.gen_tg_voisin(inst); //voisin au lieu de voisin random pour plus de répétabilité
    float deb = sol.dist_tg(inst);
    sol.opt3(inst, iter);
    

    test_TG_SIZE(inst, sol);
    test_TG_UNIQUE(inst, sol);

    if (deb == sol.cout)
    {
        std::cout << "ERREUR : ";
    }
    std::cout << "Cout avant opt: " << deb << "    Cout post-opt: " << sol.dist_tg(inst) << std::endl;

    

    std::cout << "FINISHED : " << __func__ << std::endl << std::endl;
}


  /////////////////////////////////////////////////////////////////
 //              tests pseudo-unitaires :)                      //
/////////////////////////////////////////////////////////////////

//vérification de la taille du TG
bool test_TG_SIZE(const Instance& inst, const Solution& sol)
{
    if (sol.tour_geant.size() != inst.nb_noeud + 2) //vérif taille du tg
    {
        std::cout << __func__ << ": ERR : sol.tour_geant.size() != inst.nb_noeud+2" << std::endl; //+2 pour le départ du dépot et l'arrivée au dépot
        std::cout << sol.tour_geant.size() << " != " << inst.nb_noeud + 2 << std::endl << __func__ << " FAILED" << std::endl;
        return false;
    }
    else
    {
        std::cout << __func__ << " PASSED" << std::endl;
        return true;
    }
}

bool test_TG_UNIQUE(const Instance& inst, const Solution& sol)
{
    auto cptg = sol.tour_geant;
    std::sort(cptg.begin(), cptg.end());

    for (int i = 1; i < cptg.size(); i++)
    {
        if (cptg[i - 1] == cptg[i] && cptg[i] != 0) //dépot exclu de la vérification
        {
            std::cout << __func__ << " FAILED : Duplicat : " << cptg[i] <<  std::endl;
            return false;
        }
    }
    std::cout << __func__ << " PASSED" << std::endl;
    return true;
}

