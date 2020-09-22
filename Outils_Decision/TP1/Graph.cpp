#include "Graph.hpp"

// Constructors
Graph::Graph(int n) : n(n) {};

// Methods
int Graph::getN()
{
	return n;
}

void Graph::setN(int new_n)
{
	n = new_n;
}

void Graph::insertS(int i, int j, int val)
{
	S[i][j] = val;
}

void Graph::insertL(int i, int j, int val)
{
	l[i][j] = val;
}

void Graph::insertNS(int i, int val)
{
	ns[i] = val;
}

int Graph::getS(int i, int j)
{
	return S[i][j];
}

int Graph::getL(int i, int j)
{
	return l[i][j];
}

int Graph::getNS(int i)
{
	return ns[i];
}