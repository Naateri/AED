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
void a1000Elem(double &elapsedTime, ofstream &filexd){
	int* array1000 = generarArray<int>(1000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array1000, array1000+999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1000 elementos: " << elapsedTime << endl;
	delete array1000;
	delete Csort;
}

template <class T>
void a5kElem(double &elapsedTime, ofstream &filexd){
	T* array5k = generarArray<T>(5000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array5k, array5k+4999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 5 000 elementos: " << elapsedTime << endl;
	delete array5k;
	delete Csort;
}

template <class T>
void a10kElem(double &elapsedTime, ofstream &filexd){
	T* array10k = generarArray<T>(10000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array10k, array10k+9999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 10 000 elementos: " << elapsedTime << endl;
	delete array10k;
	delete Csort;
}

template <class T>
void a25kElem(double &elapsedTime, ofstream &filexd){
	T* array25k = generarArray<T>(25000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array25k, array25k+24999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 25 000 elementos: " << elapsedTime << endl;
	delete array25k;
	delete Csort;
}

template <class T>
void a50kElem(double &elapsedTime, ofstream &filexd){
	T* array50k = generarArray<T>(50000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array50k, array50k+49999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 50 000 elementos: " << elapsedTime << endl;
	delete array50k;
	delete Csort;
}

template <class T>
void a100kElem(double &elapsedTime, ofstream &filexd){
	int* array100k = generarArray<int>(100000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array100k, array100k+99999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 elementos: " << elapsedTime << endl;
	delete array100k;
	delete Csort;
}

template <class T>
void a250kElem(double &elapsedTime, ofstream &filexd){
	T* array250k = generarArray<T>(250000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array250k, array250k+249999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 250 000 elementos: " << elapsedTime << endl;
	delete array250k;
	delete Csort;
}

template <class T>
void a500kElem(double &elapsedTime, ofstream &filexd){
	T* array500k = generarArray<T>(500000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array500k, array500k+499999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 500 000 elementos: " << elapsedTime << endl;
	delete array500k;
}

template <class T>
void a1MElem(double &elapsedTime, ofstream &filexd){
	int* array1M = generarArray<int>(1000000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array1M, array1M+999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 1 000 000 elementos: " << elapsedTime << endl;
	delete array1M;
	delete Csort;
}

template <class T>
void a100MElem(double &elapsedTime, ofstream &filexd){
	int* array100M = generarArray<int>(100000000);
	clock_t begin = clock();
	Cocktail<T> *Csort = new MenorCock<T>;
	Csort->sort(array100M, array100M+99999999);
	//imprimir<int>(array1000, array1000+999);
	clock_t end = clock();
	elapsedTime = double(end-begin) / CLOCKS_PER_SEC;
	filexd << "Array 100 000 000 elementos: " << elapsedTime << endl;
	delete array100M;
	delete Csort;
}

int main(int argc, char *argv[]) {
	double et, acum = 0;
	ofstream file;
	file.open("timesPolymorphism.txt");
	for(int i = 0; i < 100; i++){
		a1000Elem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 1000\n";
	file << "Promedio 1000: " << acum/100 << endl;
	acum = 0;
	
	for(int i = 0; i < 50; i++){
		a5kElem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 5000\n";
	file << "Promedio 5000: " << acum/50 << endl;
	acum = 0;
	
	for(int i = 0; i < 30; i++){
		a10kElem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 10 000\n";
	file << "Promedio 10 000: " << acum/30 << endl;
	acum = 0;
	
	for(int i = 0; i < 25; i++){
		a25kElem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 25 000\n";
	file << "Promedio 25 000: " << acum/25 << endl;
	acum = 0;
	
	for(int i = 0; i < 15; i++){
		a50kElem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 50 000\n";
	file << "Promedio 50 000: " << acum/15 << endl;
	acum = 0;
	
	for(int i = 0; i < 10; i++){
		a100kElem<int>(et, file);
		acum += et;
	}
	cout << "Acabo 100 000\n";
	file << "Promedio 100 000: " << acum/25 << endl;
	acum = 0;
	
	a250kElem<int>(et, file);
	cout << "Acabo 250 000\n";
	
	a500kElem<int>(et, file);
	cout << "Acabo 500 000\n";
	//for(int i = 0; i < 10; i++){
	a1MElem<int>(et, file);
	//acum += et;
	//}
	cout << "Acabo 1 000 000\n";
	//file << "Promedio 100 000 000: " << acum/5 << endl;
	return 0;
}
