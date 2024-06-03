#include "Graph.hpp"
#include "Dijkstra.hpp"
#include "AlgorithmManager.hpp"
#include <fstream>
#include <cstring>
#include <string>

int main()
{
	AlgorithmManager manager;

	bool runsApp = manager.ReadInData();
	while (runsApp)
	{
		runsApp = manager.ReadInData();
	}

	return 0;
}