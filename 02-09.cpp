#include <iostream>
using namespace std;

template <class T> class Node{
public:
	T val;
	Node<T>* next;
	Node(T a, Node<T>* n);
};

template <class T> Node<T>::Node(T a, Node<T> *n){
	this->val = a;
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
	LinkedList(T);
	void imprimir();
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

template <class T>
LinkedList<T>::LinkedList(T a){
	Node<T> *first = new Node<T>(a, NULL);
	this->head = first;
	//this->head->next = NULL;
}

template <class T>
bool LinkedList<T>::buscar(T a, Node<T>**& p){
	Node<T>** t;
	t = &(this->head);
	//Node<T>** prev;
	//prev = &(this->head);
	//t = &(*t)->next;
	//cout << "prev: " << prev << endl;
	cout << "t: " << t << endl;
	while((*t)->next != NULL && (*t)->val < a){
		//prev = &(*prev)->next;
		t = &(*t)->next;
		cout << "t while: " << t << endl;
	}
	p = &(*t)->next;
	//cout << "nodo con valor " <<(*prev)->val << " previo apunta a " << (*t)->val << endl;
	if ((*t) != NULL && (*t)->val == a) return true;
	else return false;
}

template <class T>
void LinkedList<T>::insertar(T a){
	Node<T> **p;
	cout << "Insertando " << a << endl;
	cout << "head: " << &head << endl;
	bool busq = this->buscar(a, p);
	cout << "p: " << p << endl;
	if(!busq){
		//Node<T> *value;
		//value = new Node<T>(a, (*p));
		*p = new Node<T>(a, *p);
	}
}

template <class T>
void LinkedList<T>::imprimir(){
	Node<T>* t = this->head;
	//cout << t->val << " ";
	while(t->next != NULL){
		cout << t->val << " ";
		t = t->next;
	}
	cout << t->val << endl;
	//cout << t->val << " ";
}


int main(int argc, char *argv[]) {
	/*Node<int> *a = new Node<int>(5, NULL); 
	Node<int> *b = new Node<int>(4, a);
	Node<int> **c = &(b->next); //puntero al enlace
	cout << a->val << endl;
	if (a->next == NULL) cout << "xd\n";
	cout << (b->next) << endl; //direccion de b->next = a
	cout << a << endl; // direccion de a
	cout << *c << endl; //direccion de b->next 
	cout << c << endl; //direccion del puntero al que apunta b->next (**)
	cout << &(b->next) << endl; //direccion de memoria del puntero a b->next*/
	LinkedList<long> A(1L);
	A.imprimir();
	//int a[] = {1, 2, 3, 4, 5};
	//A.insertar(1L);
	A.insertar(2L);
	A.insertar(3L);
	A.insertar(5L);
	//A.insertar(4L);
	//A.insertar(0L);
	for(long i = 6; i < 16; i+=3){
		A.insertar(i);
	}
	A.insertar(8L);
	A.imprimir();
	return 0;
}

