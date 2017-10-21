#include <iostream>
using namespace std;

typedef unsigned long long ull;

template <ull i>
class Factorial{
public:
	enum { result = i*Factorial<i-1>::result } ;
};

template <>
class Factorial<1ULL>{
public:
	enum {result = 1ULL };
};

int main(int argc, char *argv[]) {
	
	ull res = Factorial<65>::result; //max factorial b4 overflow: 65
	cout << res;
	
	return 0;
}

