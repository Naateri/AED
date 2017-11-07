#include <iostream>
using namespace std;

typedef unsigned int uint;

template <class T>
struct CNode{
	uint x;
	uint y;
	T val;
	CNode<T>* next[2]; //up: 0, right: 1
	CNode(T value, uint coord_x, uint coord_y){
		val = value;
		x = coord_x;
		y = coord_y;
		next[0] = next[1] = 0;
	}
};

template <class T, T nl>
class CSMatrix{
private:
	CNode<T>** up;
	CNode<T>** right;
	void insertUp(CNode<T>*& p, T val, uint x, uint y);
	void insertRight(CNode<T>*& p, T val, uint x, uint y);
public:
	CSMatrix(uint m, uint n);
	void insert(T val, uint x, uint y);
	T get(uint x, uint y);
};

template <class T, T nl>
CSMatrix<T, nl>::CSMatrix(uint m, uint n){
	up = new CNode<T>*[m];
	right = new CNode<T>*[n];
}

template <class T, T nl>
void CSMatrix<T, nl>::insertUp(CNode<T>*& p, T val, uint x, uint y){
	CNode<T>** temp, *temp2 = 0;
	for(temp = &up[x]; *temp && (*temp)->y < y; temp = &(*temp)->next[1], temp2 = *temp);
	temp2 = *temp;
	*temp = p;
	p->next[0] = temp2;
	return;
}

template <class T, T nl>
void CSMatrix<T, nl>::insertRight(CNode<T>*& p, T val, uint x, uint y){
	CNode<T>** temp, *temp2 = 0;
	for(temp = &right[y]; *temp && (*temp)->x < x; temp = &(*temp)->next[0], temp2 = *temp);
	temp2 = *temp;
	*temp = p;
	p->next[1] = temp2;
	return;
}

template <class T, T nl>
void CSMatrix<T, nl>::insert(T val, uint x, uint y){
	CNode<T>* p = new CNode<T>(val, x, y);
	insertUp(p, val, x, y);
	insertRight(p, val, x, y);
	return;
}

template <class T, T nl>
T CSMatrix<T, nl>::get(uint x, uint y){
	CNode<T>* temp;
	for(temp = up[x]; temp && (temp)->y < y; temp = (temp)->next[1]);
	if (!temp) return nl;
	return (temp)->val;
}

int main(int argc, char *argv[]) {
	CSMatrix<int, 0> m(6, 6);
	for(int i = 0; i < 5; i++){
		for (int j = 0; j < 6; j++){
			m.insert(i+j, i, j);
		}
	}
	for(int i = 0; i < 6; i++){
		for (int j = 0; j < 6; j++){
			cout << m.get(i, j) << ' ';
		}
		cout << endl;
	}
	return 0;
}

