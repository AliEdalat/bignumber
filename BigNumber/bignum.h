#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>
#include <sstream>
#include <string>

class BigNum
{
public:
	BigNum();
	BigNum(std::string string_number);
	BigNum(double double_number);
	BigNum& operator=(const BigNum& num);
	char& operator[](int index);
	friend BigNum operator-(const BigNum& num);
	friend std::ostream& operator << (std::ostream& out,const BigNum& num);
	friend std::istream& operator >> (std::istream& in, BigNum& num);
private:
	std::string number;
	bool is_negative;
};

#endif