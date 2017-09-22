//UNORDERED Double Linked List

#include <iostream>
using namespace std;

template <class T>
class DoubleNode{
public:
	T val;
	DoubleNode* prev;
	DoubleNode* next;
	DoubleNode(DoubleNode<T>* pr, DoubleNode<T>* nxt, T x);
};

template <class T>
DoubleNode<T>::DoubleNode(DoubleNode<T>* pr, DoubleNode<T>* nxt, T x){
	this->prev = pr;
	this->next = next;
	this->val = x;
}

template <class T>
class DLL{
private:
	DoubleNode<T>* head;
	DoubleNode<T>* tail;
public:
	DLL();
	bool find(T x, DoubleNode<T>**& p, DoubleNode<T>**& q);
	bool add(T x);
	bool remove(T x);
	void print();
};

template <class T>
DLL<T>::DLL(){
	this->head = 0;
	this->tail = 0;
}

template <class T>
bool DLL<T>::find(T x, DoubleNode<T>**& p, DoubleNode<T>**& q){
	/*p = head;
	while (p){
		p = p->next;
	}*/
	//DoubleNode<T> *r, *q;
	cout << "B4 4\n";
	for (p = &head; (*p) && ((*p)->val != x); p = &(*p)->next);
	cout << "Out of for\n";
	q = &tail;
	return (*p && (*p)->val == x);
}

template <class T>
bool DLL<T>::add(T x){
	DoubleNode<T>** p, **q;
	if(find(x, p, q)) return 0;
	*p = new DoubleNode<T>((*q), (*p), x);
	//tail = *p;
	return 1;
}

template <class T>
void DLL<T>::print(){
	DoubleNode<T>* h;// = head;
	cout << "Head: " << head << endl;
	for(h = head; h; h = h->next)
		cout << h->val << " ";
	/*for(h = tail; h; h = h->prev)
		cout << h->val << " ";*/
}

int main(int argc, char *argv[]) {
	DLL<int> A;
	A.add(5);
	A.add(6);
	A.add(7);
	A.print();
	return 0;
}

