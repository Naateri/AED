#include <iostream>
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

template <class T>
void insertionSort(T *a, T *b){
	T *a0, *aux;
	T x;
	b++;
	a0 = a+1;
	for(a0; a0 < b; a0++){
		x = *a0;
		aux = a0;
		while (( (aux) > a) && ( *(aux - 1) > x)){
			*aux = *(aux - 1);
			aux--;
		}
		*aux = x;
	}
}

template <class T>
class Methods{
public:
	bool mayor(T a, T b){ return a>b; }
	bool menor(T a, T b){ return a<b; }
};

template <class T>
class CXSort{
public:
	void Sort(T *a, T *fin, Methods<T>* method, bool(Methods<T>::*theMethod)(T, T)){
		T *aux;
		aux = a;
		bool compro = 1;
		T *auxF = fin;
		while (compro){
			compro = 0;
			for(a; a < fin; a++){
				if((method->*theMethod)(*a, *(a+1))){
					swap<T>(*a, *(a+1));
					compro = 1;
				}
			}
			for(a; fin != aux; fin--){
				if(!(method->*theMethod)(*fin, *(fin-1))){
					swap<T>(*fin, *(fin-1));
					compro = 1;
				}
			}
			swap<T>(*a,*fin);
			aux++;
			a = aux;
			auxF--;
			fin = auxF;
		}
	}
};
int main(int argc, char *argv[]) {
	Methods<int> something;
	CXSort<int> Lel;
	int a1[10] = {56, 23, 462, 312, 3521, 2, 53, 942, 1, 10};
	int *a = generarArray<int>(100);
	imprimir<int>(a, a+100);
	Lel.Sort(a, a+50, &something, &Methods<int>::menor);
	imprimir<int>(a, a+100);
	delete a;
	imprimir<int>(a1, a1+10);
	Lel.Sort(a1, a1+10, &something, &Methods<int>::mayor);
	imprimir<int>(a1, a1+10);
	return 0;
}

