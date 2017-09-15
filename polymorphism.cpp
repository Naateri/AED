#include <iostream>
#include <stdlib.h>
#include <time.h>

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

template <class T> class Cocktail{
protected:
	//virtual bool mayor(T, T) = 0;
	virtual bool menor(T, T) = 0;
public:
	void sort(T *a, T *fin){
		T *aux;
		aux = a;
		bool compro = 1;
		T *auxF = fin;
		while (compro){
			compro = 0;
			for(a; a < fin; a++){
				if(menor(*a, *(a+1))){
					swap<T>(*a, *(a+1));
					compro = 1;
				}
			}
			for(a; fin != aux; fin--){
				if(!(menor(*fin, *(fin-1)))){
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

template <class T> 
class MenorCock: public Cocktail<T>{
public:
	bool menor(T a, T b){
		return a < b;
	}
};

/*template <class T> class MenorCock: public Cocktail<T>{
public:
	bool menor(T a, T b){
		return a < b;
	}
};*/

template <class T>
void a1000Elem(){
	double elapsedTime;
	int* array1000 = generarArray<int>(1000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array1000, array1000+999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	cout << "Array 1000 elementos: " << elapsedTime << endl;
	delete array1000;
	delete Csort;
}

template <class T>
void a100kElem(){
	double elapsedTime;
	int* array100k = generarArray<int>(100000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array100k, array100k+99999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	cout << "Array 100 000 elementos: " << elapsedTime << endl;
	delete array100k;
	delete Csort;
}

template <class T>
void a1MElem(){
	double elapsedTime;
	int* array1M = generarArray<int>(1000000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array1M, array1M+999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	cout << "Array 1 000 000 elementos: " << elapsedTime << endl;
	delete array1M;
	delete Csort;
}

template <class T>
void a100MElem(){
	double elapsedTime;
	int* array100M = generarArray<int>(100000000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array100M, array100M+99999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	cout << "Array 100 000 000 elementos: " << elapsedTime << endl;
	delete array100M;
	delete Csort;
}

int main(int argc, char *argv[]) {
	a1000Elem<int>();
	a100kElem<int>();
	a1MElem<int>();
	a100MElem<int>();
	return 0;
}
