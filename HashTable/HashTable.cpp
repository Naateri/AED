#include <iostream>
#include <list>
#include <string>

using namespace std;

template <class T, class F, class E, int size>
class HashTable{
	E m_table[size];
	F m_f;
public:
	T* find(T x);
	bool insert(T x);
	bool remove(T x);
};

template <class T, class F, class E, int size>
T* HashTable<T, F, E, size>::find(T x){
	m_table[m_f(x) % size].print();
	return m_table[m_f(x) % size].find(x);
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
	T* find(T x);
	bool insert(T x);
	bool remove(T x);
	void print(){
		for(typename list<T>::iterator it = m_list.begin(); it != m_list.end(); it++){
			cout << (*it) << " ";
		}
	}
};

template <class T>
T* CLA<T>::find(T x){
	typename list<T>::iterator it = m_list.begin();
	T x1;
	cout << "m_list.begin(): " << *(m_list.begin()) << endl;
	for( ; it != m_list.end() && (*it) != x; it++){
		cout << "*it: " << *it << endl;
	}
	x = *it;
	if (x) return &x;
	return 0;
}

template <class T>
bool CLA<T>::insert(T x){
	if (find (x) ) return 0;
	m_list.push_back(x);
}


struct Person{
	string first_name;
	string last_name;
	int age;
	ostream& operator<< (ostream& out){
		out << "Name: " << first_name << " " << last_name << endl;
		out << "Age: " << age << endl;
		return out;
	}
	Person(string fn, string ln, int ag){
		this->first_name = fn;
		this->last_name = ln;
		this->age = ag;
	}
};

template <int size>
struct HashFunction{
	int operator()(int x){
		return (x+50) % size;
	}
};

int main(int argc, char *argv[]) {
	int *x;
	HashTable<int, HashFunction<13>, CLA<int>, 13> Hash;
	Hash.insert(5);
	Hash.insert(8);
	cout << "Ma find\n";
	cout << Hash.find(5);
	return 0;
}

