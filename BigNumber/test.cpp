#include <iostream>
#include "bignum.h"

using namespace std;

int main(){
	BigNum a(4);
	BigNum v(8);
	a=v;
	cout<<a<<endl;
	int n=a[0];
	return 0;
}