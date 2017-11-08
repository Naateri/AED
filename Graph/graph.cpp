#include <iostream>
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

template <class N, class E>
void CGraph<N, E>::setMinNode(Path* p, uint size, Node*& minNode){
	uint min = -1;
	for(uint i = 0; i < size; i++){
		if (!(p+i)->length || (p+i)->done ) continue;
		if (min > (p+i)->length){
			min = (p+i)->length;
			minNode = m_nodes[i];
		}
	}
	//cout << "minNode: " << minNode->m_data << endl;
	p[findInVector(m_nodes, minNode)].done = 1;
}

template<class N, class E>
uint CGraph<N, E>::findByValue(N val){
	uint i = 0;
	while(m_nodes.at(i)->m_data != val){
		i++;
	}
	return i;
}

template <class N, class E>
void CGraph<N, E>::insertNode(N node){
	Node* temp = new Node;
	temp->m_data = node;
	m_nodes.push_back(temp); //meter nodo al vector de nodos del grafo
}

template <class N, class E>
void CGraph<N, E>::insertEdge(E edge, Node* a, Node* b, bool dir){
	Edge* temp = new Edge;
	temp->m_data = edge;
	temp->m_nodes[0] = a; //extremo izquierdo arista
	temp->m_nodes[1] = b; //extremo derecho arista
	temp->m_dir = dir;
	a->m_edges.push_back(temp); //guardando la arista en 
	b->m_edges.push_back(temp); //las respectivas listas de aristas de los nodos
}

template <class N, class E>
void CGraph<N, E>::removeEdge(Node *a, Node *b, E edge){ 
	typename list<Edge*>::iterator it = a->m_edges.begin();
	for( ; it != a->m_edges.end() && (*it)->m_data != edge && (*it)->m_nodes[1] != b; ++it);
	a->m_edges.erase(it);
	it = b->m_edges.begin();
	for( ; it != b->m_edges.end() && (*it)->m_data != edge && (*it)->m_nodes[0] != a; ++it);
	b->m_edges.erase(it);
	delete *it;
}

template <class N, class E>
void CGraph<N, E>::removeNode(Node* a){
	typename list<Edge*>::iterator temp;
	//for(typename list<Edge*>::iterator it = a->m_edges.begin(); it != a->m_edges.end(); ++it){
	typename list<Edge*>::iterator it = a->m_edges.begin();
	while(it != a->m_edges.end()){
		temp = it++;
		removeEdge((*temp)->m_nodes[0], (*temp)->m_nodes[1], (*temp)->m_data);
	}
	delete a;
	m_nodes.erase(m_nodes.begin() + findInVector<Node*>(m_nodes, a) );
	
}

template <class N, class E>
void CGraph<N, E>::draw(){
	for(uint i = 0; i < m_nodes.size(); i++){
		cout << m_nodes[i]->m_data << "->";
		for(typename list<Edge*>::iterator it = m_nodes[i]->m_edges.begin(); it != m_nodes[i]->m_edges.end(); ++it){
			if ((*it)->m_nodes[0] == m_nodes[i]) cout << (*it)->m_data << (*it)->m_nodes[1]->m_data; //cuando la arista tiene direccion 1
			else if (!(*it)->m_dir) cout << (*it)->m_data << (*it)->m_nodes[0]->m_data; //cuando la arista es bidireccional
		} //mejorar esta parte si se puede
		cout << endl;
	}
}

template <class N, class E>
void CGraph<N, E>::Dijks(Node* strt_pnt, Node*& node, Path* p){
	Path* ptr; //para saber si ya paso por ese nodo o no
	Node* minNode;
	string newpath;
	uint prevLen;
	if (allNodesChecked(p, m_nodes.size())) return;
	//cout << "Cur Node: " << node->m_data << endl;
	for(typename list<Edge*>::iterator it = node->m_edges.begin(); it != node->m_edges.end(); it++){
		if (p[findInVector(m_nodes, (*it)->m_nodes[node == (*it)->m_nodes[0]])].done) continue;
		if ((*it)->m_dir){ //arista direccional
			if ( (*it)->m_nodes[1] == node) continue;
			ptr = &p[findInVector(m_nodes, (*it)->m_nodes[1])];
			newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[1]->m_data; //posible nuevo camino
			prevLen = p[findInVector(m_nodes, node)].length; 
			if (ptr->done) continue;
			//ptr->path = newpath;
			if ( !ptr->length || ptr->length > prevLen + (*it)->m_data){ //si la nueva distancia
				ptr->length = prevLen + (*it)->m_data; //es menor
				ptr->path = newpath;
			}
		} else { //arista bidireccional
			if (node == (*it)->m_nodes[0]){ //el nodo esta en la primera pos de la arista
				ptr = &p[findInVector(m_nodes, (*it)->m_nodes[1])]; //nos lleva a la segunda
				newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[1]->m_data;
				//cout << "Connected to: " << (*it)->m_nodes[1]->m_data << endl;
			} else {
				ptr = &p[findInVector(m_nodes, (*it)->m_nodes[0])];
				newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[0]->m_data;
				//cout << "Connected to: " << (*it)->m_nodes[0]->m_data << endl;
			}
			prevLen = p[findInVector(m_nodes, node)].length; 
			if (ptr->done) continue;
			if ( !ptr->length || ptr->length > prevLen + (*it)->m_data){ //si la nueva distancia
				ptr->length = prevLen + (*it)->m_data; //es menor a la ya guardada
				ptr->path = newpath;
			}
		}
	}
	setMinNode(p, m_nodes.size(), minNode);
	//int xd;
	//cin>>xd;
	if (node == minNode){
		minNode = strt_pnt;
		Dijks(strt_pnt, minNode, p);
	}
	node = minNode;
	return;
}

template <class N, class E>
uint CGraph<N, E>::Dijkstra(Node* start, Node* goal){
	Path* paths = new Path[m_nodes.size()];
	Node* copy = start;
	paths[findInVector(m_nodes, start)].done = 1; //ya "paso" por el nodo de inicio
	paths[findInVector(m_nodes, start)].path = start->m_data; //y el camino es el mismo nodo
	for(uint i = 0; i < m_nodes.size(); i++){
		Dijks(copy, start, paths);
		if (start == goal) break;
	}
	uint res = paths[findInVector(m_nodes, goal)].length;
	cout << "Camino: " << paths[findInVector(m_nodes, goal)].path << endl;
	delete[] paths;
	return res;
}

int main(int argc, char *argv[]) {
	/*CGraph<char, int> g;
	g.insertNode('A');
	g.insertNode('B');
	g.insertNode('C');
	g.insertNode('D');
	g.insertNode('E');
	g.insertNode('X');
	g.insertEdge(2, g.m_nodes[0], g.m_nodes[1], 1);
	g.insertEdge(3, g.m_nodes[0], g.m_nodes[2], 1);
	g.insertEdge(6, g.m_nodes[1], g.m_nodes[3], 1);
	g.insertEdge(7, g.m_nodes[2], g.m_nodes[3], 1);
	g.insertEdge(5, g.m_nodes[2], g.m_nodes[4], 1);
	g.insertEdge(2, g.m_nodes[2], g.m_nodes[1], 1);
	g.insertEdge(3, g.m_nodes[3], g.m_nodes[4], 1);
	g.insertEdge(7, g.m_nodes[3], g.m_nodes[5], 1);
	g.insertEdge(1, g.m_nodes[4], g.m_nodes[5], 0);
	//g.removeEdge(g.m_nodes[2], g.m_nodes[1], 2);
	//g.removeNode(g.m_nodes[3]);
	g.draw();*/
	/*CGraph<char, uint> Wikipedia;
	Wikipedia.insertNode('A');
	Wikipedia.insertNode('B');
	Wikipedia.insertNode('C');
	Wikipedia.insertNode('D');
	Wikipedia.insertNode('E');
	Wikipedia.insertNode('F');
	Wikipedia.insertNode('G');
	Wikipedia.insertNode('Z');
	Wikipedia.insertEdge(16, Wikipedia.m_nodes[0], Wikipedia.m_nodes[1], 0);
	Wikipedia.insertEdge(10, Wikipedia.m_nodes[0], Wikipedia.m_nodes[2], 0);
	Wikipedia.insertEdge(5, Wikipedia.m_nodes[0], Wikipedia.m_nodes[3], 0);
	Wikipedia.insertEdge(2, Wikipedia.m_nodes[1], Wikipedia.m_nodes[2], 0);
	Wikipedia.insertEdge(4, Wikipedia.m_nodes[1], Wikipedia.m_nodes[5], 0);
	Wikipedia.insertEdge(6, Wikipedia.m_nodes[1], Wikipedia.m_nodes[6], 0);
	Wikipedia.insertEdge(4, Wikipedia.m_nodes[2], Wikipedia.m_nodes[3], 0);
	Wikipedia.insertEdge(10, Wikipedia.m_nodes[2], Wikipedia.m_nodes[4], 0);
	Wikipedia.insertEdge(12, Wikipedia.m_nodes[2], Wikipedia.m_nodes[5], 0);
	Wikipedia.insertEdge(15, Wikipedia.m_nodes[3], Wikipedia.m_nodes[4], 0);
	Wikipedia.insertEdge(3, Wikipedia.m_nodes[4], Wikipedia.m_nodes[5], 0);
	Wikipedia.insertEdge(5, Wikipedia.m_nodes[4], Wikipedia.m_nodes[7], 0);
	Wikipedia.insertEdge(8, Wikipedia.m_nodes[5], Wikipedia.m_nodes[6], 0);
	Wikipedia.insertEdge(16, Wikipedia.m_nodes[5], Wikipedia.m_nodes[7], 0);
	Wikipedia.insertEdge(7, Wikipedia.m_nodes[6], Wikipedia.m_nodes[7], 0);
	Wikipedia.draw();
	cout << Wikipedia.Dijkstra(Wikipedia.m_nodes[7], Wikipedia.m_nodes[0]) << endl;*/
	CGraph<char, uint> Test1;
	Test1.insertNode('A');
	Test1.insertNode('B');
	Test1.insertNode('C');
	Test1.insertNode('D');
	Test1.insertNode('E');
	Test1.insertNode('F');
	Test1.insertNode('G');
	Test1.insertNode('H');
	Test1.insertNode('I');
	Test1.insertNode('J');
	Test1.insertEdge(6, Test1.m_nodes[0], Test1.m_nodes[3], 1);
	Test1.insertEdge(8, Test1.m_nodes[0], Test1.m_nodes[6], 0);
	Test1.insertEdge(5, Test1.m_nodes[1], Test1.m_nodes[0], 1);
	Test1.insertEdge(10, Test1.m_nodes[1], Test1.m_nodes[2], 1);
	Test1.insertEdge(11, Test1.m_nodes[1], Test1.m_nodes[7], 1);
	Test1.insertEdge(6, Test1.m_nodes[2], Test1.m_nodes[5], 1);
	Test1.insertEdge(15, Test1.m_nodes[3], Test1.m_nodes[1], 1);
	Test1.insertEdge(18, Test1.m_nodes[3], Test1.m_nodes[4], 1);
	Test1.insertEdge(20, Test1.m_nodes[4], Test1.m_nodes[8], 0);
	Test1.insertEdge(16, Test1.m_nodes[5], Test1.m_nodes[4], 1);
	Test1.insertEdge(14, Test1.m_nodes[5], Test1.m_nodes[8], 0);
	Test1.insertEdge(7, Test1.m_nodes[5], Test1.m_nodes[9], 0);
	Test1.insertEdge(1, Test1.m_nodes[6], Test1.m_nodes[1], 1);
	Test1.insertEdge(4, Test1.m_nodes[6], Test1.m_nodes[7], 0);
	Test1.insertEdge(2, Test1.m_nodes[7], Test1.m_nodes[5], 1);
	Test1.insertEdge(25, Test1.m_nodes[8], Test1.m_nodes[9], 0);
	Test1.insertEdge(8, Test1.m_nodes[9], Test1.m_nodes[6], 1);
	Test1.insertEdge(3, Test1.m_nodes[9], Test1.m_nodes[7], 1);
	Test1.draw();
	cout << Test1.Dijkstra(Test1.m_nodes[4], Test1.m_nodes[2]);
	return 0;
}

