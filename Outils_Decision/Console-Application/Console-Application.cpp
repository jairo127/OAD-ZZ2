#include <iostream>
#include "Tests-Job-Shop.h"
#include "Tests_Hrvp.h"

int main()
{
	 //Job-Shop
	//Test_Lecture_LaXXX();
	//Test_Gen_Vecteurs();
	//Test_Eval_Vecteur();
	//Test_Eval_Multiple();
	/*Test_Recherche_Locale();*/
	//Test_La00();
	int sum=0;
	for (int i=0; i<10; i++)
	{ 
		sum+=TestGrasp(50, 20);
	}
	std::cout << "moyenne : " << sum / 10;
	/* HVRP */
	//H_test_lecture();
	return 0;
}
