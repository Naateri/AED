#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

class Mayor{
public:
	bool operator()(int a, int b){return (a>b);};
};

class Menor{
public:
	bool operator()(int a, int b){return a<b;};
};

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

template <class T, class O> class Sort{
private:
	O Method;
public:
	void cocktail(T *a, T *fin){
		T *aux;
		aux = a;
		bool compro = 1;
		T *auxF = fin;
		while (compro){
			compro = 0;
			for(a; a < fin; a++){
				if(Method(*a, *(a+1))){
					swap<T>(*a, *(a+1));
					compro = 1;
				}
			}
			for(a; fin != aux; fin--){
				if(!(Method(*fin, *(fin-1)))){
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

template <class T, class O>
void a1000Elem(double &elapsedTime, ofstream &filexd){
	T* array1000 = generarArray<T>(1000);
	clock_t begin = clock();
	Sort<T, O> sorting;
	sorting.cocktail(array1000, array1000+999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1000 elementos: " << elapsedTime << endl;
	delete array1000;
}

template <class T, class O>
void a100kElem(double &elapsedTime, ofstream &filexd){
	T* array100k = generarArray<T>(100000);
	clock_t begin = clock();
	Sort<T, O> sorting;
	sorting.cocktail(array100k, array100k+99999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 elementos: " << elapsedTime << endl;
	delete array100k;
}

template <class T, class O>
void a1MElem(double &elapsedTime, ofstream &filexd){
	T* array1M = generarArray<T>(1000000);
	clock_t begin = clock();
	Sort<T, O> sorting;
	sorting.cocktail(array1M, array1M+999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1 000 000 elementos: " << elapsedTime << endl;
	delete array1M;
}

template <class T, class O>
void a100MElem(double &elapsedTime, ofstream &filexd){
	T* array100M = generarArray<int>(100000000);
	clock_t begin = clock();
	Sort<T, O> sorting;
	sorting.cocktail(array100M, array100M+99999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 000 elementos: " << elapsedTime << endl;
	delete array100M;
}

int main(int argc, char *argv[]) {
	double et, acum = 0;
	ofstream file;
	file.open("timesFunctor.txt");
	for(int i = 0; i < 100; i++){
		a1000Elem<int, Menor>(et, file);
		acum += et;
	}
	cout << "Acabo 1000\n";
	file << "Promedio 1000: " << acum/100 << endl;
	acum = 0;
	for(int i = 0; i < 25; i++){
		a100kElem<int, Menor>(et, file);
		acum += et;
	}
	cout << "Acabo 100 000\n";
	file << "Promedio 100 000: " << acum/25 << endl;
	acum = 0;
	for(int i = 0; i < 10; i++){
		a1MElem<int, Menor>(et, file);
		acum += et;
	}
	cout << "Acabo 1 000 000\n";
	file << "Promedio 1 000 000: " << acum/10 << endl;
	acum = 0;
	for (int i = 0; i < 5; i++){
		a100MElem<int, Menor>(et, file);
		acum += et;
	}
	cout << "Acabo 100 000 000\n";
	file << "Promedio 100 000 000: " << acum/5 << endl;
	return 0;
}

