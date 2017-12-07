#include <iostream>
#include <thread>
#include <stdlib.h>
#include <ctime>

#define SIZE_OF_ARRAY 350000000

using namespace std;
typedef unsigned int uint;

int *elems = new int[SIZE_OF_ARRAY];

void swap(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void fillArray(){
	srand(time(NULL));
	for(uint i = 0; i < SIZE_OF_ARRAY; i++){
		int xd = int((rand() % 200/*3219328*/));
		while (!xd){
			xd = int((rand() % 200/*3219328*/));
		}
		elems[i] = xd;
	}
}

void my_find(int* array, uint start, uint end, int x){
	uint i, pos;
	for(i = start; i < end; i++){
		if ( *(array+i) == x ){
			pos = i;
			swap(array[start], array[pos]); 
			//return;
			break;
		}
	}
}

bool findVal(int* array, int x, uint N){
	uint n_threads = thread::hardware_concurrency();
	thread* threads = new thread[n_threads];
	int* possible_values = new int[n_threads];
	for(uint i = 0; i < n_threads; i++){
		threads[i] = thread(my_find, array, i * (N/n_threads), (i+1) * (N/n_threads), x);
	}
	for(uint i = 0; i < n_threads; i++){
		threads[i].join();
	}
	for(uint i = 0; i < n_threads; i++){
		possible_values[i] = array[i * (N/n_threads)];
		if (possible_values[i] == x) {
			delete[] threads;
			delete[] possible_values;
			return 1;
		}
	}
	delete[] threads;
	delete[] possible_values;
	return 0;
}

bool sequentialFindVal(int* array, int x, uint N){
	for (uint i = 0; i < N; i++){
		if (*(array+i) == x) return 1;
	}
	return 0;
}

int main(int argc, char *argv[]) {
	fillArray();
	cout << findVal(elems, 10, SIZE_OF_ARRAY) << endl;
	cout << sequentialFindVal(elems, 10, SIZE_OF_ARRAY) << endl;
	return 0;
}

