#include "bignum.h"

using namespace std;
class invalid_number_exception{};
class invalid_digit_exception{};
void update_number(string& number){
	for (int i = 0; i < number.size(); ++i)
	{
		if(number[i] < 48 && number[i] != 46 && number[i] >= 0 && number[i] < 10){
			int temp=(int)number[i];
			number[i]=temp+48;
		}
		if (number[i] < 48 && number[i] != 46 && (number[i] < 0 || number[i] >=10))
		{
			throw invalid_digit_exception();
		}
	}
}
bool valid_number(string num){
	for (int i = 0; i < num.size(); ++i)
	{
		if((num[i]<48 || num[i]>57) && num[i] != 46 && num[i] != '-'){
			return false;
		}
	}
	return true;
}
bool valid_index(int index,string number){
	int find=number.find('.');
	if (index < 0 && (find+(-1*index)) >= number.size())
	{
		return false;
	}
	if(index >= 0 && (find-index-1) < 0){
		return false;
	}
	return true;
}
BigNum::BigNum(){
	number="0";
	is_negative=false;
}
BigNum::BigNum(string string_number){
	if (!valid_number(string_number))
	{
		throw invalid_number_exception();
	}
	if(string_number.find('-') != -1){
		is_negative=true;
	}
	else{
		is_negative=false;
	}
	number=string_number;
}
BigNum::BigNum(double double_number){
	is_negative=false;
	if(double_number < 0){
		is_negative=true;
	}
	ostringstream convert;
	convert<<double_number;
	number=convert.str();
}
ostream& operator << (ostream& out,const BigNum& num){
	out<<num.number;
	return out;
}
istream& operator >> (istream& in,BigNum& num){
	//check valid numbers;
	in>>num.number;
	if(num.number[0] == '-'){
		num.is_negative=true;
	}
	else{
		num.is_negative=false;
	}
	return in;
}
BigNum& BigNum::operator=(const BigNum& num){
	number=num.number;
	return *this;
}
BigNum operator-(const BigNum& num){
	string temp=num.number;
	if(num.is_negative){
		int found=temp.find('-');
		string temp2=temp.substr(found+1);
		return BigNum(temp2);
	}
	else{
		temp=string("-")+temp;
		return BigNum(temp);
	}
}
char& BigNum::operator[](int index){
	try{
		update_number(number);
	}catch(invalid_digit_exception exception){
		cout<<"invalid digit in number!"<<endl;
		throw;
	}
	int item=0;
	//valid_index ? and set []=
	if(valid_index(index,number)){
		if(index >= 0){
			int found=number.find('.')-1;
			item=found-index;
		}
		else{
			index*=-1;
			int found=number.find('.');
			item=found+index;
		}
		return number[item];
	}
	else{
		number.push_back('0');
		return number[number.size()-1];
	}
}