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
	uint col;
	uint rows;
	void insertUp(CNode<T>*& p, T val, uint x, uint y);
	void insertRight(CNode<T>*& p, T val, uint x, uint y);
public:
	CSMatrix(uint m, uint n);
	void print();
	void insert(T val, uint x, uint y);
	void modify(T val, uint x, uint y);
	void erase(uint x, uint y);
	T get(uint x, uint y);
};

template <class T, T nl>
CSMatrix<T, nl>::CSMatrix(uint m, uint n){
	up = new CNode<T>*[m];
	right = new CNode<T>*[n];
	col = m;
	rows = n;
}

template <class T, T nl>
void CSMatrix<T, nl>::insertUp(CNode<T>*& p, T val, uint x, uint y){
	CNode<T>** temp, *temp2 = 0;
	for(temp = &up[x]; *temp && (*temp)->y < y; temp = &(*temp)->next[0], temp2 = *temp);
	temp2 = *temp;
	*temp = p;
	p->next[0] = temp2;
	return;
}

template <class T, T nl>
void CSMatrix<T, nl>::insertRight(CNode<T>*& p, T val, uint x, uint y){
	CNode<T>** temp, *temp2 = 0;
	for(temp = &right[y]; *temp && (*temp)->x < x; temp = &(*temp)->next[1], temp2 = *temp);
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
void CSMatrix<T, nl>::modify(T val, uint x, uint y){
	CNode<T>* temp;
	for(temp = up[x]; temp->y < y; temp = temp->next[0]);
	temp->val = val;
	return;
}

template <class T, T nl>
T CSMatrix<T, nl>::get(uint x, uint y){
	CNode<T>* temp;
	for(temp = up[x]; temp && (temp)->y < y; temp = (temp)->next[0]);
	if (!temp || temp->y != y) return nl;
	return (temp)->val;
}

template <class T, T nl>
void CSMatrix<T, nl>::print(){
	for(int i = 0; i < rows; i++){
		for (int j = 0; j < col; j++){
			cout << get(i, j) << ' ';
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	CSMatrix<int, 0> m(6, 6);
	/*for(int i = 0; i < 5; i++){
		for (int j = 0; j < 6; j++){
			m.insert(i+j, i, j);
		}
	}*/
	m.insert(5, 2, 3);
	m.insert(9, 3, 2);
	m.modify(7, 3, 2);
	m.print();
	return 0;
}

