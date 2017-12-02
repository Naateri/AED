#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

typedef unsigned int uint;
typedef unsigned short ushort;

//1, 8, 3, 7, 2, 9, 4, 5, 6

template <class T>
struct CNode{
	T m_x;
	CNode<T>* m_nodes[2];
	short height;
	ushort depth;
	CNode(T x){
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
		height = 0;
		depth = 0;
	}
};

template <class T>
void printList(list<CNode<T>* > xd){
	for(typename list<CNode<T>* >::iterator it = xd.begin(); it != xd.end(); it++){
		cout << (*it)->m_x << ' ';
	}
	cout << endl;
}

template <class T>
struct Menor{
	inline bool operator()(T a, T b){
		return a<b;
	}
};

template <class T, class C>
class AVL{
public:
	CNode<T>* m_root;
	C mc;
	AVL();
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void inorder(CNode<T>* p);
	//private:
	CNode<T>** Rep(CNode<T>** p);
	short getHeight(CNode<T>* p);
	void printTree(CNode<T>* p);
private:
	bool findInPath(CNode<T>* p);
	bool findHeight(CNode<T>**& p, short& h);
	void updateDepth();
	void updateDepthR();
	void updateHeights(T x);
	list< CNode<T>* > path;
	short posInList(T val);
	void RR(CNode<T>** p);
	void LL(CNode<T>** p);
	void LR(CNode<T>** p);
	void RL(CNode<T>** p);
};
