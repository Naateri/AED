//Linked List with a single pointer

#include <iostream>
using namespace std;

template <class T> class Node{
public:
	T val;
	Node<T>* next;
	Node(T val);
	Node(T a, Node<T>* n);
};

template <class T> Node<T>::Node(T a, Node<T> *n){
	this->val = a;
	this->next = n;
}

template <class T>
Node<T>::Node(T val){
	this->val = val;
	this->next = NULL;
} 

template <class T> class LinkedList{
private:
	Node<T> *head;
public:
	LinkedList(T);
	LinkedList();
	void imprimir();
	bool buscar(T a, Node<T>*& prev); 
	void insertar(T a);
	void borrar(T a);
};

template <class T>
LinkedList<T>::LinkedList(T a){
	Node<T> *first = new Node<T>(a, NULL);
	this->head = first;
	//this->head->next = NULL;
}

template <class T>
LinkedList<T>::LinkedList(){
	this->head = NULL;
}

template <class T>
bool LinkedList<T>::buscar(T a, Node<T>*& prev){
	Node<T> *p = head;
	prev = head;
	if (p && p->val < a){
		p = p->next;
	}
	while(p && (p->val < a)){
		p = p->next;
		prev = prev->next;
	}
	return (p && p->val == a);
}

template <class T>
void LinkedList<T>::insertar(T a){
	Node<T> *prev;
	bool busq = this->buscar(a, prev);
	if (!busq){
		Node<T> *nod = new Node<T>(a);
		if (head == NULL){
			this->head = nod;
		} else {
			if (prev != head){
				if (!prev){
					nod->next = NULL;
					prev->next = nod;
				} else {
					nod->next = prev->next;
					prev->next = nod;
				}
			} else {
				if (prev->val > a){
					nod->next = prev;
					//head = nod;
				} else {
					nod->next = prev->next;
					prev->next = nod;
				}
			}
		
		}
	}
}

template <class T>
void LinkedList<T>::imprimir(){
	Node<T>* t = this->head;
	while(t->next != NULL){
		cout << t->val << " ";
		t = t->next;
	}
	cout << t->val << endl;
}

template <class T>
void LinkedList<T>::borrar(T a){
	Node<T> *prev;
	cout << "Borrando: " << a <<"\n";
	bool busq = this->buscar(a, prev);
	if(busq){
		if (prev == head){
			Node<T>* temp = head->next;
			delete head;
			head = temp;
		} else {
			Node<T>* temp = (prev->next->next);
			delete prev->next;
			prev->next = temp;
		}
	} else {
		cout << "El valor " << a << " no existe en la lista.\n";
	}
}

int main(int argc, char *argv[]) {
	LinkedList<long> A;
	for(long i = 3; i < 16; i+=3){
		A.insertar(i);
		A.imprimir();
	}
	A.insertar(8L);
	A.insertar(2L);
	A.insertar(20L);
	A.insertar(20L);
	//A.insertar(-123514L);
	//A.insertar(12356244L);
	A.insertar(0L);
	//A.insertar(6L);
	A.imprimir();
	A.borrar(8L);
	A.imprimir();
	A.borrar(3L);
	A.imprimir();
	A.insertar(-1L);
	A.imprimir();
	A.borrar(20L);
	A.imprimir();
	return 0;
}

