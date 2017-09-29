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
	void erase2();
public:
	TNode<T>* root;
	BinTree();
	bool find(T x, TNode<T>**& p);
	bool insert(T x);
	bool erase(T x);
	void preorder();
	void inorder(TNode<T>* cur);
	void postorder();
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
bool BinTree<T>::erase(T x){
	TNode<T> **p;
	if (!find(x, p)) return 0;
	if ( !(*p)->left && !(*p)->right){
		erase0(p);
	} else if ( (!(*p)->left && (*p)->right) || (!(*p)->right && (*p)->left)){
		erase1(p);
	}
	return 1;
}

template <class T>
void BinTree<T>::inorder(TNode<T>* cur){
	cout << cur->val << " ";
	if (cur->left) inorder(cur->left);
	if (cur->right) inorder(cur->right);
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
	/*myTree.erase(77);
	myTree.inorder(myTree.root);
	cout << endl;*/
	myTree.erase(94);
	myTree.inorder(myTree.root);
	cout << endl;
	return 0;
}

