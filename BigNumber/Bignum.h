#ifndef BIGNUM_H
#define BIGNUM_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "digit.h"

class Bignum
{
public:
	Bignum();
	Bignum(std::string string_number);
	Bignum(double double_number);
	Bignum& operator=(const Bignum& num);
	Digit& operator[](int index);
	int get_signpos(){return sign_position;}
	bool get_isnegative(){return is_negative;}
	bool get_iszero(){return is_zero;}
	void set_signpos(int position){sign_position=position;}
	void set_isnegative(bool negative){is_negative=negative;}
	std::vector<Digit> get_digits();
	std::string get_number(){return number;}
	Bignum operator+(Bignum other);
	bool operator<(Bignum other);
	bool operator==(Bignum other);
	Bignum& operator+=(Bignum other);
	Bignum operator+(double double_number);
	Bignum& operator++();
	Bignum operator++(int);
	friend std::ostream& operator << (std::ostream& out,Bignum num);
	friend std::istream& operator >> (std::istream& in, Bignum& num);
private:
	std::string number;
	std::vector<Digit> digits_befor;
	std::vector<Digit> digits_after;
	bool is_negative;
	bool is_zero;
	int sign_position;
};
bool operator==(double double_number,Bignum number);
bool operator<(double double_number,Bignum number);
Bignum operator+(double double_number,Bignum number);
Bignum operator-(Bignum& num);
Bignum& operator+=(Bignum& number,double double_number);
Bignum& operator+=(double& double_number,Bignum& number);

#endif