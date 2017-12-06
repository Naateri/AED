#include <iostream>
#include <vector>
#include <thread>
#include <stdlib.h>
#include <ctime>

#define SIZE_OF_ARRAY 350000000

using namespace std;
typedef unsigned int uint;
typedef vector<uint> vec;

int elems[SIZE_OF_ARRAY];

void swapint(int* a, int* b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void fillArray(){
	srand(time(NULL));
	for(uint i = 0; i < SIZE_OF_ARRAY; i++){
		int xd = int((rand() % 2003219328));
		while (!xd){
			xd = int((rand() % 2003219328));
		}
		elems[i] = xd;
	}
}

int classicMin(int* array, uint size){
	int min = array[0];
	for(uint i = 1; i < size; i++){
		if (array[i] < min) min = array[i];
	}
	return min;
}

void findMin(int* array, uint start, uint end){
	int min = *(array);
	uint pos;
	for(uint i = start + 1; i < end; i++){
		if (array[i] < min){
			min = array[i];
			pos = i;
		}
	}
	swapint(array+start, array+pos);
}

int findActualMin(int* array, uint N){
	uint num_threads = thread::hardware_concurrency();
	int *mins = new int[num_threads], min;
	thread *threads = new thread[num_threads];
	for(uint i = 0; i < num_threads; i++){
		threads[i] = thread(findMin, array, i*(N/num_threads), (i+1)*(N/num_threads));
	}
	for(uint i = 0; i < num_threads; i++){
		threads[i].join();
	}
	for(uint i = 0; i < num_threads; i++){
		mins[i] = *(array + i*(N/num_threads));
	}
	findMin(mins, 0, num_threads);
	min = mins[0];
	delete[] threads;
	delete[] mins;
	return min;
}


int main(int argc, char *argv[]) {
	fillArray();
	//cout << thread::hardware_concurrency() << endl;
	double time;
	clock_t begin = clock();
	cout << findActualMin(elems, SIZE_OF_ARRAY) << endl;
	clock_t end = clock();
	time = (end-begin)/CLOCKS_PER_SEC;
	cout << "Time in threads: " << time << endl;
	clock_t begin1 = clock();
	cout << classicMin(elems, SIZE_OF_ARRAY) << endl;
	clock_t end1 = clock();
	time = (end1-begin1)/CLOCKS_PER_SEC;
	cout << "Time sequential: " << time << endl;
	return 0;
}

