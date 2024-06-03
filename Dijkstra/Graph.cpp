#include "Graph.hpp"
#include <string>

/*
* Adding new nodes to the Graph.
*/
Graph& Graph::operator +=(const graphPoints& b)
{

	if (numOfElements+1 <= startingSize)
	{
		arr[b.id].id = b.id;
		arr[b.id].name = b.name;
		arr[b.id].to = NULL;
		arr[b.id].out_num = 0;
		numOfElements++;
		return *this;
	}
	else
	{
		Graph k(numOfElements + 1);
		for (unsigned i = 0; i < numOfElements; i++)
		{
			k.arr[i] = arr[i];
		}
		k.startingSize = startingSize;
		k.numOfElements = numOfElements + 1;
		unsigned id = numOfElements;
		k.arr[id].id = id;
		k.arr[id].name = b.name;
		k.arr[id].to = NULL;
		k.arr[id].out_num = 0;

		*this = k;
		return *this;

	}

}

/*
* Adding new edges to the Graph
*/

Graph& Graph::operator+=(const graphEdge& b) 
{
	unsigned out_num = arr[b.from_id].out_num;
	if (out_num == 0)
	{
		
		graphEdge* tmp= new graphEdge[1];
		tmp->cost_km = b.cost_km;
		tmp->from_id = b.from_id;
		tmp->speed = b.speed;
		tmp->to_id = b.to_id;
		tmp->to = &arr[b.to_id];
		arr[b.from_id].to = tmp;

	}
	else
	{
		graphEdge* tmp= new graphEdge[out_num+1];
		
		for (unsigned i = 0; i <out_num ; i++)
		{
			tmp[i].cost_km = arr[b.from_id].to[i].cost_km;
			tmp[i].from_id = b.from_id;
			tmp[i].speed = arr[b.from_id].to[i].speed;
			tmp[i].to = &arr[arr[b.from_id].to[i].to_id];
			tmp[i].to_id = arr[b.from_id].to[i].to_id;;
		}
		tmp[out_num].cost_km = b.cost_km;
		tmp[out_num].from_id = b.from_id;
		tmp[out_num].speed = b.speed;
		tmp[out_num].to = &arr[b.to_id];
		tmp[out_num].to_id = b.to_id;


		if(arr[b.from_id].to!=NULL)delete[] arr[b.from_id].to;
		arr[b.from_id].to = tmp;
		
	}
	arr[b.from_id].out_num++;

	return *this;
}

graphEdge Graph::swap(graphEdge& b)
{
	unsigned tmp = b.from_id;
	b.from_id = b.to_id;
	b.to_id = tmp;
	b.to = &arr[b.to_id];
	return b;
}

/*
* A print function for the Graph for testing
*/
void Graph::print()
{
	for (unsigned i = 0; i < numOfElements; i++)
	{
		cout << arr[i].id << " point has the name: " << arr[i].name << " and has " << arr[i].out_num << " outgoing edges." << endl;
		cout << "These are: ";
		for (unsigned j = 0; j < arr[i].out_num; j++)
		{
			cout << "Cost in km: " << arr[i].to[j].cost_km << " allowed speed kmph: " << arr[i].to[j].speed << " and goes to: " <<
				arr[i].to[j].to_id << endl;
		}
	}
}

/*
* Responsible for reading in the data from the input file, with operator overload
*/

istream& operator>>(istream& is, Graph& b)
{
	string in;
	unsigned numberOfStarters = 0;
	unsigned indexer = 0;
	unsigned id = 0;
	string name;
	graphEdge l;
	graphPoints p;


	while (getline(is, in))
	{
		numberOfStarters++;
	}
	Graph k(numberOfStarters);
	is.clear();
	is.seekg(0);
	for (unsigned i = 0; i < numberOfStarters; i++)
	{
		unsigned where = 0;
		unsigned till = 0;

		getline(is, in);
		p.id = i;
		where= in.find_first_of('"')+1;
		till = in.find_first_of('"', where);
		p.name = in.substr(where, till - where);

		k += p;
		if (in.find('-',till) < in.size()) continue;

		while (indexer<in.size())
		{
			where=in.find_first_of(' ', till)+1;
			indexer = in.find_first_of('[', where);
			l.from_id = i;
			l.to_id = stoul(in.substr(where, indexer - where));
			where=in.find_first_of('[', indexer)+1;
			indexer = in.find_first_of(',', where);
			l.cost_km = stof( in.substr(where, indexer - where));
			where = in.find_first_not_of(',', indexer);
			indexer = in.find_first_of(']', where);
			l.speed = stoul(in.substr(where, indexer - where));
			indexer++;
			till = indexer;
			k += l;

		}
		indexer = 0;

	}
	for (unsigned i = 0; i < numberOfStarters; i++)
	{
		unsigned out_numb = k.arr[i].out_num;
		graphEdge tmp;
		for ( unsigned j = 0; j < out_numb; j++)
		{
			tmp = k.arr[i].to[j];
			if (k.arr[i].to[j].to_id < i) continue;
			k.swap(tmp);
			k += tmp;
		}
	}
	b = k;

	return is;
}


Graph& Graph::operator=(const Graph& b)
{
	if (arr != NULL) delete[] arr;
	startingSize = b.startingSize;
	numOfElements = b.numOfElements;
	arr = new graphPoints[b.numOfElements];
	for (unsigned i = 0; i < numOfElements; i++)
	{
		arr[i] = b.arr[i];
	}
	return *this;
}

Graph::~Graph()
{
	if(arr != NULL) delete[]arr;
	arr = NULL;
	
}

Graph::Graph(const Graph& other)
{
	numOfElements = other.numOfElements;
	if (numOfElements != 0)
	{
		arr = new graphPoints[other.numOfElements];
		for (unsigned i = 0; i < numOfElements; i++)
		{
			arr[i] = other.arr[i];
		}
	}
	else arr = NULL;
}

graphPoints& graphPoints::operator=(const graphPoints& other)
{

	name = other.name;
	id = other.id;
	out_num = other.out_num;
	if (out_num != 0)
	{
		to = new graphEdge[out_num];
		for (unsigned i = 0; i < out_num; i++)
		{
			to[i] = other.to[i];
		}
	}
	else to = NULL;
	return *this;
}


graphPoints::~graphPoints()
{
	
	if (to != NULL)delete[] to;
	to = NULL;
	out_num = 0;
	
}