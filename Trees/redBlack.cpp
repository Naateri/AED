#include <iostream>
using namespace std;

template <class T>
struct CNode{
	T m_x;
	CNode<T>* m_nodes[2];
	bool colour; //0 = red, 1 = black
	CNode(T x){
		m_nodes[0] = m_nodes[1] = 0;
		m_x = x;
		colour = 0;
	}
};

template <class T>
struct Menor{
	inline bool operator()(T a, T b){
		return a<b;
	}
};

template <class T, class C>
class RedBlack{
public:
	CNode<T>* m_root;
	C mc;
	CBTree();
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void inorder(CNode<T>* p);
	//private:
	CNode<T>** Rep(CNode<T>** p);
};

template <class T, class C>
CNode<T>** CBTree<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[0]);
	return p;
}

template <class T, class C>
CBTree<T,C>::CBTree(){
	this->m_root = 0;
}

template <class T, class C>
bool CBTree<T,C>::find(T x, CNode<T>**& p){
	for(p = &m_root; *p && (*p)->m_x != x; p = &((*p)->m_nodes[mc((*p)->m_x, x)]));
	return !!*p;
}

template <class T, class C>
bool CBTree<T,C>::insert(T x){
	CNode<T>** p;
	if(find(x, p)) return 0;
	*p = new CNode<T>(x);
	if (*p == this->m_root)
		(*p)->colour = 1;
	return 1;
}

template<class T, class C>
bool CBTree<T,C>::remove(T x){
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
void CBTree<T,C>::inorder(CNode<T>* p){
	if (!p) return;
	inorder(p->m_nodes[0]);
	cout << p->m_x << " ";
	inorder(p->m_nodes[1]);
}

int main(int argc, char *argv[]) {
	return 0;
}

