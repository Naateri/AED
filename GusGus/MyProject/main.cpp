#include <iostream>
#include <string>
#include "AVL.h"
#include "DLClist.h"
#include "graph.h"
using namespace std;

typedef unsigned int uint;

class Jugador{
	uint nro;
	uint age;
	string l_name;
	char pos;
	string country;
};

bool allNodesChecked(Path* p, uint size){
	for(uint i = 0; i < size; i++){
		if ( ! (p+i)->done ) return 0;
	}
	return 1;
}

bool findSameLetter(string a, string b){
	int shortest;
	if (a.size() > b.size()) shortest = b.size();
	else shortest = a.size();
	for(int i = 0; i < shortest; i++){
		if ( a[i] == b[i] ) return 1;
	}
	return 0;
}

int main (int argc, char *argv[]) {
	
	return 0;
}

