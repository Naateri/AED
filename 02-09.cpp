#include <iostream>
using namespace std;

template <class T> class Node{
public:
	T dato;
	Node<T>* next;
	Node(T a, Node<T>* n);
};

template <class T> Node<T>::Node(T a, Node<T> *n){
	this->dato = a;
	this->next = n;
}

//*p = new node(a, **p); insertando nodo en una sola linea 

//*p = Node
//**p = node->next
//***p = &(nodo->next) 

template <class T> class LinkedList{
private:
	Node<T> *head;
public:
	LinkedList();
	//bool buscar(T a); //si quiero insertar, tendré que buscar otra vez
	//Node<T>* buscar(T a); //si no existe, retorno el nodo anterior para futura inserción
	//bool buscar(T a, Node* pos); //juntar ambos metodos, funciona siempre excepto para el head 
	//pero mejor es situarse en el enlace previo
	//bool buscar(T a, Node*** p); //triple asterisco porque estoy apuntando al next, con 2* no apunto al next 
	//**& -> estoy en la direccion de memoria de ese puntero a puntero
	bool buscar(T a, Node<T>**& p); //Es lo mismo que el buscar anterior, pero queda lo mismo y me ahorro 4 bytes
	void insertar(T a);
	void borrar(T a);
};


int main(int argc, char *argv[]) {
	Node<int> *a = new Node<int>(5, NULL); 
	Node<int> *b = new Node<int>(4, a);
	Node<int> **c = &(b->next); //puntero al enlace
	cout << a->dato << endl;
	if (a->next == NULL) cout << "xd\n";
	cout << (b->next) << endl; //direccion de b->next = a
	cout << a << endl; // direccion de a
	cout << *c << endl; //direccion de b->next 
	cout << c << endl; //direccion del puntero al que apunta b->next (**)
	cout << &(b->next) << endl; //direccion de memoria del puntero a b->next
	return 0;
}

