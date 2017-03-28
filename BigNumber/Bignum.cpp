#include "Bignum.h"

using namespace std;

void update_number(string& number,vector<Digit> digits,bool is_negative,int found){
	string temp;
	for (int k = 0; k < digits.size(); k++)
	{
		if(is_negative == false && k == found){
			temp.push_back('.');
		}
		if(is_negative == true && k == (found-1)){
			temp.push_back('.');
		}
		temp.push_back((char)(digits[k].get_digit()+48));
	}
	if( temp.find('.') == -1){
		temp.push_back('.');
		temp.push_back('0');
	}
	if (is_negative)
	{
		temp=string("-")+temp;
	}
	if (temp[0] == '.' || (temp[1] == '.' && (temp[0] == '-' || temp[0] == '+' )))
	{
		int find=temp.find('.');
		temp.insert(find+1,1,'0');
	}
	number=temp;
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
bool valid_index(int index,string number,int digits){
	int find=number.find('.');
	int item=find+(-1)*(index)-1;
	if(number.find('-') != -1){
		item-=1;
	}
	if (index < 0 && item >= digits)
	{
		return false;
	}
	if(index >= 0 && (find-index-1) <= 0 && number.find('-') != -1){
		return false;
	}
	if(index >= 0 && (find-index-1) < 0 && number.find('-') == -1){
		return false;
	}
	return true;
}
void remove_not_important_digits(vector<Digit>& digits,string number,int& sign_position){
	for (int i = 0; i < digits.size(); ++i)
	{
		if(digits[i].get_digit() != 0){
			digits.erase(digits.begin(),digits.begin()+i);
			sign_position-=i;
			break;
		}
	}
	if(sign_position < number.size()){
		for (int i = digits.size()-1; i >= sign_position-1; i--)
		{
			if(digits[i].get_digit() != 0){
				digits.erase(digits.end()+(i-digits.size()+1),digits.end());
				break;
			}
		}
	}
}
void update_digits(vector<Digit>& digits,string number){
	digits.clear();
	for (int i = 0; i < number.size(); ++i)
	{
		if(number[i] == '.' || number[i]=='-'){
			continue;
		}
		digits.push_back(Digit(number[i]-48));
	}
}
Bignum::Bignum(){
	number="0";
	digits.push_back(Digit(0));
	sign_position=1;
	is_negative=false;
}
Bignum::Bignum(string string_number){
	if (!valid_number(string_number))
	{
		throw runtime_error("invalid_number_excaption");
	}
	if(string_number[0] == '-'){
		is_negative=true;
	}
	else{
		is_negative=false;
	}
	sign_position=string_number.size();
	for (int i = 0; i < string_number.size(); ++i)
	{
		if(string_number[i] == '.'){
			sign_position=i;
			break;
		}
	}
	number=string_number;
	//cout<<"constractor :"<<string_number<<endl;
	update_digits(digits,string_number);
	remove_not_important_digits(digits,string_number,sign_position);
}
Bignum::Bignum(double double_number){
	is_negative=false;
	if(double_number < 0){
		is_negative=true;
	}
	ostringstream convert;
	convert<<double_number;
	number=convert.str();
	sign_position=number.find('.');
	if(sign_position < 0){
		sign_position=number.size();
	}
	update_digits(digits,number);
	remove_not_important_digits(digits,number,sign_position);
}
ostream& operator << (ostream& out,Bignum num){
	string temp=num.number;
	update_number(temp,num.digits,num.is_negative,num.get_signpos());
	out<<temp;
	return out;
}
istream& operator >> (istream& in,Bignum& num){
	//check valid numbers;
	in>>num.number;
	string temp=num.number;
	//cout<<"operator>> :"<<temp<<endl;
	update_digits(num.digits,num.number);
	num.sign_position=num.number.size();
	for (int i = 0; i < temp.size(); ++i)
	{
		if(temp[i] == '.'){
			num.sign_position=i;
			break;
		}
	}
	remove_not_important_digits(num.digits,num.number,num.sign_position);
	if(num.number[0] == '-'){
		num.is_negative=true;
	}
	else{
		num.is_negative=false;
	}
	return in;
}
Bignum& Bignum::operator=(Bignum num){
	number=num.number;
	update_digits(digits,number);
	sign_position=num.number.size();
	for (int i = 0; i < (num.number).size(); ++i)
	{
		if(num.number[i] == '.'){
			sign_position=i;
			break;
		}
	}
	remove_not_important_digits(digits,number,sign_position);
	if(num.get_isnegative()){
		is_negative=true;
	}
	else{
		is_negative=false;
	}
	return *this;
}
Bignum operator-(Bignum num){
	string temp=num.get_number();
	vector<Digit> digits=num.get_digits();
	update_number(temp,digits,num.get_isnegative(),num.get_signpos());
	if(num.get_isnegative()){
		/*int found=temp.find('-');
		string temp2=temp.substr(found+1);*/
		update_number(temp,digits,!(num.get_isnegative()),num.get_signpos()-1);
		//cout<<temp<<endl;
		return Bignum(temp);
	}
	else{
		//temp=string("-")+temp;
		update_number(temp,digits,!(num.get_isnegative()),num.get_signpos()+1);
		//cout<<temp<<endl;
		return Bignum(temp);
	}
}
Digit& Bignum::operator[](int index){
	int item=0;
	string temp;
	update_number(temp,digits,this->get_isnegative(),this->get_signpos());
	//valid_index ? and set []=
	if(valid_index(index,temp,digits.size())){
		if(index >= 0){
			int found=this->get_signpos()-1;
			item=found-index;
			if(this->get_isnegative() == true){
				item-=1;
			}
		}
		else{
			index*=-1;
			int found=this->get_signpos();
			item=found+index-1;
			if(this->get_isnegative() == true){
				item-=1;
			}
			//cout<<item<<endl;
		}
		return digits[item];
	}
	else{
		digits.push_back(Digit(0));
		return digits[digits.size()-1];
	}
}
void add_zero_digits_end(vector<Digit>& other_number_digits,vector<Digit>& first_number_digits){
	if(other_number_digits.size() > first_number_digits.size()){
		first_number_digits.insert(first_number_digits.end(),(other_number_digits.size() - first_number_digits.size()),Digit(0));
	}
	if(other_number_digits.size() < first_number_digits.size()){
		other_number_digits.insert(other_number_digits.end(),(first_number_digits.size() - other_number_digits.size()),Digit(0));
	}
}
void prepare_oprands(vector<Digit>& other_number_digits,vector<Digit>& first_number_digits,int& first_sign_position,int& other_sign_position,Bignum other,Bignum* first){
	first_sign_position=first->get_signpos();
	other_sign_position=other.get_signpos();
	bool first_nagative=first->get_isnegative();
	bool other_negative=other.get_isnegative();
	if(first_nagative == true){
		first_sign_position-=1;
	}
	if(other_negative == true){
		other_sign_position-=1;
	}
	if(first_sign_position > other_sign_position){
		other_number_digits.insert(other_number_digits.begin(),(first_sign_position - other_sign_position) ,Digit(0));
		other_sign_position+=((first_sign_position - other_sign_position));
		add_zero_digits_end(other_number_digits,first_number_digits);
	}
	if(first_sign_position < other_sign_position){
		first_number_digits.insert(first_number_digits.begin(),(other_sign_position - first_sign_position) ,Digit(0));
		first_sign_position+=((other_sign_position - first_sign_position));
		add_zero_digits_end(other_number_digits,first_number_digits);	
	}
	if(first_sign_position == other_sign_position){
		add_zero_digits_end(other_number_digits,first_number_digits);
	}
	if(first_nagative == true){
		first_sign_position+=1;
	}
	if(other_negative == true){
		other_sign_position+=1;
	}
}
vector<Digit> subtraction_act(vector<Digit>& first_number_digits,vector<Digit>& other_number_digits){
	vector<Digit> result_number_digits;
	for (int i = first_number_digits.size()-1; i >= 0; i--)
	{
		if(first_number_digits[i].get_digit() >= other_number_digits[i].get_digit()){
			int result=first_number_digits[i].get_digit()-other_number_digits[i].get_digit();
			result_number_digits.push_back(Digit(result));
		}
		else{
			int result=first_number_digits[i].get_digit()-other_number_digits[i].get_digit()+10;
			first_number_digits[i-1].set_digit(first_number_digits[i-1].get_digit()-1);
			result_number_digits.push_back(Digit(result));
		}
	}
	return result_number_digits;
}
Bignum Bignum::operator+(Bignum other){
	int first_sign_position , other_sign_position,sign_position;
	bool is_negative;
	vector<Digit> result_number_digits;
	vector<Digit> first_number_digits=this->get_digits();
	vector<Digit> other_number_digits=other.get_digits();
	prepare_oprands(other_number_digits,first_number_digits,first_sign_position,other_sign_position,other,this);
	/*if(other.get_signpos() > sign_position){
		sign_position=other.get_signpos();
	}*/
	/*if(this->get_isnegative() == true){
		first_sign_position-=1;
	}
	if(other.get_isnegative() == true){
		other_sign_position-=1;
	}*/
	sign_position=first_sign_position;
	if(other_sign_position > first_sign_position){
		sign_position=other_sign_position;
	}
	if(this->get_isnegative() == other.get_isnegative()){
		is_negative=this->get_isnegative();
		int carry=0;
		for (int i = first_number_digits.size()-1; i >= 0; i--)
		{
			int result=carry+first_number_digits[i].get_digit()+other_number_digits[i].get_digit();
			if(result >= 10){
				result_number_digits.push_back(Digit(result%10));	
				carry=result/10;
			}
			else{
				result_number_digits.push_back(Digit(result));
				carry=0;	
			}
			
		}
		if(carry != 0){
			result_number_digits.push_back(Digit(carry));
			sign_position++;
		}
	}
	else{
		if(this->get_isnegative() == true){
			this->is_negative=false;
			this->sign_position-=1;
			if( *this == other){
				this->sign_position+=1;
				this->is_negative=true;
				return Bignum(0);
			}
			else if ( *this < other)
			{
				this->sign_position+=1;
				this->is_negative=true;
				is_negative=false;
				result_number_digits=subtraction_act(other_number_digits,first_number_digits);
			}
			else{
				this->sign_position+=1;
				this->is_negative=true;
				is_negative=true;
				result_number_digits=subtraction_act(first_number_digits,other_number_digits);
			}
		}
		else{
			other.is_negative=false;
			other.sign_position-=1;
			if( *this == other){
				other.sign_position+=1;
				other.is_negative=true;
				return Bignum(0);
			}
			else if ( *this < other)
			{
				other.sign_position+=1;
				other.is_negative=true;
				is_negative=true;
				result_number_digits=subtraction_act(other_number_digits,first_number_digits);
			}
			else{
				other.sign_position+=1;
				other.is_negative=true;
				is_negative=false;
				result_number_digits=subtraction_act(first_number_digits,other_number_digits);
			}
		}
	}
	for (int i = 0; i < result_number_digits.size(); ++i)
	{
		int end=result_number_digits.size()-1;
		if((end-i) >= i){
			swap(result_number_digits[end-i],result_number_digits[i]);
		}
	}
	string temp;
	update_number(temp,result_number_digits,is_negative,sign_position);
	//cout<<"operator+ :"<<temp<<endl;
	return Bignum(temp);
}
bool Bignum::operator<(Bignum other){
	string number1,number2;
	if (this->get_isnegative() == true && other.get_isnegative() == false)
	{
		return true;
	}
	if (this->get_isnegative() == false && other.get_isnegative() == true)
	{
		return false;
	}
	if (*this == other)
	{
		//cout<<"operator< :";
		return false;
	}
	if(this->get_isnegative() == false){
		int first_sign_position,other_sign_position;
		vector<Digit> first_number_digits=this->get_digits();
		vector<Digit> other_number_digits=other.get_digits();
		prepare_oprands(other_number_digits,first_number_digits,first_sign_position,other_sign_position,other,this);
		update_number(number1,first_number_digits,this->get_isnegative(),first_sign_position);
		update_number(number2,other_number_digits,this->get_isnegative(),other_sign_position);
		//cout<<number1<<' '<<number2<<endl;
		if(number1 < number2){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(number1 > number2){
			return true;
		}
		else{
			return false;
		}
	}
}
bool Bignum::operator==(Bignum other){
	if(other.get_isnegative() == this->get_isnegative()){
		int first_sign_position,other_sign_position;
		vector<Digit> first_number_digits=this->get_digits();
		vector<Digit> other_number_digits=other.get_digits();
		prepare_oprands(other_number_digits,first_number_digits,first_sign_position,other_sign_position,other,this);
		string number1,number2;
		update_number(number1,first_number_digits,this->get_isnegative(),first_sign_position);
		update_number(number2,other_number_digits,this->get_isnegative(),other_sign_position);
		if(number1.compare(number2) == 0){
			return true;
		}
		return false;
	}
	else{
		return false;
	}

}
Bignum& Bignum::operator+=(Bignum other){
	*this=*this+other;
	return *this;
}
Bignum Bignum::operator+(double double_number){
	Bignum temp(double_number);
	temp+=*this;
	return temp;
}
Bignum operator+(double double_number,Bignum number){
	Bignum temp(double_number);
	temp.operator+=(number);
	return temp;	
}
Bignum& Bignum::operator++(){
	Bignum temp(1);
	*this+=temp;
	return *this;
}
Bignum Bignum::operator++(int){
	Bignum copy(this->get_number());
	Bignum temp(1);
	*this+=temp;
	return copy;
}
bool operator==(double double_number,Bignum number){
	Bignum temp(double_number);
	return (temp==number);
}
bool operator<(double double_number,Bignum number){
	Bignum temp(double_number);
	return (temp < number);
}