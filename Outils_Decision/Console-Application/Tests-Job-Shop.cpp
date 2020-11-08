#include "Tests-Job-Shop.h"
#include "../Job-Shop-Lib/Instance.h"
#include "../Job-Shop-Lib/BierwithVector.h"

void Test_Lecture_LaXXX() // sa marche
{
	Instance la01, la02, la03;
	la01.Lecture("DataSet/La01");
	la02.Lecture("DataSet/La02");
	la03.Lecture("DataSet/La03");
	la01.Afficher();
	la02.Afficher();
	la03.Afficher();
}

void Test_Gen_Vecteurs() // sa marche
{
	Instance la01;
	BierwithVector vectors[10];
	la01.Lecture("DataSet/La01");
	la01.Afficher();
	//la01.m = la01.n = 3;
	for (int i = 0; i < 10; i++)
	{
		vectors[i].Generer_Aleatoirement(la01);
		vectors[i].AfficherVecteur();
	}

}

void Test_Eval_Vecteur()
{
	Instance la01;
	BierwithVector vector;
	la01.Lecture("DataSet/La01");
	la01.Afficher();
	vector.Generer_Aleatoirement(la01);
	vector.AfficherVecteur();
	vector.Evaluer(la01);
	vector.AfficherCout();
	std::cout << "DONE!" << std::endl;
}

void Test_Eval_Multiple()
{
	Instance la01;
	BierwithVector vectors[10];
	la01.Lecture("DataSet/La02");
	la01.Afficher();

	for (int i = 0; i<10; i++)
	{ 
	vectors[i].Generer_Aleatoirement(la01);
	vectors[i].AfficherVecteur();
	vectors[i].Evaluer(la01);
	vectors[i].AfficherCout();
	}
	
	std::cout << "DONE!" << std::endl;
}

void Test_Recherche_Locale()
{
	Instance la01;
	BierwithVector vector;
	
	la01.Lecture("DataSet/La01");
	la01.Afficher();

	vector.Generer_Aleatoirement(la01);
	vector.Recherche_Locale(la01, 100);

	std::cout << "DONE!" << std::endl;
}

void Test_La00()
{
	Instance la00;
	la00.Lecture("DataSet/La00");
	la00.Afficher();

	BierwithVector vector;
	vector.Generer_Aleatoirement(la00);
	vector.AfficherVecteur();
	vector.Evaluer(la00);
	vector.AfficherCout();
	//vector.Recherche_Locale(la00, 2000);
	//vector.AfficherVecteur();
	//vector.AfficherCout();
}

void TestGrasp(int valeur)
{
	Instance la01;
	la01.Lecture("DataSet/La01");
	la01.Afficher();
	la01.Grasp(valeur);

}