#include <list>
#include <vector>
#include <algorithm>
#include <string.h>

//Wikipedia: graph from https://es.wikipedia.org/wiki/Anexo:Ejemplo_de_Algoritmo_de_Dijkstra

using namespace std;

typedef unsigned int uint;

struct Path{
	string path;
	uint length = 0;
	bool done = 0;
};

bool allNodesChecked(Path* p, uint size){
	for(uint i = 0; i < size; i++){
		if ( ! (p+i)->done ) return 0;
	}
	return 1;
}

bool findSameLetter(string a, string b){
	int shortest;
	if (a.size() > b.size()) shortest = b.size();
	else shortest = a.size();
	for(int i = 0; i < shortest; i++){
		if ( a[i] == b[i] ) return 1;
	}
	return 0;
}

template <class T>
uint findInVector(vector<T> vec, T elem){
	uint i = 0;
	while(vec.at(i) != elem){
		i++;
	}
	return i;
}

template <class G>
struct CNode{
	typedef typename G::Edge Edge;
	typedef typename G::n N;
	N m_data;
	list<Edge*> m_edges; //TIL: STL list = Double Linked List
};

template <class T>
struct Dist2Node{
	CNode<T>* Node;
	int distance;
};

template <class G>
struct CEdge{
	typedef typename G::Node Node;
	typedef typename G::e E;
	Node* m_nodes[2];
	E m_data;
	bool m_dir; //0, <->; 1, m_nodes[0]->m_nodes[1]
};

template <class N, class E>
class CGraph{
public:
	typedef CGraph<N, E> self;
	typedef CNode<self> Node;
	typedef CEdge<self> Edge;
	typedef N n;
	typedef E e;
	vector<Node*> m_nodes;
	void insertNode(N node);
	void insertEdge(E edge, Node* a, Node* b, bool dir);
	void removeEdge(Node* a, Node* b, E edge);
	void removeNode(Node* a);
	void draw();
	uint Dijkstra(Node* start, Node* goal); //DISCLAIMER: Este para nada es el mejor Dijkstra y tiene (al menos) 69*10^(69) mejoras posibles de hecho
private:
	uint findByValue(N val);
	void Dijks(Node* strt_pnt, Node*& node, Path* p);
	void setMinNode(Path* p, uint size, Node*& minNode);
};

