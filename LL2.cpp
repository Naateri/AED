//Circular Linked List

#include <iostream>
using namespace std;

template <class T>
class CircularNode{
public:
	T val;
	CircularNode *next;
	CircularNode(T x, CircularNode<T>* nxt);
};

template <class T>
CircularNode<T>::CircularNode(T x, CircularNode<T>* nxt){
	this->val = x;
	this->next = nxt;
}

template <class T>
class CircularLinkedList{
private:
	CircularNode<T> *head;
	CircularNode<T> **headPrev;
public:
	CircularLinkedList();
	CircularLinkedList(T x);
	bool buscar(T x, CircularNode<T>**& p);
	bool insertar(T x);
	bool borrar(T x);
	void imprimir();
};

template <class T>
CircularLinkedList<T>::CircularLinkedList(){
	this->head = NULL;
	//CircularNode<T> lol = CircularNode<T>(0, head); 
	//this->headPrev = lol;.
}

template <class T>
CircularLinkedList<T>::CircularLinkedList(T x){
	this->head = new CircularLinkedList<T>(x, head);
}

template <class T>
bool CircularLinkedList<T>::buscar(T x, CircularNode<T>**& p){
	bool aux = 1; //1 si no ha pasado por head, 0 si ya paso por head
	p = &head;
	if (*p == NULL) return 0;
	while (*p && (*p != this->head || aux) && ((*p)->val != x)){
		p = &((*p)->next);
		aux = 0;
	}
	return ((*p) && (*p)->val == x);
}

template <class T>
bool CircularLinkedList<T>::insertar(T x){
	CircularNode<T> **p;
	if(!buscar(x, p)){
		*p = new CircularNode<T>(x, head);
		headPrev = &(*p)/*->next*/;
		return 1;
	}
	return 0;
}

template <class T>
bool CircularLinkedList<T>::borrar(T x){
	CircularNode<T> **p;
	cout << "Borrando: " << x << endl;
	if(buscar(x, p)){
		CircularNode<T>* temp = (*p)->next;
		/*cout << "headPrev: " << *headPrev << endl;
		cout << "Head: " << head << endl;*/
		delete *p;
		/*cout << "Borrado.\n";
		cout << "Head: " << head << endl;*/
		*p = temp;
		(*headPrev) = head;
		/*cout << "headPrev: " << headPrev << endl;
		cout << "*headPrev: " << *headPrev << endl;*/
		return 1;
	}
	return 0;
}

template <class T>
void CircularLinkedList<T>::imprimir(){
	CircularNode<T>* t = head;
	bool aux = 1;
	while ((t) && (t != this->head || aux)){
		cout << (t)->val << " ";
		t = (t)->next;
		aux = 0;
	}
	cout << endl;
}


int main(int argc, char *argv[]) {
	CircularLinkedList<int> A;
	A.insertar(5);
	A.insertar(6);
	A.insertar(2);
	A.insertar(4);
	A.insertar(8);
	A.imprimir();
	//A.borrar(5);
	//A.imprimir();
	A.borrar(8);
	A.imprimir();
	//CircularNode<int> **B;
	//if (A.buscar(5, B)) cout << "1\n";
	/*A.borrar(5);
	A.imprimir();*/
	A.borrar(2);
	A.imprimir();
	A.insertar(69);
	A.insertar(1337);
	A.imprimir();
	A.borrar(1337);
	A.imprimir();
	return 0;
}

