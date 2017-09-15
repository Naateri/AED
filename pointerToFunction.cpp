#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

//unsigned long long int can store up to 19 digit numbers

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
	T *auxF = fin;
	while (compro){
		compro = 0;
		for(a; a < fin; a++){
			if(p(*a, *(a+1))){
				swap<T>(*a, *(a+1));
				compro = 1;
			}
		}
		for(a; fin != aux; fin--){
			if(!(p(*fin, *(fin-1)))){
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

template <class T>
void a1000Elem(bool (*p) (T, T), double &elapsedTime, ofstream &filexd){
	int* array1000 = generarArray<int>(1000);
	clock_t begin = clock();
	cocktail<int>(array1000, array1000+999, p);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1000 elementos: " << elapsedTime << endl;
	delete array1000;
}

template <class T>
void a100kElem(bool (*p) (T, T), double &elapsedTime, ofstream &filexd){
	int* array100k = generarArray<int>(100000);
	clock_t begin = clock();
	cocktail<int>(array100k, array100k+99999, p);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 elementos: " << elapsedTime << endl;
	delete array100k;
}

template <class T>
void a1MElem(bool (*p) (T, T), double &elapsedTime, ofstream &filexd){
	int* array1M = generarArray<int>(1000000);
	clock_t begin = clock();
	cocktail<int>(array1M, array1M+999999, p);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1 000 000 elementos: " << elapsedTime << endl;
	delete array1M;
}

template <class T>
void a100MElem(bool (*p) (T, T), double &elapsedTime, ofstream &filexd){
	int* array100M = generarArray<int>(100000000);
	clock_t begin = clock();
	cocktail<int>(array100M, array100M+99999999, p);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 000 elementos: " << elapsedTime << endl;
	delete array100M;
}

int main(int argc, char *argv[]) {
	bool (*p) (int, int) = &menor<int>;
	double et, acum = 0;
	ofstream file;
	file.open("timesPtr2Func.txt");
	for(int i = 0; i < 100; i++){
		a1000Elem<int>(p, et, file);
		acum += et;
	}
	cout << "Acabo 1000\n";
	file << "Promedio 1000: " << acum/100 << endl;
	acum = 0;
	for(int i = 0; i < 25; i++){
		a100kElem<int>(p, et, file);
		acum += et;
	}
	cout << "Acabo 100 000\n";
	file << "Promedio 100 000: " << acum/25 << endl;
	acum = 0;
	for(int i = 0; i < 10; i++){
		a1MElem<int>(p, et, file);
		acum += et;
	}
	cout << "Acabo 1 000 000\n";
	file << "Promedio 1 000 000: " << acum/10 << endl;
	acum = 0;
	for (int i = 0; i < 5; i++){
		a100MElem<int>(p, et, file);
		acum += et;
	}
	cout << "Acabo 100 000 000\n";
	file << "Promedio 100 000 000: " << acum/5 << endl;
	return 0;
}

