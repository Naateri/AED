//Ordered non-repeated values Double Linked List

#include <iostream>
using namespace std;

template <class T>
class DoubleNode{
public:
	T val;
	DoubleNode* prev;
	DoubleNode* next;
	DoubleNode(DoubleNode<T>* nxt, T x);
};

template <class T>
DoubleNode<T>::DoubleNode(DoubleNode<T>* nxt, T x){
	this->next = nxt;
	this->val = x;
}

template <class T>
class DLL{
private:
	DoubleNode<T>* head;
	DoubleNode<T>* tail;
public:
	DLL();
	bool find(T x, DoubleNode<T>**& p);
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
bool DLL<T>::find(T x, DoubleNode<T>**& p){
	for (p = &head; (*p) && ((*p)->val < x); p = &(*p)->next);
	return (*p && (*p)->val == x);
}

template <class T>
bool DLL<T>::add(T x){
	DoubleNode<T>** p;
	if(find(x, p)) return 0;
	*p = new DoubleNode<T>((*p), x);
	if ( (*p)->next == NULL ){
		tail = *p;
	}
	if ( !((*p)->prev)) (*p)->prev = NULL;
	return 1;
}

template <class T>
bool DLL<T>::remove(T x){
	DoubleNode<T>** p;
	if (!find(x, p)) return 0;
	DoubleNode<T>* temp = ((*p)->next);
	if (!temp) tail = (*p)->next;
	delete *p;
	*p = temp;
}

template <class T>
void DLL<T>::print(){
	DoubleNode<T>* h;// = head;
	//cout << "Head: " << head << endl;
	for(h = head; h; h = h->next)
		cout << h->val << " ";
	cout << endl;
	/*for(h = tail; h; h = h->prev)
	cout << h->val << " ";*/
}


int main(int argc, char *argv[]) {
	DLL<int> A;
	A.add(5);
	A.print();
	A.add(8);
	//A.print();
	A.add(10);
	A.add(12);
	A.add(1);
	A.print();
	A.add(7);
	A.print();
	A.remove(8);
	A.print();
	A.remove(1);
	A.print();
	A.remove(12);
	A.print();
	return 0;
}

