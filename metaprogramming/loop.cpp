#include <iostream>
using namespace std;

typedef unsigned long long ull;

template <ull i>
class Loop{
public:
	static inline void f(){
		cout << "A-" << i << endl;
		Loop<i-1>::f();
		cout << "B-" << i << endl;
	}
};

template <>
class Loop<0ULL>{
public: 
	inline void f(){
		//cout << "A-" << 0ULL << endl;
		cout << endl;
		//cout << "B-" << 0ULL << endl;
	}
};

int main(int argc, char *argv[]) {
	Loop<0>::f();
	return 0;
}

