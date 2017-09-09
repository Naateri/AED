#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template <class T>
T* generarArray(T *a, T *b, int size){
	srand(time(NULL));
	T* ret = new T[size];
	a = ret;
	for(; a<b; a++){
		*a = T(rand()%1000000);
		cout << "a: " << *a << endl;
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
void swap(T &p, T &q){
	T temp;
	temp = p;
	p = q;
	q = temp;
}

template <class T>
bool mayor(T a, T b){
	return a > b;
}

template <class T>
bool menor(T a, T b){
	return a < b;
}

template <class T>
void cocktail(T *a, T *fin, bool (*p) (T, T)){
	T *aux;
	aux = a;
	bool compro = 1;
	while (compro){
		compro = 0;
		for(; a < fin; a++){
			if(p(*a, *(a+1))){
				swap(*a, *(a+1));
				compro = 1;
			}
		}
		for(; fin != aux; fin--){
			if(!(p(*fin, *(fin-1)))){
				swap(*fin, *(fin-1));
				compro = 1;
			}
		}
		swap(a,fin);
		a++;
		fin--;
	}
}

int main(int argc, char *argv[]) {
	long* array1000;
	array1000 = generarArray(array1000, array1000+1000, 1000);
	imprimir(array1000, array1000+1000);
	return 0;
}

