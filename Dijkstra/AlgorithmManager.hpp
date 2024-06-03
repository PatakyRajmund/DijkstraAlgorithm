#ifndef ALGORITHM_M
#define ALGORITHM_M
#include "Graph.hpp"
#include "Dijkstra.hpp"
#include <fstream>
#include <cstring>
#include <string>
/*
* A class for running and managing the Application.
*/
class AlgorithmManager {
private:
	bool isOngoing = true;
	string answer;
	Graph graph;
	bool Adding();
	void RunAlgorithm(unsigned from, unsigned to);

public:
	AlgorithmManager()
	{
		ifstream fin;
		fin.open("inputs.txt");
		fin >> graph;
		fin.close();
	}
	bool ReadInData();


};


#endif