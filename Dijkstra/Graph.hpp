#include <iostream>
using std::string;
using namespace std;
#ifndef GRAPH
#define GRAPH

/*
* Represents the nodes of the Graph
* In the to array are the outgoing edges stored
*/

 struct graphPoints
{
	string name;
	unsigned id;
	struct graphEdge *to;
	unsigned out_num;
	graphPoints(const string name_, const unsigned i, graphEdge* tl = NULL, unsigned outgoing=0)
	{
		name = name_;
		id = i;
		to = NULL;
		out_num = outgoing;
	}
	graphPoints& operator=(const graphPoints&);

	graphPoints(const string name_) { name = name_; to = NULL; }
	graphPoints() {to = NULL; }
	~graphPoints();
	
};

 /*
 * A struct that represents the edges of the Graph
 * For length is the cost in kms, and there is a speed limit
 */
struct graphEdge
{
	graphEdge() { to = NULL; }
	graphEdge(double km, unsigned s_limit, unsigned to_id_, unsigned f_id)
	{
		cost_km = km;
		speed = s_limit;
		to_id =to_id_;
		from_id = f_id;
	}
	double cost_km;
	unsigned speed;
	struct graphPoints* to;
	unsigned to_id;
	unsigned from_id;
	~graphEdge()
	{
		
	}
};

/*
* Represents the graph itself
*/
class Graph
{
protected:
	graphPoints* arr;
	unsigned numOfElements;
	unsigned startingSize;
public:
	Graph(unsigned groesse = 0) { startingSize = groesse; if (groesse == 0) { arr = NULL; return; } arr = new graphPoints[startingSize]; numOfElements = 0; }

	Graph& operator+=(const graphPoints&);
	Graph& operator+=(const graphEdge&);
	Graph& operator=(const Graph&);
	graphEdge swap(graphEdge& b);
	Graph(const Graph& other);
	void print();
	graphPoints* getTo(unsigned num) 
	{ 
		return arr[num].to[num].to; 
	}
	friend istream& operator>> (istream& is,  Graph& b);
	virtual ~Graph();

};

#endif