#include "AlgorithmManager.hpp"

/*
* Responsible for managing user interaction
*/
bool AlgorithmManager::ReadInData()
{
	string answer;
	cout << "Would you like to run the Algorithm of Dijkstra? If you would like to add a new node/edge write add"<<endl;
	cin >> answer;
	if (answer == "yes")
	{
		cout << "From where?" << endl;
		unsigned from = 0;
		cin >> from;
		cout << "To where?" << endl;
		unsigned to = 0;
		cin >> to;
		RunAlgorithm(from, to);
	}
	else {
		if (answer == "end")
		{
			return false;
		}
		if (answer == "add")
		{
			bool runsAdding = Adding();
			while (runsAdding)
			{
				runsAdding = Adding();
			}
		}
	}
	return true;
}

/*
* Responsible for adding edges or nodes to the used Graph, if the user wants to do so.
*/

bool AlgorithmManager::Adding() 
{
	cout << "What's the name of the point or would you like to add an edge?" << endl;
	cin >> answer;
	if (answer == "edge")
	{
		cout << "What's the length of the edge?" << endl;
		double km = 0;
		unsigned speed = 0;
		unsigned f_id = 0, to_id = 0;
		cin >> km;
		cout << "What's the speed limit here?" << endl;
		cin >> speed;
		cout << "Where does it come from (id)?" << endl;
		cin >> f_id;
		cout << "Where does it go to?" << endl;
		cin >> to_id;
		graphEdge e(km, speed, to_id, f_id);
		graph += e;
	}
	else 
	{
		if (answer == "end") return false;
		graphPoints gp(answer);

	}
	return true;

}

/*
* Responsible for running the Algorithm, if the user wants to run it.
*/

void AlgorithmManager::RunAlgorithm(unsigned from, unsigned to)
{
	Dijkstra g(graph);
	g.Algo(to, from);
	unsigned* bestWay = g.getBestW();
	cout << "The best way is: " << endl;
	for (unsigned i = 0; i < g.getsizeofBesW(); i++)
	{
		cout << bestWay[i] << " ";
	}
	cout << endl;
}
