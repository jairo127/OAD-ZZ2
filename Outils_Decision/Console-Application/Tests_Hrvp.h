#ifndef TESTS_HRVP
#define TESTS_HRVP
#include <iostream>
#include "../HVRP-Lib/Instance.h"
#include "../HVRP-Lib/Label.h"
#include "../HVRP-Lib/Solution.h"


void H_test_lecture();
void H_test_label();
void test_tg_random();
void test_tg_voisin();
void test_tg_voisin_random();
void test_opt2();
void test_opt3();

/// <summary>
/// Teste si la taille du tour-géant généré pour une instance est cohérente.
/// <returns>True si taille ok</returns>
/// </summary>
bool test_TG_SIZE(const Instance& inst, const Solution& sol);

/// <summary>
/// Teste si les éléments dans le tour géant ne sont pas dupliqués.
/// <returns>True si pas de duplicats</returns>
/// </summary>
bool test_TG_UNIQUE(const Instance& inst, const Solution& sol);

#endif