#include "Tests_Hrvp.h"
#include "../HVRP-Lib/Instance.h"

void H_test_lecture()
{
    Instance* ptr_instance = new Instance;
    Instance & moninstance =  *ptr_instance;
    moninstance.lecture("HFVRP/HVRP_DLP_01");

    std::cout << "Fin test lecture" << std::endl;
}
