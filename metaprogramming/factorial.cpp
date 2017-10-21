#include <iostream>
#include <time.h>
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

ull fact(ull n){
	if (n == 1ULL) return 1;
	return n * fact(n-1);
}

int main(int argc, char *argv[]) {
	
	ull res = Factorial<65>::result; //max factorial b4 overflow: 65
	cout << res << endl;
	res = fact(65);
	cout << res << endl;
	return 0;
}

