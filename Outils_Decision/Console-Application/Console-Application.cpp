#include <iostream>
#include "Tests-Job-Shop.h"
#include "Tests_Hrvp.h"

int main()
{
	// === Job-Shop ===
	//Test_Lecture_LaXXX();
	//Test_Gen_Vecteurs();
	//Test_Eval_Vecteur();
	//Test_Eval_Multiple();
	//Test_Recherche_Locale();
	//Test_La00();
	//TestGrasp(300);

	// === HVRP ===
	//H_test_lecture();
	//H_test_label();
	//test_tg_random();
	//test_tg_voisin();
	//test_tg_voisin_random();
	//test_opt2(200); //nombre d'essai max pour opt
	//test_inserer();
	test_r_locale(10000);
	//test_split();
	

	return 0;
}
