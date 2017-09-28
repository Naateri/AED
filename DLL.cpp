//Ordered non-repeated values Double Linked List

#include <iostream>
using namespace std;

template <class T>
class DoubleNode{
public:
	T val;
	DoubleNode* prev;
	DoubleNode* next;
	DoubleNode(DoubleNode<T>* nxt, DoubleNode<T>* prv, T x);
	DoubleNode(T x, DoubleNode<T>* nxt);
};

template <class T>
DoubleNode<T>::DoubleNode(DoubleNode<T>* nxt, DoubleNode<T>* prv, T x){
	this->next = nxt;
	this->prev = prv;
	this->val = x;
}

template <class T>
DoubleNode<T>::DoubleNode(T x, DoubleNode<T>* nxt){
	this->val = x;
	this->next = nxt;
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
	void printByHead();
	void printByTail();
};

template <class T>
DLL<T>::DLL(){
	this->head = 0;
	this->tail = 0;
}

template <class T>
bool DLL<T>::find(T x, DoubleNode<T>**& p, DoubleNode<T>**& q){
	for (p = &head; (*p) && ((*p)->val < x); p = &(*p)->next);
	for (q = &(tail); (*q) && ((*q)->val > x); q = &(*q)->prev);
	return (*p && (*p)->val == x);
}

template <class T>
bool DLL<T>::add(T x){
	DoubleNode<T>** p, **q;
	if(find(x, p, q)) return 0;
	(*p) = new DoubleNode<T>(x, *p);
	(*p)->prev = *q;
	*q = *p;
	return 1;
}

template <class T>
bool DLL<T>::remove(T x){
	DoubleNode<T>** p, **q;
	if (!find(x, p, q)) return 0;
	cout << "Borrando " << x << ":\n";
	DoubleNode<T>* temp = ((*p)->next), *tempPrev = ((*q)->prev);
	delete *p;
	*p = temp;
	*q = tempPrev;
	return 1;
}

template <class T>
void DLL<T>::printByHead(){
	DoubleNode<T>* h;// = head;
	for(h = head; h; h = h->next)
		cout << h->val << " ";
	cout << endl;
}

template <class T>
void DLL<T>::printByTail(){
	DoubleNode<T>* h;// = head;
	for(h = tail; h; h = h->prev)
		cout << h->val << " ";
	cout << endl;
}

int main(int argc, char *argv[]) {
	DLL<int> A;
	A.add(5);
	A.printByHead();
	A.printByTail();
	A.add(8);
	//A.print();
	A.add(10);
	A.add(12);
	A.printByHead();
	A.printByTail();
	A.add(1);
	A.printByHead();
	A.printByTail();
	A.add(7);
	A.printByHead();
	A.printByTail();
	cout << "Borrado:\n";
	A.remove(8);
	A.printByHead();
	A.printByTail();
	A.remove(1);
	A.printByHead();
	A.printByTail();
	A.remove(12);
	A.printByHead();
	A.printByTail();
	return 0;
}

