#include "digit.h"
#include <iostream>
#include <string>
#include <cstdio>

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
	return *this;
}
ostream& operator << (ostream& out,Digit num){
	out<<num.get_digit();
	return out; 
}
istream& operator >> (istream& in, Digit& num){
	/*string temp;
	while(getline(in,temp) && (int)temp[0] == 0){
	}
	if(temp.size() == 1 && temp[0]>= '0' && temp[0]<= '9'){
		num._digit=temp[0]-'0';
	}
	else{
		throw std::runtime_error("invalid digit value!");	
	}*/
	if(!(in>>num._digit) || num._digit > 9 || num._digit < 0){
		throw std::runtime_error("invalid digit value!");
	}
	return in;
}
Digit& Digit::operator=(const Digit& value){
	_digit=value._digit;
	return *this;
}