using namespace std;
typedef unsigned int uint;

template <class T>
struct CNode{
	CNode<T>* next;
	CNode<T>* prev;
	T m_x;
	CNode(T x){
		m_x = x;
		next = prev = this;
	}
};

template <class T>
class DList{
	CNode<T>* head;
	CNode<T>* tail;
	uint size = 0;
public:
	DList();
	bool find(T x, CNode<T>*& p);
	bool insert(T x);
	bool remove(T x);
	void print();
	void Josephus(int soldiers, int gap);
};
