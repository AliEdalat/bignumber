#ifndef DIGIT_H
#define DIGIT_H

#include <iostream>
#include <stdexcept>
class Digit
{
public:
	Digit();
	Digit(int value);
	Digit& operator=(int value);
	operator int() const { return _digit; }
	int get_digit(){return _digit;}
	void set_digit(int value){_digit=value;}
	friend std::ostream& operator << (std::ostream& out,const Digit& num);
	friend std::istream& operator >> (std::istream& in, Digit& num);
private:
	int _digit;
};

#endif