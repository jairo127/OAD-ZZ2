#pragma once
class Tuple
{
	public:
		int j;//job
		int i;//num d'opé
		Tuple();
		Tuple(int i, int j);
		bool operator==(const Tuple& tup) const;
		bool operator!=(const Tuple& tup) const;
};

