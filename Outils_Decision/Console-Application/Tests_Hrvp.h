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
bool test_TG_SIZE(const Instance& inst, const Solution& sol);
bool test_TG_UNIQUE(const Instance& inst, const Solution& sol);

#endif