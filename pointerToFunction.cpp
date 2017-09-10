#include <iostream>
#include <stdlib.h>
#include <time.h>

//unsigned long long int can store up to 19 digit numbers

using namespace std;

template <class T>
T* generarArray(int size){
	srand(time(NULL));
	T* ret = new T[size];
	T* a = ret;
	for(int i = 0; i<size; a++, i++){
		*a = T(rand());
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
	T* temp;
	*temp = *p;
	*p = *q;
	*q = *temp;
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
		cout << "bucleee\n";
		compro = 0;
		for(a; a < fin; a++){
			cout << "fooooor1\n";
			if(p(*a, *(a+1))){
				cout << "swaaaaaaaaaap1\n";
				swap<T>(*a, *(a+1));
				compro = 1;
			}
		}
		for(a; fin != aux; fin--){
			cout << "foooor2\n";
			if(!(p(*fin, *(fin-1)))){
				swap<T>(*fin, *(fin-1));
				compro = 1;
			}
		}
		cout << "FUERA FORSSSS\n";
		swap<T>(*a,*fin);
		a++;
		fin--;
	}
}

int main(int argc, char *argv[]) {
	int* array1000 = generarArray<int>(1000);
	bool (*p) (int, int) = &menor<int>;
	//p = menor<int>;
	imprimir<int>(array1000, array1000+999);
	cocktail<int>(array1000, array1000+999, p);
	delete array1000;
	return 0;
}

