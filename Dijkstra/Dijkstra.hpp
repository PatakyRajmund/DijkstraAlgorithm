#include "Graph.hpp"
#ifndef DIJKSTRA
#define DIJKSTRA

/*
* The declaration of the Dijkstra class, represents the Dijkstra algorithm
*/
class Dijkstra :private Graph
{
	unsigned* BestWay;
	bool* isFinished;
	unsigned sizeofBestway;

public:
	Dijkstra() { BestWay = NULL, isFinished = NULL; sizeofBestway = 0; }
	Dijkstra(const Graph& b);
	void Algo(unsigned, unsigned);
	unsigned getsizeofBesW() { return sizeofBestway; }
	unsigned* getBestW() { return BestWay; }
	friend void BestWMaker(Dijkstra& b, double**, unsigned, unsigned);
	~Dijkstra();
};
#endif