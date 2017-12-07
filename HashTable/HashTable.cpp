#include <iostream>
#include <list>
#include <string>

using namespace std;

template <class T, class F, class E, int size>
class HashTable{
	E m_table[size];
	F m_f;
public:
	bool find(T x, T*& t, int& p);
	bool insert(T x);
	bool remove(T x);
};

template <class T, class F, class E, int size>
bool HashTable<T, F, E, size>::find(T x, T*& t, int& p){
	return m_table[m_f(x) % size].find(x, t, p);
}

template <class T, class F, class E, int size>
bool HashTable<T, F, E, size>::insert(T x){
	return m_table[m_f(x) % size].insert(x);
}

template <class T, class F, class E, int size>
bool HashTable<T, F, E, size>::remove(T x){
	return m_table[m_f(x) % size].remove(x);
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

template <class T, int size>
struct HashFunction{
	T operator()(T x){
		return (x+50) % size;
	}
};

int main(int argc, char *argv[]) {
	int* x, y;
	HashTable<int, HashFunction<int, 5>, CLA<int>, 5> Hash;
	Hash.insert(5);
	Hash.insert(8);
	Hash.insert(9);
	Hash.insert(-3);
	Hash.insert(3);
	Hash.find(15, x, y);
	cout << *x << endl;
	return 0;
}

