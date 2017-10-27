#include <iostream>
#include <list>
using namespace std;

typedef unsigned int uint;

template <class T>
struct CNode{
	T m_x;
	CNode<T>* m_nodes[2];
	uint height;
	CNode(T x){
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
		height = 0;
	}
};

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
private:
	list< CNode<T>* > path;
	int getHeight(CNode<T>* p);
	void RR(CNode<T>** p);
	void LL(CNode<T>** p);
	void LR(CNode<T>** p);
	void RL(CNode<T>** p);
};

template <class T, class C>
CNode<T>** AVL<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[0]);
	return p;
}

template <class T, class C>
int AVL<T,C>::getHeight(CNode<T>* p){
	int left, right;
	CNode<T> temp = p;
	for(left = 0;  temp && (temp)->m_nodes[0]; temp = (temp)->m_nodes[0], left++);
	for(right = 0, temp = p; temp && (temp)->m_nodes[1]; temp = temp->m_nodes[1], right++);
	return right - left;
}

template <class T, class C>
AVL<T,C>::AVL(){
	this->m_root = 0;
}

template <class T, class C>
bool AVL<T,C>::find(T x, CNode<T>**& p){
	for(p = &m_root; *p && (*p)->m_x != x; p = &((*p)->m_nodes[mc((*p)->m_x, x)])){
		path.push_back(*p);
	}
	return !!*p;
}

template <class T, class C>
bool AVL<T,C>::insert(T x){
	CNode<T>** p;
	if(find(x, p)) return 0;
	*p = new CNode<T>(x);
	if ((*p) != m_root) (*p)->height = (path.back())->height + 1;
	for(typename list< CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
		cout << getHeight(*it);
	}
	path.clear();
	return 1;
}

template<class T, class C>
bool AVL<T,C>::remove(T x){
	CNode<T>** p;
	if(!(find(x,p))) return 0;
	if ((*p)->m_nodes[0] && (*p)->m_nodes[1]){
		CNode<T>** q = Rep(p);
		(*p)->m_x = (*q)->m_x;
		p = q;
	}
	CNode<T>* temp = *p;
	*p = (*p)->m_nodes[(*p)->m_nodes[1]!=0];
	delete temp;
	return 1;
}

template <class T, class C>
void AVL<T,C>::inorder(CNode<T>* p){
	if (!p) return;
	inorder(p->m_nodes[0]);
	cout << p->m_x << " ";
	inorder(p->m_nodes[1]);
}

int main(int argc, char *argv[]) {
	AVL<int, Menor <int> > Tree;
	Tree.insert(5);
	Tree.insert(6);
	Tree.inorder(Tree.m_root);
	return 0;
}

