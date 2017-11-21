#include <iostream>
#include <list>
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
	void updateDepth(short &h);
	void updateHeights(T x);
	list< CNode<T>* > path;
	short posInList(T val);
	void RR(CNode<T>** p);
	void LL(CNode<T>** p);
	void LR(CNode<T>** p);
	void RL(CNode<T>** p);
};

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
	//it++;
	while ( (*it) != (*p) ){
		it--;
	}
	CNode<T>* temp, *father;
	if (*it != m_root){ //si es que se tiene que balancear
		temp = *(--it); //fuera de la raiz
		it++; //regresando a la posicion
	}
	//CNode<T>* gfather = *(it++);
	CNode<T>* gfather = *it;
	/*if (LR) father = *(++it);
	else father = *(it);*/
	father = (*it)->m_nodes[1];
	//if (!father->m_nodes[0] && !father->m_nodes[1] ) RL = 1;
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
	if (!LR && !RL){
		gfather->depth -= 2;
	}
	if (LR){
		gfather->depth -= 2;
		father->depth++;
		father->m_nodes[1]->depth--;
	}
	if (RL)
		cout << "Father val RR part of RL: " << father->m_x << endl;
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
		temp = *(--it); //fuera de la raiz
		it++; //regresando a la posicion
	}
	CNode<T>* gfather = *(it);
	/*if(RL) father = *(++it);
	else father = *(it);*/
	father = (*it)->m_nodes[0];
	CNode<T> *br = father->m_nodes[1];
	//if ( !father->m_nodes[0] && !father->m_nodes[1] ) LR = 1;
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
	if (!LR && !RL){
		gfather->depth -= 2;
	}
	if (RL){
		cout << "Father val: " << father->m_x << endl;
		cout << "GFather val: " << gfather->m_x << endl;
		cout << "gfather depth: " << gfather->depth << endl;
		int x; cin >> x;
		father->depth++;
		gfather->depth -= 2;
		cout << "new gfather depth: " << gfather->depth << endl;
		cin >> x;
		father->m_nodes[1]->depth -= 1;
	}
}

template <class T, class C>
void AVL<T,C>::LR(CNode<T>** p){
	LL( &(*p)->m_nodes[1]);
	RR(p);
	
}

template <class T, class C>
void AVL<T,C>::RL(CNode<T>** p){
	RR( &(*p)->m_nodes[0]);
	LL(p);
}

template <class T, class C>
CNode<T>** AVL<T,C>::Rep(CNode<T>** p){
	for(p = &(*p)->m_nodes[0]; *p && (*p)->m_nodes[1]; p = &(*p)->m_nodes[1]){
		path.push_back(*p);
	}
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
void AVL<T,C>::updateDepth(short& h){
	CNode<T>** p;
	bool balance = 0;
	typename list<CNode<T>* >::reverse_iterator rit = path.rbegin();
	rit++;
	while(rit != path.rend() ){
		(*rit)->depth = (*--rit)->depth + 1;
		rit++;
		if ( (*rit)->m_x == 7 ) cout << "Depth of 7 is: " << (*rit)->depth << endl;
		(*rit)->height = getHeight(*rit);
		/*cout << "Height of: " << (*rit)->m_x << " : " << (*rit)->height << endl;
		cin >> h;*/
		if ((*rit)->height == 2){
			p = &(*rit);
			balance = 1;
			if ( (*rit)->m_nodes[1]->height == -1){
				/*h = 3;*/ LR(p);
			}
			else{
				/*h = 2*/RR(p);
			}
		} else if ((*rit)->height == -2){
			p = &(*rit);
			balance = 1;
			if ( (*rit)->m_nodes[0]->height == 1){
				cout << "P is: " << (*p)->m_x << endl;
				/*h = -3*/ RL(p);
			}
			else{
				/*h = -2*/ LL(p);
			}
		}
		if (balance) break;
		rit++;
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
	short h = 0;
	bool Switch = 1;
	if(find(x, p)){
		path.clear();
		return 0;
	}
	//(*p)->depth ++ 1;
	*p = new CNode<T>(x);
	path.push_back(*p);
	//printTree(m_root);
	updateDepth(h);
	/*cout << "Depths:\n";
	for(typename list<CNode<T>* >::iterator it = path.begin(); it != path.end(); it++){
		cout << "Cur val: " << (*it)->m_x << ", depth: " << (*it)->depth << endl;
		cin >> h;
	}*/
	/*updateHeights(x);
	findHeight(p, h);
	switch(h){
	case 2:
		RR(p);
		break;
	case -2:
		LL(p);
		break; 
	case 3:
		LR(p);
		break;
	case -3:
		RL(p);
		break;
	default:
		Switch = 0;
		break;
	}*/
	//if (Switch) updateHeights(x);
	//updateDepth(h);
	path.clear();
	return 1;
}

template<class T, class C>
bool AVL<T,C>::remove(T x){
	CNode<T>** p;
	short h = 0;
	bool Switch = 0;
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
	p = &(*p)->m_nodes[(*p)->m_nodes[1]!=0];
	delete temp;
	updateHeights(x);
	findHeight(p, h);
	switch(h){
	case 2:
		RR(p);
		break;
	case -2:
		LL(p);
		break; 
	case 3:
		LR(p);
		break;
	case -3:
		RL(p);
		break;
	default:
		Switch = 0;
		break;
	}
	path.clear();
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
	/*Tree.insert(5);
	Tree.insert(7);
	Tree.insert(9);
	Tree.printTree(Tree.m_root);
	cout << endl;
	Tree.insert(3);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	Tree.insert(2);
	Tree.printTree(Tree.m_root);
	cout << endl;
	cin >> xd;
	Tree.insert(1);
	//Tree.insert(1);
	//Tree.inorder(Tree.m_root);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(11);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(14);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(15);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(17);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(0);
	Tree.printTree(Tree.m_root);
	cin >> xd;
	cout << endl;
	Tree.insert(6); //BREAKPOINT
	Tree.insert(8);
	Tree.insert(19);
	Tree.insert(21);
	Tree.insert(24);
	Tree.insert(22);
	Tree.insert(69);
	Tree.insert(72);
	Tree.printTree(Tree.m_root);*/
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
	Tree.insert(1); //ARBOL PRUEBA GUSTAVO
	Tree.insert(8);
	Tree.insert(3);
	Tree.insert(7);
	Tree.insert(2);
	Tree.insert(9);
	cout << "insertando 4:\n";
	cin >> xd;
	Tree.insert(4);
	Tree.printTree(Tree.m_root);
	cout << "insertando 5:\n";
	cin >> xd;
	Tree.insert(5);
	Tree.printTree(Tree.m_root);
	cout << "insertando 6: \n";
	cin >> xd;
	Tree.insert(6);
	Tree.printTree(Tree.m_root);
	cout << "6 insertado\n";
	//cin >> xd;
	//Tree.printTree(Tree.m_root);
	return 0;
}
