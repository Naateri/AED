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
	bool find(T x, CNode<T>*& p);
	bool insert(T x);
	bool remove(T x);
	void print();
};

template <class T>
DList<T>::DList(){
	this->head = this->tail = 0;
}

template <class T>
bool DList<T>::find(T x, CNode<T>*& p){
	if (!head) return 0;
	for (p = (head); ((p)->m_x) < ((p)->next->m_x) && (p)->m_x < x; p = (p)->next); //if prev node value < cur node value
	return (p)->m_x == x;
}

template <class T>
bool DList<T>::insert(T x){
	if(!head){
		head = new CNode<T>(x);
		tail = head;
	} else {
		CNode<T>* p;
		if(find(x,p)) return 0;
		CNode<T>* newNode = new CNode<T>(x);
		if (p == tail){ //insertion at the end
			if (p->m_x < x){
				newNode->next = head;
				p->next = newNode;
				newNode->prev = p;
				head->prev = newNode;
				tail = newNode;
			} else {
				newNode->next = p;
				newNode->prev = p->prev;
				p->prev->next = newNode;
				p->prev = newNode;
			}
		}
		else if (p == head){ //insertion at the beginning
			newNode->next = p;
			newNode->prev = tail;
			p->prev = newNode;
			head = newNode;
			tail->next = newNode;
		} else { //insertion at the middle 
			newNode->next = p;
			newNode->prev = p->prev;
			p->prev->next = newNode;
			p->prev = newNode;
		}
	}
	return 1;
}

template <class T>
bool DList<T>::remove(T x){
	CNode<T>* p;
	if(!find(x,p)) return 0;
	p = (p)->next;
	if(head->m_x == x){
		head = head->next;
	}
	delete p;
	return 1;
}

template <class T>
void DList<T>::print(){
	if (!head) cout << endl;
	else {
		CNode<T>* temp;
	for(temp = head; ((temp)->m_x) < ((temp)->next->m_x) ; temp = temp->next ){
		cout << (temp)->m_x << " "; 
	}
	cout << (temp)->m_x << endl;
	}
}

int main(int argc, char *argv[]) {
	DList<int> A;
	A.insert(1);
	A.insert(3);
	A.print();
	A.insert(5);
	A.print();
	A.insert(7);
	A.print();
	A.insert(6);
	A.print();
	A.insert(2);
	//A.remove(7);
	A.print();
	A.insert(0);
	A.print();
	return 0;
}

