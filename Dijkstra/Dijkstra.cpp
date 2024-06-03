#include "Dijkstra.hpp"
#include <climits>

/*
* Giving back the minimum of an array with its index
*/
template<typename T>
T* min(T* arr, unsigned size)
{
	T* arr2 = new T[2];
	unsigned index = 0;
	if (size == 0)return 0;
	T min = arr[0];
	for (unsigned i = 0; i < size; i++)
	{
		if (min > arr[i])
		{
			min = arr[i];
			index = i;
		}

	}
	arr2[0] = min;
	arr2[1] = index;
	return arr2;
}

Dijkstra::Dijkstra(const Graph& b):Graph(b)
{
	isFinished = new bool[numOfElements];
	BestWay = NULL;
	for (unsigned i = 0; i < numOfElements; i++)
	{
		isFinished[i] = false;
	}
	
}

/*
* The Dijkstra algorithm 
*/

void Dijkstra::Algo(unsigned starter, unsigned goal)
{
	double** distances = new double*[numOfElements];
	for (unsigned i = 0; i < numOfElements; i++)
	{
		distances[i] = new double[numOfElements+1];
	}
	double minOfRow=DBL_MAX;
	unsigned min_ID=starter;
	unsigned indexOfLastVisited = starter;
	unsigned numberOfDone = 0;
	unsigned indexerOfBest = 0;
	bool wasIn = false;
	unsigned nowDoing = starter;
	double b4cost=0;
	if (starter == goal)return;
	for (unsigned i = 0; i < numOfElements; i++)
	{
		distances[starter][i] = DBL_MAX;
	}
	while (numberOfDone<numOfElements)
	{
		if (isFinished[min_ID] == false)
		{
			

			nowDoing = min_ID;			
			distances[nowDoing][numOfElements] = indexOfLastVisited;
			for (unsigned i = 0; i < arr[nowDoing].out_num; i++)
			{
				double cost = b4cost+(arr[nowDoing].to[i].cost_km / arr[nowDoing].to[i].speed);
				unsigned indexTo = arr[nowDoing].to[i].to_id;
				if (distances[indexOfLastVisited][indexTo] > cost)
				{
					distances[nowDoing][indexTo] = cost;
					if (minOfRow > cost)
					{
						min_ID = indexTo;
						minOfRow = cost;
					}
				}
				else
				{
					distances[nowDoing][indexTo] = distances[indexOfLastVisited][indexTo];
					if (minOfRow > distances[indexOfLastVisited][indexTo])
					{
						min_ID = indexTo;
						minOfRow = distances[indexOfLastVisited] [indexTo];
					}
				}
			}
			for (unsigned i = 0; i < numOfElements; i++)
			{
				if (i == nowDoing)
				{
					distances[nowDoing] [i] = DBL_MAX;
					continue;
				}
				if (isFinished[i])
				{
					distances[nowDoing][i] = DBL_MAX;
					continue;
				}
				for (unsigned j = 0; j < arr[nowDoing].out_num; j++)
				{

					if (i == arr[nowDoing].to[j].to_id)
					{
						wasIn = true;
					}
				}
				if(!wasIn) distances[nowDoing][i] = distances[indexOfLastVisited][i];
				if (distances[indexOfLastVisited][i] < minOfRow)
				{
					min_ID = i;
					minOfRow = distances[indexOfLastVisited] [i];
				}
				wasIn = false;
			}
			isFinished[nowDoing] = true;
			indexOfLastVisited = nowDoing;
			numberOfDone++;
			if (minOfRow != DBL_MAX) b4cost = minOfRow;
			else b4cost = 0;
			if(arr[min_ID].out_num!=0)minOfRow = DBL_MAX;
		}
		else
		{
			double tmp = DBL_MAX;
			double* infos = min(distances[nowDoing], numOfElements);
			min_ID = infos[1];
		}
		

	}

	BestWMaker(*this, distances, goal, starter);
	for (unsigned i = 0; i < numOfElements; i++) 	
	{
		delete[]distances[i];
	}
}

/*
* Makes from the output of the Algorithm (the matrix output) an output that the user can understand (an array of ids).
*/
void BestWMaker(Dijkstra& b, double** bisher_Bester, unsigned end, unsigned start)
{
	unsigned indexNow = end;
	unsigned indexer=0;
	unsigned tmp = 0;
	unsigned sizer = 0;
	bool finishR = false;
	unsigned good = 0;
	while (indexNow != start)
	{
		unsigned before = bisher_Bester[indexNow][b.numOfElements];
		tmp = bisher_Bester[before][b.numOfElements];
		good= bisher_Bester[before][b.numOfElements];
		if (tmp == before && tmp == start)
		{
			sizer++;
			indexNow = start;
			break;
		}
		while ((bisher_Bester[tmp][indexNow] == bisher_Bester[before][indexNow])&&bisher_Bester[tmp][indexNow]!=DBL_MAX)
		{
			good = tmp;
			tmp = bisher_Bester[tmp][b.numOfElements];

			if (tmp == start)
			{
				finishR = true;
				break;
			}
		}
		if (!finishR)
		{
			sizer++;
			if (tmp != bisher_Bester[before][b.numOfElements]) indexNow = good;
			if (tmp == bisher_Bester[before][b.numOfElements]) indexNow = before;
		}
		else
		{
			
			indexNow= start;
			if(tmp!=good)sizer++;
		}
	}
	if (sizer == 0)sizer++;
	b.BestWay = new unsigned[sizer];
	b.sizeofBestway = sizer;
	finishR = false;
	indexNow = end;
	while(indexNow!=start)
	{
		if (sizer == 1)
		{
			b.BestWay[indexer] = start;
			break;
		}

		unsigned before = bisher_Bester[indexNow][b.numOfElements];
		tmp = bisher_Bester[before][b.numOfElements];
		good= bisher_Bester[before][b.numOfElements];
		
		while (bisher_Bester[tmp][indexNow]==bisher_Bester[before][indexNow] && bisher_Bester[tmp][indexNow] != DBL_MAX)
		{

			
			good = tmp;
			tmp = bisher_Bester[tmp][b.numOfElements];
			if (tmp == start)
			{
				finishR = true;
				break;
			}
		}

		if (!finishR)
		{
			if (tmp == before && tmp == start)
			{
				b.BestWay[indexer] = indexNow;
				indexNow = start;
				break;
			}
			if (tmp != bisher_Bester[before][b.numOfElements])
				indexNow = good;

			if (tmp == bisher_Bester[before][b.numOfElements])
				indexNow = before;

			b.BestWay[indexer] = indexNow;
			indexer++;
		}
		else
		{			
			if (tmp!=good)b.BestWay[indexer] = good;
			indexNow = start;

		}		
	}
	
}
Dijkstra::~Dijkstra()
{
	delete[] BestWay;
	delete[] isFinished;
}