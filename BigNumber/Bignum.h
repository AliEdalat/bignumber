#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include "digit.h"

class Bignum
{
public:
	Bignum();
	Bignum(std::string string_number);
	Bignum(double double_number);
	Bignum& operator=(Bignum num);
	Digit& operator[](int index);
	int get_signpos(){return sign_position;}
	bool get_isnegative(){return is_negative;}
	std::vector<Digit> get_digits(){return digits;}
	std::string get_number(){return number;}
	Bignum operator+(Bignum other);
	bool operator<(Bignum other);
	bool operator==(Bignum other);
	friend std::ostream& operator << (std::ostream& out,Bignum num);
	friend std::istream& operator >> (std::istream& in, Bignum& num);
private:
	std::string number;
	std::vector<Digit> digits;
	bool is_negative;
	int sign_position;
};

#endif