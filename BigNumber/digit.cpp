#include "digit.h"
#include <iostream>
using namespace std;
Digit::Digit(){
	_digit=0;
}
Digit::Digit(int value){
	if (value > 9 || value < 0)
	{
		throw std::runtime_error("invalid digit value!");
	}
	_digit=value;
}
Digit& Digit::operator=(int value){
	if (value > 9 || value < 0)
	{
		throw std::runtime_error("invalid digit value!");
	}
	_digit=value;
}
ostream& operator << (ostream& out,const Digit& num){
	out<<num._digit;
	return out; 
}
istream& operator >> (istream& in, Digit& num){
	in>>num._digit;
	return in;
}