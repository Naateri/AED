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
class CSMatrix;	

template <class T, T nl>
class CCosa{
	uint x,y;
	CSMatrix<T, nl>* m;
public:
	CCosa(CSMatrix<T, nl>* mat, uint x, uint y){
		this->m = mat;
		this->x = x;
		this->y = y;
	}
	void operator=(T val);
	operator T(){
		return m->get(x, y);
	}
};

template <class T, T nl>
void CCosa<T, nl>::operator=(T val){
	m->set(val, x, y);
	return;
}

template <class T, T nl>
class CSMatrix{
private:
	CNode<T>** up;
	CNode<T>** right;
	uint col;
	uint rows;
	bool findUp(CNode<T>**& p, uint x, uint y);
	bool findRight(CNode<T>**& p, uint x, uint y);
	void insertUp(CNode<T>* p, T val, uint x, uint y);
	void insertRight(CNode<T>* p, T val, uint x, uint y);
	void eraseUp(uint x, uint y);
	void eraseRight(uint x, uint y);
public:
	CSMatrix(uint m, uint n);
	uint get_cols(){return col;}
	uint get_rows(){return rows;}
	void print();
	void insert(T val, uint x, uint y);
	void modify(T val, uint x, uint y);
	void erase(uint x, uint y);
	void visitFirstColumn(){
		CNode<T>* temp, *temp2;
		for(temp = up[0]; temp; temp = (temp)->next[0]){
			cout << temp->val << endl;
		}
	}
	void visitFirstRow(){
		CNode<T>* temp;
		for(temp = right[0]; temp; temp = temp->next[1]){
			cout << temp->val << endl;
		}
	}
	T get(uint x, uint y);
	void set(T val, uint x, uint y);
	CCosa<T, nl> operator()(uint x, uint y);
};

template <class T, T nl>
CCosa<T, nl> CSMatrix<T, nl>::operator()(uint x, uint y){
	CCosa<T, nl> Cosa(this, x, y);
	return Cosa;
}

template <class T, T nl>
bool CSMatrix<T, nl>::findRight(CNode<T>**& p, uint x, uint y){
	CNode<T>* temp2;
	for (p = &right[y]; *p && (*p)->x < x; p = &(*p)->next[1]);
	return *p && (*p)->x == x;
}

template <class T, T nl>
bool CSMatrix<T, nl>::findUp(CNode<T>**& p, uint x, uint y){
	CNode<T>** temp, *temp2;
	for(temp = &up[x]; *temp && (*temp)->y < y; temp = &(*temp)->next[0]);
	temp = p;
	return (*temp)->y == y;
}

template <class T, T nl>
CSMatrix<T, nl>::CSMatrix(uint m, uint n){
	up = new CNode<T>*[m];
	right = new CNode<T>*[n];
	col = m;
	rows = n;
}

template <class T, T nl>
void CSMatrix<T, nl>::insertUp(CNode<T>* p, T val, uint x, uint y){
	CNode<T>** temp, *temp2;
	for(temp = &up[x]; *temp && (*temp)->y < y; temp = &(*temp)->next[0]);
	temp2 = *temp;
	*temp = p;
	p->next[0] = temp2;
	return;
}

template <class T, T nl>
void CSMatrix<T, nl>::insertRight(CNode<T>* p, T val, uint x, uint y){
	CNode<T>** temp, *temp2;
	for(temp = &right[y]; *temp && (*temp)->x < x; temp = &(*temp)->next[1]);
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
	for(temp = right[y]; temp->x != x; temp = temp->next[1]);
	temp->val = val;
	return;
}

template <class T, T nl>
T CSMatrix<T, nl>::get(uint x, uint y){
	CNode<T>* temp;
	for(temp = right[y]; temp && (temp)->x < x; temp = (temp)->next[1]);
	if (!temp || temp->x != x) return nl;
	return (temp)->val;
}

template <class T, T nl>
void CSMatrix<T, nl>::eraseUp(uint x, uint y){
	CNode<T>** temp, *temp2;
	for(temp = &up[x]; *temp && (*temp)->y < y; temp = &(*temp)->next[0]);
	temp2 = *temp;
	*temp = (*temp)->next[0];
	temp2 = 0;
}

template <class T, T nl>
void CSMatrix<T, nl>::eraseRight(uint x, uint y){
	CNode<T>** temp, *temp2;
	for(temp = &right[y]; *temp && (*temp)->x < x; temp = &(*temp)->next[1]);
	temp2 = (*temp);
	*temp = (*temp)->next[1];
	temp2 = 0;
	delete temp2;
}

template <class T, T nl>
void CSMatrix<T, nl>::erase(uint x, uint y){
	eraseUp(x, y);
	eraseRight(x, y);
}

template <class T, T nl>
void CSMatrix<T, nl>::set(T val, uint x, uint y){
	if (val == nl){
		erase(x,y);
		return;
	}
	CNode<T>** p;
	if (findRight(p, x, y) ){
		modify(val, x, y); return;
	}
	insert(val, x, y);
	return;
	
}

template <class T, T nl>
void CSMatrix<T, nl>::print(){
	for(uint i = 0; i < col; i++){
		for (uint j = 0; j < rows; j++){
			cout << get(j, i) << ' ';
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	CSMatrix<int, 0> m(6, 6);
	int x;
	/*for(int i = 0; i < 5; i++){
		for (int j = 0; j < 6; j++){
			m.insert(i+j, i, j);
		}
	}*/
	//m.set(5, 2, 3);
	m(2, 3) = 5;
	m(3, 2) = 9;
	m(3, 2) = 7;
	m(3, 4) = 4;
	m(1, 3) = 8;
	m(4, 3) = 1;
	m(5, 3) = 1;
	m(3, 4) = 0;
	m(3, 2) = 0;
	x = m(2, 3);
	cout << x << endl;
	//m.print();
	m(0,0) = 5;
	m(0,1) = 8;
	m(0,2) = 4;
	m(0,4) = 6;
	m(0,5) = 3;
	
	m(1,0) = 4;
	m(2,0) = 3;
	m(3,0) = 2;
	m(4,0) = 1;
	m(5,0) = 6;
	m.print();
	cout << "Visiting first row:\n";
	//for(int i = 0; i < 6; i++){
	m.visitFirstRow();
	cout << "Visiting first column:\n";
	m.visitFirstColumn();
	//}*/
	return 0;
}

