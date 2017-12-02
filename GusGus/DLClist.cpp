#include "DLClist.h"

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
	size++;
	return 1;
}

template <class T>
bool DList<T>::remove(T x){
	if (head == head->next){ //only 1 element left
		delete head;
		head = tail = 0;
		return 0;
	}
	CNode<T>* p;
	if(!find(x,p)) return 0;
	if (p == head){
		head = (p)->next;
		head->prev = tail;
		tail->next = head;
	} else if (p == tail){
		tail = (p)->prev;
		tail->next = head;
		head->prev = tail;
	} else {
		(p)->prev->next = (p)->next;
		(p)->next->prev = (p)->prev;
	}
	delete p;
	size--;
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

template <class T>
void DList<T>::Josephus(int soldiers, int gap){
	for(int i = 0; i < soldiers; i++){
		insert(i);
	}
	CNode<int>* temp = head;
	int tmp;
	while(size > 2){
		for(int i = 0; i < gap-1; i++){
			temp = temp->next;
		}
		tmp = temp->m_x;
		temp = temp->next; //para no perder los enlaces
		cout << "Muere: " << tmp << endl; 
		remove(tmp);
	}
	cout << "Sobreviven: ";
	print();
}
