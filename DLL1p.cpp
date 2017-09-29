//Ordered non-repeated values Double Linked List single pointer 

#include <iostream>
using namespace std;

template <class T>
class DoubleNode{
public:
	T val;
	DoubleNode* prev;
	DoubleNode* next;
	DoubleNode(DoubleNode<T>* nxt, DoubleNode<T>* prv, T x);
	DoubleNode(T x);
};

template <class T>
DoubleNode<T>::DoubleNode(DoubleNode<T>* nxt, DoubleNode<T>* prv, T x){
	this->next = nxt;
	this->prev = prv;
	this->val = x;
}

template <class T>
DoubleNode<T>::DoubleNode(T x){
	this->val = x;
}

template <class T>
class DLL{
private:
	DoubleNode<T>* head;
	DoubleNode<T>* tail;
public:
	DLL();
	bool find(T x, DoubleNode<T>*& p);
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
bool DLL<T>::find(T x, DoubleNode<T>*& p){
	p = head;
	while (p && p->next && p->val < x){
		p = p->next;
	}
	return (p && (p)->val == x);
}

template <class T>
bool DLL<T>::add(T x){
	DoubleNode<T>* p, *q;
	if(find(x, p)) return 0;
	q = new DoubleNode<T>(x);
	if (!head){
		head = q;
		tail = q;
		q->prev = NULL;
		q->next = NULL;
	} else {
		if (!(p->next)){ ///p->next es nulo, insercion al final
			tail = q;
			q->next = p->next;
			p->next = q;
			q->prev = p;
		} else if (!(p->prev)){ ///p->prev es nulo, insercion al comienzo
			head = q;
			q->prev = p->prev;
			p->prev = q;
			q->next = p;
		} else { ///insercion al medio
			q->next = p;
			q->prev = p->prev;
			q->prev->next = q;
			p->prev = q;
		}
	}
	return 1;
}
template <class T>
bool DLL<T>::remove(T x){
	DoubleNode<T>* p;
	if (!find(x, p)) return 0;
	cout << "Borrando " << x << ":\n";
	DoubleNode<T>* temp;
	if (p == head){ ///borrado de la cabeza
		temp = p->next;
		delete p;
		head = temp;
		temp->prev = NULL;
	} else if (p == tail){ ///borrado al final
		temp = p->prev;
		delete p;
		tail = temp;
		temp->next = NULL;
	} else { ///borrado al medio
		temp = p->next;
		p->prev->next = temp;
		temp->prev = p->prev;
		delete p;
	}
	return 1;
}

template <class T>
void DLL<T>::printByHead(){
	DoubleNode<T>* h;
	for(h = head; h; h = h->next)
		cout << h->val << " ";
	cout << endl;
}

template <class T>
void DLL<T>::printByTail(){
	DoubleNode<T>* h;
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
	A.add(9);
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

