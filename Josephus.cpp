#include <iostream>
using namespace std;

template <class T>
struct CNode{
	CNode<T>* next;
	CNode<T>* prev;
	T m_x;
	CNode(T x){
		m_x = x;
		next = prev = this;
	}
};

template <class T>
class DList{
	CNode<T>* head;
	CNode<T>* tail;
public:
	DList();
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void print();
};

template <class T>
DList<T>::DList(){
	this->head = this->tail = 0;
}

template <class T>
bool DList<T>::find(T x, CNode<T>**& p){
	for (p = &(head->next); *p !=head && (*p)->m_x != x; p = &((*p)->next));
	cout << "*p val: " << (*p)->m_x << " ";
	return *p && (*p)->m_x == x;
}

template <class T>
bool DList<T>::insert(T x){
	if(!head){
		head = new CNode<T>(x);
		return 1;
	} else {
		CNode<T>** p;
		if(find(x,p)) return 0;
		CNode<T>* newNode = new CNode<T>(x);
		newNode->next = *p;
		*p = newNode;
		return 1;
	}
}

template <class T>
bool DList<T>::remove(T x){
	CNode<T>** p;
	if(!find(x,p)) return 0;
	cout << "*p val: " << (*p)->m_x << " ";
	p = &(*p)->next;
	if(head->m_x == x){
		head = head->next;
	}
	delete *p;
	return 1;
}

template <class T>
void DList<T>::print(){
	CNode<T>* temp = (head->next);
	for( ; temp != head ; temp = temp->next ){
		cout << (temp)->m_x << " "; 
	}
	cout << (temp)->m_x << endl;
}

int main(int argc, char *argv[]) {
	DList<int> A;
	A.insert(1);
	A.insert(2);
	A.insert(3);
	A.insert(7);
	A.insert(5);
	A.remove(7);
	A.print();
	return 0;
}

