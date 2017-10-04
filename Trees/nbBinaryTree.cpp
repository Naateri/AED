//NonBalanced Binary Tree

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
private:
	void erase0(TNode<T>**& p);
	void erase1(TNode<T>**& p);
	void erase2(TNode<T>**& p);
public:
	TNode<T>* root;
	BinTree();
	bool find(T x, TNode<T>**& p);
	bool insert(T x);
	bool erase(T x);
	void preorder(TNode<T>* cur);
	void inorder(TNode<T>* cur);
	void postorder(TNode<T>* cur);
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
void BinTree<T>::erase0(TNode<T>**& p){
	delete *p;
	*p = 0;
}

template <class T>
void BinTree<T>::erase1(TNode<T>**& p){
	TNode<T>* temp;
	if ((*p)->right){ 
		temp = (*p)->right;
	} else {
		temp = (*p)->left;
	}
	delete *p;
	(*p) = temp;
}

template <class T>
void BinTree<T>::erase2(TNode<T>**& p){
	TNode<T>* temp, **tmp;
	T tempVal;
	temp = (*p)->left;
	while ( temp->right ){
		temp = temp->right;
	}
	tempVal = (*p)->val;
	(*p)->val = temp->val;
	temp->val = tempVal;
	tmp = &temp;
	if ( !(temp)->left ){
		erase0(tmp);
	} else {
		erase1(tmp);
	}
}

template <class T>
bool BinTree<T>::erase(T x){
	TNode<T> **p;
	if (!find(x, p)) return 0;
	if ((*p)->right){
		if((*p)->left){ //tiene 2 hijos
			TNode<T> **tmp;
			T tempVal;
			tmp = &(*p)->left;
			while ( (*tmp)->right ){
				tmp = &(*tmp)->right;
			}
			tempVal = (*p)->val;
			(*p)->val = (*tmp)->val;
			(*tmp)->val = tempVal;
			if ((*tmp)->left){
				delete *tmp;
				*tmp = (*tmp)->left;
			} else {
				delete *tmp;
				*tmp = 0;
			}
		} else { //solo tiene el hijo derecho
			TNode<T>* temp;
			temp = (*p)->right;
			delete *p;
			*p = temp;
		}
	} else {
		if (!((*p)->right)){ //solo tiene el hijo izquierdo
			TNode<T>* temp;
			temp = (*p)->left;
			delete *p;
			*p = temp;
		} else { //no tiene hijos
			delete *p;
			*p = 0;
		}
	}
	return 1;
}

template <class T>
void BinTree<T>::inorder(TNode<T>* cur){
	cout << cur->val << " ";
	if (cur->left) inorder(cur->left);
	if (cur->right) inorder(cur->right);
}

template <class T>
void BinTree<T>::postorder(TNode<T>* cur){
	if (cur->left) postorder(cur->left);
	if (cur->right) postorder(cur->right);
	cout << cur->val << " ";
}

int main(int argc, char *argv[]) {
	BinTree<int> myTree;
	myTree.insert(51);
	myTree.insert(42);
	myTree.insert(80);
	myTree.insert(20);
	myTree.insert(47);
	myTree.insert(77);
	myTree.insert(94);
	myTree.insert(95);
	myTree.inorder(myTree.root);
	cout << endl;
	myTree.erase(77);
	myTree.inorder(myTree.root);
	cout << endl;
	myTree.erase(51);
	myTree.inorder(myTree.root);
	cout << endl;
	return 0;
}

