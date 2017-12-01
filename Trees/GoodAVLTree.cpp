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

template <class T, class C>
bool AVL<T,C>::findInPath(CNode<T>* p){
	for (typename list<CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
		if ( *it == p ) return 1;
	}
	return 0;
}

template <class T, class C>
short AVL<T,C>::posInList(T val){
	short i = 1;
	typename list<CNode<T>* >::iterator it;
	for(it = path.begin() ; it != path.end() && (*it)->m_x != val; it++, i++);
	if (it == path.end() ) return -1;
	return i;
}

template <class T, class C>
void AVL<T,C>::printTree(CNode<T>* p){
	if (!p) return;
	cout << "Valor: " << p->m_x << " prof: " << p->depth << endl;
	if (p->m_nodes[0]) cout << "Hijo izquierdo: " << p->m_nodes[0]->m_x << ' ';
	if (p->m_nodes[1]) cout << "Hijo derecho: " << p->m_nodes[1]->m_x << endl;
	printTree(p->m_nodes[0]);
	printTree(p->m_nodes[1]);
}

template <class T, class C>
bool AVL<T,C>::findHeight(CNode<T>**& p, short& h){
	for(typename list<CNode<T>*>::reverse_iterator it = path.rbegin(); it != path.rend(); it++){
		if ((*it)->height == 2){
			p = &(*it);
			if ( (*it)->m_nodes[1]->height == -1) h = 3;
			else h = 2;
			return 1;
		} else if ((*it)->height == -2){
			p = &(*it);
			if ( (*it)->m_nodes[0]->height == 1) h = -3;
			else h = -2;
			return 1;
		}
	}
	return 0;
}

template <class T, class C>
void AVL<T,C>::RR(CNode<T>** p){
	typename list<CNode<T>*>::iterator it = path.end();
	bool LR = 0, RL = 0;
	if ( (*p)->m_nodes[1] && (*p)->m_nodes[1]->m_nodes[1] && (*p)->m_nodes[1]->m_nodes[1]->height == -1) LR = 1;
	if ( (*p)->height  == 1) {RL = 1; LR = 0;}
	while ( (*it) != (*p) ){
		it--;
	}
	CNode<T>* temp, *father;
	if (*it != m_root){ //si es que se tiene que balancear
		it--;
		if (RL){
			while( *p != (*it)->m_nodes[0]) it--; //busca en el camino hasta encontrar el padre de p
			temp = *it;
		} else 
		//temp = *(--it); //fuera de la raiz
		temp = *(it);
	}
	CNode<T>* gfather = *p;
	father = (*p)->m_nodes[1];
	if (!findInPath(father) ) path.push_back(father);
	CNode<T> *bl = father->m_nodes[0];
	father->m_nodes[0] = gfather;
	gfather->m_nodes[1] = bl;
	if (m_root == gfather) m_root = father;
	else {
		if (RL){
			temp->m_nodes[0] = father;
		} else if (LR && father->height == 1) temp->m_nodes[0] = father;
		else temp->m_nodes[1] = father;
	}
}

template <class T, class C>
void AVL<T,C>::LL(CNode<T>** p){
	bool LR = 0, RL = 0;
	typename list<CNode<T>*>::iterator it = path.end();
	if ((*p)->m_nodes[0] && (*p)->m_nodes[0]->m_nodes[0] && (*p)->m_nodes[0]->m_nodes[0]->height == 1 ) RL = 1;
	if ( (*p)->height == -1) {LR = 1; RL = 0;}
	while ( (*it) != (*p)){
		it--;
	}
	CNode<T>* temp, *father;
	if (*it != m_root){ //si es que se tiene que balancear
		--it;
		if (LR){
			while( *p != (*it)->m_nodes[1]) it--; //busca en el camino hasta encontrar el padre de p
			temp = *it;
		} else 
		temp = (*it);
	}
	CNode<T>* gfather = *(p);
	father = (*p)->m_nodes[0];
	CNode<T> *br = father->m_nodes[1];
	if (!findInPath(father) ) path.push_back(father);
	father->m_nodes[1] = gfather;
	gfather->m_nodes[0] = br;
	if (m_root == gfather){
		m_root = father;
	}
	else {
		if (LR) {
			temp->m_nodes[1] = father;
		}
		else if (RL && father->height == -1) temp->m_nodes[1] = father;
		else temp->m_nodes[0] = father;
	}
}

template <class T, class C>
void AVL<T,C>::LR(CNode<T>** p){
	if (!findInPath( (*p)->m_nodes[1] ) ) path.push_back((*p)->m_nodes[1]);
	LL( &(*p)->m_nodes[1]);
	RR(p);
}

template <class T, class C>
void AVL<T,C>::RL(CNode<T>** p){
	if (!findInPath( (*p)->m_nodes[0] ) ) path.push_back((*p)->m_nodes[0]);
	RR( &(*p)->m_nodes[0]);
	LL(p);
}

template <class T, class C>
CNode<T>** AVL<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[1]){ //the university-one like
		path.push_back(*p);
	}
	/*for(p = &(*p)->m_nodes[1]; *p && (*p)->m_nodes[0]; p = &(*p)->m_nodes[0]){ //VisuAlgo like
		path.push_back(*p);
	}*/
	path.push_back(*p);
	return p;
}

template <class T, class C>
short AVL<T,C>::getHeight(CNode<T>* p){
	//if (p->m_x == x) return 0;
	short left, right;
	if (p->m_nodes[0]) left = (p)->m_nodes[0]->depth;
	else return (p->depth);//left = 0;
	if (p->m_nodes[1]) {
		right = p->m_nodes[1]->depth;
	}
	else return -p->depth;//right = 0;
		return right - left;
}

template <class T, class C>
void AVL<T,C>::updateHeights(T x){
	for(typename list<CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
		(*it)->height = getHeight(*it);
	}
}

template <class T, class C>
void AVL<T,C>::updateDepth(){
	CNode<T>** p;
	bool balance = 0;
	ushort lDepth, rDepth;
	typename list<CNode<T>* >::reverse_iterator rit = path.rbegin();
	while(rit != path.rend() ){
		if ( !(*rit)->m_nodes[0] && !(*rit)->m_nodes[1] ){
			(*rit)->depth = 0;
			rit++;
			continue;
		}
		if ( (*rit)->m_nodes[0] ) lDepth = (*rit)->m_nodes[0]->depth;
		else lDepth = 0;
		if ( (*rit)->m_nodes[1] ) rDepth = (*rit)->m_nodes[1]->depth;
		else rDepth = 0;
		(*rit)->depth = max(lDepth, rDepth) + 1;
		(*rit)->height = getHeight(*rit);
		if ((*rit)->height == 2){
			p = &(*rit);
			balance = 1;
			if ( getHeight((*rit)->m_nodes[1]) == -1){
				LR(p);
			}
			else{
				RR(p);
			}
		} else if ((*rit)->height == -2){
			p = &(*rit);
			balance = 1;
			if ( getHeight((*rit)->m_nodes[0]) == 1){
				RL(p);
			}
			else{
				LL(p);
			}
		}
		if (balance){
			break;
		}
		rit++;
	}
}

template <class T, class C>
void AVL<T,C>::updateDepthR(){
	ushort lDepth, rDepth;
	typename list<CNode<T>* >::iterator it = path.begin();
	while(it != path.end() ){
		if ( !(*it)->m_nodes[0] && !(*it)->m_nodes[1] ){
			(*it)->depth = 0;
			it++;
			continue;
		}
		if ( (*it)->m_nodes[0] ) lDepth = (*it)->m_nodes[0]->depth;
		else lDepth = 0;
		if ( (*it)->m_nodes[1] ) rDepth = (*it)->m_nodes[1]->depth;
		else rDepth = 0;
		(*it)->depth = max(lDepth, rDepth) + 1;
		(*it)->height = getHeight(*it);
		it++;
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
	if(find(x, p)){
		path.clear();
		return 0;
	}
	*p = new CNode<T>(x);
	path.push_back(*p);
	updateDepth();
	updateDepthR();
	path.clear();
	return 1;
}

template<class T, class C>
bool AVL<T,C>::remove(T x){
	CNode<T>** p;
	if(!(find(x,p))){
		path.clear();
		return 0;
	}
	path.push_back(*p);
	if ((*p)->m_nodes[0] && (*p)->m_nodes[1]){
		CNode<T>** q = Rep(p);
		(*p)->m_x = (*q)->m_x;
		p = q;
	}
	CNode<T>* temp = *p;
	*p = (*p)->m_nodes[(*p)->m_nodes[1]!=0];
	delete temp;
	path.pop_back();
	updateDepth();
	updateDepthR(); //this is needed when we do a balance after erasing
	path.clear(); //because a balanced node may not be a part of the path
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
	int xd;
	/*Tree.insert(5); //Hasta remove 21 es un caso
	Tree.insert(7); //Que funciona
	Tree.insert(9);
	Tree.printTree(Tree.m_root);
	cout << endl;
	Tree.insert(3);
	Tree.printTree(Tree.m_root);
	cout << endl;
	Tree.insert(2);
	Tree.insert(1);
	Tree.insert(11);
	Tree.insert(14);
	Tree.insert(15);
	Tree.insert(17);
	Tree.insert(0);
	Tree.insert(6);
	Tree.insert(8);
	Tree.insert(19);
	Tree.insert(21);
	Tree.insert(24);
	Tree.insert(22);
	Tree.insert(69);
	Tree.insert(72);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.remove(19);
	Tree.remove(15);
	Tree.remove(21);
	Tree.remove(7);
	Tree.remove(6); //Hasta aqui bien
	Tree.remove(3);
	Tree.remove(11);
	Tree.remove(69);
	Tree.remove(22);
	Tree.remove(72);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.printTree(Tree.m_root); //tested at https://www.cs.usfca.edu/~galles/visualization/AVLtree.html step by step*/
	/*Tree.insert(4); //RR base test
	Tree.insert(5);
	Tree.insert(6);*/
	/*Tree.insert(7); //LL base test
	Tree.insert(5);
	Tree.insert(3);*/
	/*Tree.insert(5); //LR Base Test
	Tree.insert(9);
	Tree.insert(7);*/
	/*Tree.insert(6); //RL Base Test
	Tree.insert(3);
	Tree.insert(5);*/
	/*Tree.insert(1); //ARBOL PRUEBA GUSTAVO
	Tree.insert(8);
	Tree.insert(3);
	Tree.insert(7);
	Tree.insert(2);
	Tree.insert(9);
	Tree.insert(4);
	Tree.insert(5);
	Tree.insert(6);
	Tree.remove(3);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	Tree.remove(9); //normal
	Tree.printTree(Tree.m_root);
	cin >> xd;
	Tree.remove(2);
	Tree.printTree(Tree.m_root); //hasta aqui funciona*/
	//cin >> xd;
	/*Tree.insert(8); //Esto funca
	Tree.insert(9);
	Tree.insert(10);
	Tree.insert(15);
	Tree.insert(2);
	Tree.insert(1);
	Tree.insert(17);
	Tree.remove(2);
	Tree.remove(5);
	Tree.remove(10);
	Tree.remove(8);*/
	//Tree.printTree(Tree.m_root);
	return 0;
}

