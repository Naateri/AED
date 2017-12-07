#include <iostream>
#include <list>
using namespace std;

template <class T, int size>
class Functions{
public:
	T f1(T x){
		return (x+50) % size;
	}
};

template <class T, class E, int size>
class HashTable{
	E m_table[size];
	T(Functions<T, size>::*theMethod)(T);
	Functions<T, size>* m_f;
public:
	HashTable(Functions<T,size>* m_f, T(Functions<T,size>::*method)(T));
	bool find(T x, T*& t, int& p);
	bool insert(T x);
	bool remove(T x);
};

template <class T, class E, int size>
HashTable<T, E, size>::HashTable(Functions<T,size>* m_f, T(Functions<T,size>::*method)(T)){
	this->m_f = m_f;
	this->theMethod = method;
}

template <class T, class E, int size>
bool HashTable<T, E, size>::find(T x, T*& t, int& p){
	return m_table[(m_f->*theMethod)(x) % size].find(x, t, p);
}

template <class T, class E, int size>
bool HashTable<T, E, size>::insert(T x){
	return m_table[(m_f->*theMethod)(x) % size].insert(x);
}

template <class T, class E, int size>
bool HashTable<T, E, size>::remove(T x){
	return m_table[(m_f->*theMethod)(x) % size].remove(x);
}

template <class T>
class CLA{
	list<T> m_list;
public:
	bool find(T x, T*& t, int& p);
	bool insert(T x);
	bool remove(T x);
	void print(){
		for(typename list<T>::iterator it = m_list.begin(); it != m_list.end(); it++){
			cout << (*it) << " ";
		}
		cout << endl;
	}
};

template <class T>
bool CLA<T>::find(T x, T*& t, int& p){
	if (m_list.empty() ) return 0;
	typename list<T>::iterator it = m_list.begin();
	p = 0;
	for( ; it != m_list.end() && (*it) != x; it++, p++){
		;
	}
	t = &(*it);
	if (*t != x) *t = 0;
	return (x == *it);
}

template <class T>
bool CLA<T>::insert(T x){
	int p;
	T* temp;
	if (find (x, temp, p) ) return 0;
	m_list.push_back(x);
	return 1;
}

template <class T>
bool CLA<T>::remove(T x){
	int p;
	T* temp;
	if (!find(x, temp, p) ) return 0;
	m_list.remove(m_list.begin() + p);
	return 1;
}


int main(int argc, char *argv[]) {
	Functions<int, 5> Something;
	int *x, y;
	HashTable<int, CLA<int>, 5> Hash(&Something, &Functions<int, 5>::f1);
	Hash.insert(5);
	Hash.insert(8);
	Hash.insert(9);
	Hash.insert(-3);
	Hash.insert(3);
	Hash.find(-3, x, y);
	cout << *x << endl;
	return 0;
}

