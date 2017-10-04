//Examen parcial 2017-01 pregunta 3, using bubblesort 

#include <iostream>
using namespace std;

#include <time.h>
#include <stdlib.h>
using namespace std;

template <class T>
T* generarArray(unsigned long long size){
	srand(time(NULL));
	T* ret = new T[size];
	T* a = ret;
	for(int i = 0; i<size; a++, i++){
		*a = T(rand()) % 1000000;
	}
	return ret;
}

template <class T>
void imprimir(T *a, T *b){
	cout << "[";
	for(; a < b; a++){
		cout << *a << ",";
	}
	cout << "]" << endl;
}


template <class T>
void swap(T *p, T *q){
	T temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

template <class T, class O>
class CXSortFunctor{
private:
	O method;
public:
	void Sort(T *a, T *b){
		T *a0, *a1, *a_b; //a_b = a beginning
		a_b = a;
		bool status = true;
		while (status){
			status = false;
			a0 = a; a1 = (a0 + 1);
			for(a; a < b; a++){
				if (method(*a0, *a1)){
					swap(a0, a1);
					status = true;
				}
				a0 = a1;
				a1 = (a1+1);
			}
			a = a_b;
			b--;
		}
	}
};

template <class T>
class MenorFunctor{
public: 
	bool operator()(T a, T b){return a<b;}
};

template <class T>
class CXSortPoly{
public:
	virtual bool cmp(T a, T b) = 0;
	void Sort(T *a, T *b){
		T *a0, *a1, *a_b; //a_b = a beginning
		a_b = a;
		bool status = true;
		while (status){
			status = false;
			a0 = a; a1 = (a0 + 1);
			for(a; a < b; a++){
				if (cmp(*a0, *a1)){
					swap(a0, a1);
					status = true;
				}
				a0 = a1;
				a1 = (a1+1);
			}
			a = a_b;
			b--;
		}
	}
};

template <class T>
class MayorPoly: public CXSortPoly<T>{
	bool cmp(T a, T b){
		return a > b;
	}
};

template <class T>
class MenorPoly: public CXSortPoly<T>{
	bool cmp(T a, T b){ return a<b; }
};

template <class T>
class Methods{
public:
	bool menor(T a, T b){ return a<b; }
};

template <class T>
class CXSortPtoMet{
public:
	void Sort(T *a, T *b, Methods<T>* method, bool (Methods<T>::*someMethod)(T, T)){
		T *a0, *a1, *a_b; //a_b = a beginning
		a_b = a;
		bool status = true;
		while (status){
			status = false;
			a0 = a; a1 = (a0 + 1);
			for(a; a < b; a++){
				if ((method->*someMethod)(*a0, *a1)){
					swap(a0, a1);
					status = true;
				}
				a0 = a1;
				a1 = (a1+1);
			}
			a = a_b;
			b--;
		}
	}
};

int main(int argc, char *argv[]) {
	int *a;
	///MAIN FUNCTOR
	a = generarArray<int>(100);
	CXSortFunctor<int, MenorFunctor<int> > Ej;
	Ej.Sort(a, a+100);
	imprimir<int>(a, a+100);
	delete a;
	///MAIN POLYMORPHISM
	int *b;
	CXSortPoly<int>* Ej2 = new MenorPoly<int>;
	b = generarArray<int>(100);
	Ej2->Sort(b, b+100);
	imprimir<int>(b, b+100);
	delete b;
	///MAIN POINTER TO METHOD
	int *c;
	c = generarArray<int>(100);
	CXSortPtoMet<int> Ej3;
	Methods<int> *Method;
	Ej3.Sort(c, c+100, Method, &Methods<int>::menor);
	imprimir<int>(c, c+100);
	delete c;
	return 0;
}

