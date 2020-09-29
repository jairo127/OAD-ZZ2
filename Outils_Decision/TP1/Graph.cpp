#include "Graph.hpp"

// Constructors
Graph::Graph(int n) : n(n) {};

Graph::Graph(string file_path)
{
	ifstream file(file_path.c_str());
	int nb_arc = 0;
	if (!file.fail())
	{
		file >> n; // lecture nb sommet
		
		// parcours des sommets à insérer
		for (int i = 1; i <= n; i++)
		{
			int nb_s = 0;
			int succ = 1;
			int tmp;
			string lecture;
			file >> tmp;
			file >> lecture;
			while (lecture != "*")
			{
				S[i][succ] = atoi(lecture.c_str());
				succ++; // Curseur de successeur
				nb_s++; // Nombre de successeurs
				file >> lecture;
			}
			ns[i] = nb_s;
		}
		// cout << "Lecture sommets done !" << endl;
		file >> nb_arc;
		int arc_courant = 0;
		while (arc_courant < nb_arc)
		{
			// lecture des arc d'un sommet
			int sommet, sommet_dest;
			float poids;
			file >> sommet;
			file >> sommet_dest;
			file >> poids;
			l[sommet][1] = poids;
			arc_courant++;
			int nb_s = ns[sommet];
			// lecture des poids des autres successeurs du sommet
			for (int i = 2; i <= nb_s; i++)
			{
				file >> sommet;
				file >> sommet_dest;
				file >> poids;
				l[sommet][i] = poids;
				arc_courant++;
			}
		}
		file.close();
	}
}

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

void Graph::insertL(int i, int j, float val)
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

float Graph::getL(int i, int j)
{
	return l[i][j];
}

int Graph::getNS(int i)
{
	return ns[i];
}