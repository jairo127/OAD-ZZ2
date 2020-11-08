#include "pch.h"
#include "Tuple.h"

Tuple::Tuple() : j(-1), i(-1)
{
}

Tuple::Tuple(int j, int i) : j(j), i(i)
{
}


//ça ne sert à rien d'avoir une classe tuple sans ces opérateurs.......
bool Tuple::operator==(const Tuple& tup) const {
	return (j == tup.j) && (i == tup.i);
}

bool Tuple::operator!=(const Tuple& tup) const {
	return (j != tup.j) || (i != tup.i);
}