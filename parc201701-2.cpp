///Binary Tree with single pointer 

#include <iostream>

using namespace std;

template <class T>
struct TNode{
	T val;
	TNode* left;
	TNode* right;
};

template <class T>
class BinTree{
public:
	TNode<T>* root;
	BinTree();
	bool find(T x, TNode<T>**& p);
	bool buscar2(TNode<T>*& p, TNode<T>*& prev, T x, bool &prevFlag);
	bool insert(T x);
	bool borrar2(T x);
	void inorder(TNode<T>* cur);
};

template <class T>
BinTree<T>::BinTree(){
	this->root = 0;
}

template <class T>
bool BinTree<T>::find(T x, TNode<T>**& p){
	p = &root;
	while(*p && (*p)->val != x){
		if (x < (*p)->val) p = &(*p)->left;
		else p = &(*p)->right;
	}
	return (*p && (*p)->val == x);
}

template <class T>
bool BinTree<T>::insert(T x){
	TNode<T> **p;
	if (find(x, p)) return 0;
	*p = new TNode<T>;
	(*p)->val = x;
	(*p)->left = 0;
	(*p)->right = 0;
	return 1;
}

template <class T>
bool BinTree<T>::buscar2(TNode<T>*& p, TNode<T>*& prev, T x, bool& prevFlag){
	prev = root;
	p = root;
	while(p && p->val != x){
		prev = p;
		if(p->val < x){
			p = p->right;
			prevFlag = 1;
		} else {
			p = p->left;
			prevFlag = 0;
		}
	}
	return (p && p->val == x);
}

template <class T>
bool BinTree<T>::borrar2(T x){
	TNode<T>* p, *prev;
	bool pflag; //1, prev->right = p, 0, prev->left = p
	if(!buscar2(p, prev, x, pflag)) return 0;
	if (p->right){
		if(p->left){ //tiene ambos hijos
			T temp;
			TNode<T>* mostRight = p->left;
			TNode<T>* mostRightPrev;
			while(mostRight && mostRight->right){
				mostRightPrev = mostRight;
				mostRight = mostRight->right;
			}
			temp = mostRight->val;
			mostRight->val = p->val;
			p->val = temp;
			if(mostRight->left){
				TNode<T>* temp = mostRight->left;
				delete mostRight;
				mostRightPrev->right = temp;
			} else {
				delete mostRight;
				mostRightPrev->right = 0;
			}
		} else { //solo tiene un hijo, el derecho
			TNode<T>* temp = p->right;
			delete p;
			if (pflag) prev->right = temp;
			else prev->left = temp;
		}
	} else {
		if (!(p->right)){ //de nuevo, solo tiene un hijo, el izquierdo
			TNode<T>* temp = p->left;
			delete p;
			if (pflag) prev->right = temp;
			else prev->left = temp;
		} else { //no tiene hijos
			delete p;
			p = 0;
		}
	}
}

template <class T>
void BinTree<T>::inorder(TNode<T>* cur){
	cout << cur->val << " ";
	if (cur->left) inorder(cur->left);
	if (cur->right) inorder(cur->right);
}

int main(int argc, char *argv[]) {
	BinTree<int> X;
	X.insert(23);
	X.insert(10);
	X.insert(25);
	X.insert(5);
	X.insert(11);
	X.insert(24);
	X.insert(27);
	X.inorder(X.root);
	cout << endl;
	X.borrar2(27);
	X.inorder(X.root);
	cout << endl;
	X.borrar2(25);
	X.inorder(X.root);
	cout << endl;
	X.borrar2(23);
	X.inorder(X.root);
	return 0;
}

