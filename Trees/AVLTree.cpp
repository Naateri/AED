#include <iostream>
#include <list>
using namespace std;

typedef unsigned int uint;

//1, 8, 3, 7, 2, 9, 4, 5, 6

template <class T>
struct CNode{
	T m_x;
	CNode<T>* m_nodes[2];
	short height;
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
	short getHeight(CNode<T>* p);
	void printTree(CNode<T>* p);
private:
	bool findHeight(CNode<T>**& p, short& h);
	bool findHeightN2(CNode<T>**& p);
	void updateHeights();
	list< CNode<T>* > path;
	void RR(CNode<T>** p);
	void LL(CNode<T>** p);
	void LR(CNode<T>** p);
	void RL(CNode<T>** p);
};

template <class T, class C>
void AVL<T,C>::printTree(CNode<T>* p){
	if (!p) return;
	cout << "Valor: " << p->m_x << endl;
	if (p->m_nodes[0]) cout << "Hijo izquierdo: " << p->m_nodes[0]->m_x << ' ';
	if (p->m_nodes[1]) cout << "Hijo derecho: " << p->m_nodes[1]->m_x << endl;
	printTree(p->m_nodes[0]);
	printTree(p->m_nodes[1]);
}

template <class T, class C>
bool AVL<T,C>::findHeight(CNode<T>**& p, short& h){
	h = 0;
	for(typename list<CNode<T>*>::iterator it = path.begin(); it != path.end(); it++){
		if ((*it)->height == 2){
			p = &(*it);
			h = 2;
			return 1;
		} else if ((*it)->height == -2){
			p = &(*it);
			h = -2;
			return 1;
		}
	}
	return 0;
}

template <class T, class C>
bool AVL<T,C>::findHeightN2(CNode<T>**& p){
	for(typename list<CNode<T>*>::iterator it = path.begin(); it != path.end(); it++){
		if ((*it)->height == -2){
			p = &(*it);
			return 1;
		}
	}
	return 0;
}

template <class T, class C>
void AVL<T,C>::RR(CNode<T>** p){
	typename list<CNode<T>*>::iterator it = path.end();
	while ( (*it) != (*p)->m_nodes[1] ){
		it--;
	}
	CNode<T>* temp;
	if (*it != m_root){
		temp = *(--it);
		it++;
	}
	//it++;
	CNode<T>* gfather = *(it++);
	CNode<T>* father = *(it), *bl = father->m_nodes[0];
	cout << "father: " << father->m_x << endl;
	cout << "bl: " << bl << endl;
	father->m_nodes[0] = gfather;
	gfather->m_nodes[1] = bl;
	if (m_root == gfather) m_root = father;
	else {
		temp->m_nodes[1] = father;
	}
}

template <class T, class C>
void AVL<T,C>::LL(CNode<T>** p){
	typename list<CNode<T>*>::iterator it = path.end();
	while ( (*it) != (*p) ){
		it--;
	}
	CNode<T>* gfather = *(it++);
	CNode<T>* father = *it, *br = father->m_nodes[1];
	father->m_nodes[1] = gfather;
	gfather->m_nodes[0] = br;
	if (m_root == gfather) m_root = father;
}

template <class T, class C>
CNode<T>** AVL<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[0]);
	return p;
}

template <class T, class C>
short AVL<T,C>::getHeight(CNode<T>* p){
	short left, right;
	CNode<T> *temp = p;
	for(left = 0;  temp && (temp)->m_nodes[0]; temp = (temp)->m_nodes[0], left++);
	for(right = 0, temp = p; temp && (temp)->m_nodes[1]; temp = temp->m_nodes[1], right++);
	return right - left;
}

template <class T, class C>
void AVL<T,C>::updateHeights(){
	for(typename list<CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
		(*it)->height = getHeight(*it);
	}
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
	short h;
	if(find(x, p)){
		path.clear();
		return 0;
	}
	*p = new CNode<T>(x);
	path.push_back(*p);
	//if ((*p) != m_root) (*p)->height = (path.back())->height + 1;
	updateHeights();
	/*for(typename list< CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
	//cout << getHeight(*it) << ' ';
	}*/
	//path.push_back(*p);
	findHeight(p, h);
	switch(h){
	case 2:
		RR(p);
		break;
	case -2:
		LL(p);
		break; 
	default:
		cout << "No hay nada\n";
	}
	/*if (findHeight2(p)){
	RR(p);
	}
	if (findHeightN2(p)){
	LL(p);
	}*/
	updateHeights();
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
	Tree.insert(7);
	Tree.insert(4);
	//Tree.insert(4);
	Tree.insert(8);
	Tree.printTree(Tree.m_root);
	cout << endl;
	Tree.insert(9);
	//Tree.insert(3);
	//Tree.inorder(Tree.m_root);
	Tree.printTree(Tree.m_root);
	cout << endl;
	//cout << Tree.getHeight(Tree.m_root);
	return 0;
}

