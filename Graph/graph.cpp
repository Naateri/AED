#include <iostream>
#include <list>
#include <vector>

//Wikipedia: graph from https://es.wikipedia.org/wiki/Anexo:Ejemplo_de_Algoritmo_de_Dijkstra

using namespace std;

typedef unsigned int uint;

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
	uint Dijkstra(Node* start);
};

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
void CGraph<N, E>::removeEdge(Node *a, Node *b, E edge){ //ni idea de porque no funciona con C->2B
	typename list<Edge*>::iterator it = a->m_edges.begin();
	for( ; it != a->m_edges.end() && (*it)->m_data != edge; ++it);
	a->m_edges.erase(it);
	it = b->m_edges.begin();
	for( ; it != b->m_edges.end() && (*it)->m_data != edge; ++it);
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
	for(int i = 0; i < m_nodes.size(); i++){
		cout << m_nodes[i]->m_data << "->";
		for(typename list<Edge*>::iterator it = m_nodes[i]->m_edges.begin(); it != m_nodes[i]->m_edges.end(); ++it){
			if ((*it)->m_nodes[0] == m_nodes[i]) cout << (*it)->m_data << (*it)->m_nodes[1]->m_data; //cuando la arista tiene direccion 1
			else if (!(*it)->m_dir) cout << (*it)->m_data << (*it)->m_nodes[0]->m_data; //cuando la arista es bidireccional
		} //mejorar esta parte si se puede
		cout << endl;
	}
}

template <class N, class E>
uint CGraph<N, E>::Dijkstra(Node* start){
	;
}

int main(int argc, char *argv[]) {
	CGraph<char, int> g;
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
	//g.removeEdge(g.m_nodes[0], g.m_nodes[2], 3);
	g.removeNode(g.m_nodes[1]);
	g.draw();
	/*CGraph<char, int> Wikipedia;
	Wikipedia.insertNode('a');
	Wikipedia.insertNode('b');
	Wikipedia.insertNode('c');
	Wikipedia.insertNode('d');
	Wikipedia.insertNode('e');
	Wikipedia.insertNode('f');
	Wikipedia.insertNode('g');
	Wikipedia.insertNode('z');
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
	*/
	return 0;
}

