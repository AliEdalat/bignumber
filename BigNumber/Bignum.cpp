#include "Bignum.h"

using namespace std;

bool find_zero_number(vector<Digit> digits);
void convert_digits_to_string(string& number,vector<Digit> digits,bool is_negative,int found){
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
		if((num[i]<48 || num[i]>57) && num[i] != '.'){
			if(i==0 && num[i] == '-'){
				;
			}
			else{
				return false;
			}
		}
	}
	return true;
}
bool valid_index(int index,int sign_position,int size,bool is_negative){
	if(index>0){
		int max=sign_position-1;
		if(is_negative){
			max-=1;
		}
		if(index > max){
			return false;
		}
	}
	else{
		int min=size-1;
		min=sign_position-min;
		if(index < min){
			return false;
		}
	}
	return true;
}
void remove_not_important_digits(vector<Digit>& digits_after,vector<Digit>& digits_befor,string number,int& sign_position){
	if(find_zero_number(digits_after) && find_zero_number(digits_befor)){
		digits_after.clear();
		digits_befor.clear();
		digits_befor.push_back(Digit(0));
		sign_position=1;
	}
	for (int i = digits_befor.size()-1; i >= 0; i--)
	{
		if(digits_befor[i].get_digit() != 0){
			sign_position -= ((digits_befor.size()-1)-i);
			digits_befor.erase(digits_befor.end()+(i-digits_befor.size()+1),digits_befor.end());
			//cout<<"sign_position :"<<sign_position<<endl;
			break;
		}
	}
	if(sign_position < number.size()){
		for (int i = digits_after.size()-1; i >= 0; i--)
		{
			if(digits_after[i].get_digit() != 0){
				digits_after.erase(digits_after.end()+(i-digits_after.size()+1),digits_after.end());
				break;
			}
		}
	}
}
void convert_string_to_digits(vector<Digit>& digits_after,vector<Digit>& digits_befor,string number){
	digits_after.clear();digits_befor.clear();
	int found=number.find('.');
	for (int i = 0; i < found; ++i)
	{
		if(number[i]=='-'){
			continue;
		}
		//cout<<number[i]<<endl;
		digits_befor.push_back(Digit(number[i]-48));
	}
	reverse(digits_befor.begin(),digits_befor.end());
	for (int i = found+1; i < number.size() ; ++i)
	{
		//cout<<number[i]<<endl;
		digits_after.push_back(Digit(number[i]-48));
	}
	//cout<<"size :"<<digits_after.size()<<endl;
}
bool find_zero_number(vector<Digit> digits){
	for (int i = 0; i < digits.size(); ++i)
	{
		if(digits[i].get_digit() != 0){
			return false;
		}
	}
	return true;
}
Bignum::Bignum(){
	number="0";
	digits_befor.push_back(Digit(0));
	sign_position=1;
	is_negative=false;
	is_zero=true;
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
	is_zero=false;
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
	convert_string_to_digits(digits_after,digits_befor,string_number);
	remove_not_important_digits(digits_after,digits_befor,string_number,sign_position);
	if(find_zero_number(digits_after) && find_zero_number(digits_befor)){
		is_zero=true;
		if (is_negative)
		{
			is_negative=false;
			sign_position--;	
		}
	}
	//cout<<"size :"<<digits_after.size()<<endl;
}
Bignum::Bignum(double double_number){
	is_negative=false;
	is_zero=false;
	if(double_number < 0){
		is_negative=true;
	}
	if(double_number == 0){
		is_zero=true;
	}
	ostringstream convert;
	convert<<double_number;
	number=convert.str();
	sign_position=number.find('.');
	if(sign_position < 0){
		sign_position=number.size();
	}
	convert_string_to_digits(digits_after,digits_befor,number);
	remove_not_important_digits(digits_after,digits_befor,number,sign_position);
}
vector<Digit> Bignum::get_digits(){
	vector<Digit> result_digits;
	for (int i = digits_befor.size()-1; i >= 0; i--)
	{
		//cout<<digits_befor[i].get_digit()<<endl;
		result_digits.push_back(Digit(digits_befor[i].get_digit()));
	}
	//cout<<digits_after[0]<<endl;
	for (int j = 0; j < digits_after.size(); ++j)
	{
		//cout<<digits_after[j].get_digit()<<endl;
		result_digits.push_back(Digit(digits_after[j].get_digit()));
	}
	return result_digits;
}
ostream& operator << (ostream& out,Bignum num){
	string temp=num.number;
	vector<Digit> digits=num.get_digits();
	for (int i = 0; i < digits.size(); ++i)
	{
		//cout<<digits[i].get_digit()<<' ';
	}
	//cout<<endl;
	//cout<<"remove_not_important_digits :"<<endl;
	remove_not_important_digits(num.digits_after,num.digits_befor,temp,num.sign_position);
	digits=num.get_digits();
	for (int i = 0; i < digits.size(); ++i)
	{
		//cout<<digits[i].get_digit()<<' ';
	}
	//cout<<endl;
	//cout<<"convert_digits_to_string :"<<endl;
	convert_digits_to_string(temp,digits,num.is_negative,num.get_signpos());
	out<<temp;
	return out;
}
istream& operator >> (istream& in,Bignum& num){
	//check valid numbers;
	in>>num.number;
	if (!valid_number(num.number))
	{
		throw runtime_error("invalid_number_excaption");
	}
	string temp=num.number;
	//cout<<"operator>> :"<<temp<<endl;
	convert_string_to_digits(num.digits_after,num.digits_befor,num.number);
	num.sign_position=num.number.size();
	for (int i = 0; i < temp.size(); ++i)
	{
		if(temp[i] == '.'){
			num.sign_position=i;
			break;
		}
	}
	remove_not_important_digits(num.digits_after,num.digits_befor,num.number,num.sign_position);
	if(num.number[0] == '-'){
		num.is_negative=true;
	}
	else{
		num.is_negative=false;
	}
	return in;
}
Bignum& Bignum::operator=(const Bignum& num){
	number=num.number;
	convert_string_to_digits(digits_after,digits_befor,number);
	sign_position=num.sign_position;
	remove_not_important_digits(digits_after,digits_befor,number,sign_position);
	is_negative=num.is_negative;
	return *this;
}
Bignum operator-(Bignum& num){
	string string_number;
	vector<Digit> digits=num.get_digits();
	convert_digits_to_string(string_number,digits,num.get_isnegative(),num.get_signpos());
	Bignum temp(string_number);
	//cout<<"after :"<<temp<<endl;
	if(temp.get_isnegative() && !(temp.get_iszero())){
		temp.set_isnegative(false);
		temp.set_signpos(temp.get_signpos()-1);
		return temp;
	}
	else if(!(temp.get_iszero())){
		temp.set_isnegative(true);
		temp.set_signpos(num.get_signpos()+1);
		return temp;
	}else{
		return temp;
	}
}
Digit& Bignum::operator[](int index){
	int item=0;
	string temp;
	vector<Digit> digits=this->get_digits();
	convert_digits_to_string(temp,digits,this->get_isnegative(),this->get_signpos());
	//valid_index ? and set []=
	if(valid_index(index,this->get_signpos(),temp.size(),this->get_isnegative())){
		//cout<<"valid index :"<<index<<endl;
		if(index >= 0){
			return digits_befor[index];
		}
		else{
			index=(-1)*index-1;
			return digits_after[index];
		}
	}
	else{
		//cout<<"invalid index :"<<index<<endl;
		if(index>0){
			int delta=index-digits_befor.size()+1;
			digits_befor.insert(digits_befor.end(),delta,Digit(0));
			this->set_signpos(this->get_signpos()+delta);
			return digits_befor[digits_befor.size()-1];
		}
		else{
			index=(-1)*index-1;
			int delta=index-(digits_after.size()-1);
			digits_after.insert(digits_after.end(),delta,Digit(0));
			return digits_after[digits_after.size()-1];
		}
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
void ABS(Bignum& other){
	//cout<<other<<endl;
	if(other.get_isnegative()){
		other=(-other);
	}
	//cout<<other<<endl;
}
void revert_number(Bignum& other,Bignum* this_number,bool other_negative,bool this_negative){
	if(other_negative){
		other=(-other);
	}
	if(this_negative){
		*this_number=(-(*this_number));
	}
}
void prepare_oprands(vector<Digit>& other_number_digits,vector<Digit>& first_number_digits,int& first_sign_position,int& other_sign_position,Bignum other,Bignum* first){
	bool first_nagative=first->get_isnegative();
	bool other_negative=other.get_isnegative();
	ABS(other);ABS(*first);
	first_sign_position=first->get_signpos();
	other_sign_position=other.get_signpos();
	//cout<<"1# :"<<first_sign_position<<' '<<other_sign_position<<endl;
	if(first_sign_position > other_sign_position){
		other_number_digits.insert(other_number_digits.begin(),(first_sign_position - other_sign_position) ,Digit(0));
		//other_sign_position+=((first_sign_position - other_sign_position));
		add_zero_digits_end(other_number_digits,first_number_digits);
	}
	if(first_sign_position < other_sign_position){
		first_number_digits.insert(first_number_digits.begin(),(other_sign_position - first_sign_position) ,Digit(0));
		//first_sign_position+=((other_sign_position - first_sign_position));
		add_zero_digits_end(other_number_digits,first_number_digits);	
	}
	if(first_sign_position == other_sign_position){
		add_zero_digits_end(other_number_digits,first_number_digits);
	}
	//cout<<"1 :"<<first_sign_position<<' '<<other_sign_position<<endl;
	other.set_signpos(other_sign_position);first->set_signpos(first_sign_position);
	revert_number(other,first,other_negative,first_nagative);
	first_sign_position=first->get_signpos();
	other_sign_position=other.get_signpos();
	//cout<<"2 :"<<first_sign_position<<' '<<other_sign_position<<endl;
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

vector<Digit> addition_act(vector<Digit>& first_number_digits,vector<Digit>& other_number_digits,int carry,int& sign_position){
	vector<Digit> result_number_digits;
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
	return result_number_digits;
}
vector<Digit> subtract(Bignum& other,Bignum* this_number,vector<Digit>& other_number_digits,vector<Digit>& first_number_digits,bool& is_negative,int& sign_position){
	vector<Digit> result_number_digits;
	bool other_negative=other.get_isnegative();
	bool this_negative=this_number->get_isnegative();
	ABS(other);
	ABS(*this_number);
	//cout<<other<<' '<<*this_number<<endl;
	if( *this_number == other){
		revert_number(other,this_number,other_negative,this_negative);
		result_number_digits.push_back(Digit(0));
		is_negative=false;
	}
	else if ( *this_number < other)
	{
		revert_number(other,this_number,other_negative,this_negative);
		is_negative=other_negative;
		sign_position=other.get_signpos();
		result_number_digits=subtraction_act(other_number_digits,first_number_digits);
	}
	else{
		revert_number(other,this_number,other_negative,this_negative);
		is_negative=this_negative;
		sign_position=this_number->get_signpos();
		result_number_digits=subtraction_act(first_number_digits,other_number_digits);
	}
	return result_number_digits;
}

Bignum Bignum::operator+(Bignum other){
	int first_sign_position , other_sign_position,sign_position;
	bool is_negative;
	remove_not_important_digits(this->digits_after,this->digits_befor,this->number,this->sign_position);
	remove_not_important_digits(other.digits_after,other.digits_befor,other.number,other.sign_position);
	vector<Digit> result_number_digits;
	vector<Digit> first_number_digits=this->get_digits();
	vector<Digit> other_number_digits=other.get_digits();
	//cout<<this->get_signpos()<<' '<<other.get_signpos()<<endl;
	prepare_oprands(other_number_digits,first_number_digits,first_sign_position,other_sign_position,other,this);
	sign_position=first_sign_position;
	if(other_sign_position > first_sign_position){
		sign_position=other_sign_position;
	}
	if(this->get_isnegative() == other.get_isnegative()){
		is_negative=this->get_isnegative();
		int carry=0;
		result_number_digits=addition_act(first_number_digits,other_number_digits,carry,sign_position);
	}
	else{
		result_number_digits=subtract(other,this,other_number_digits,first_number_digits,is_negative,sign_position);
		
	}
	reverse(result_number_digits.begin(),result_number_digits.end());
	string temp;
	//cout<<first_sign_position<<' '<<other_sign_position<<endl;
	//cout<<sign_position<<endl;
	convert_digits_to_string(temp,result_number_digits,is_negative,sign_position);
	//cout<<temp<<endl;
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
		return false;
	}
	if(this->get_isnegative() == false){
		int first_sign_position,other_sign_position;
		vector<Digit> first_number_digits=this->get_digits();
		vector<Digit> other_number_digits=other.get_digits();
		prepare_oprands(other_number_digits,first_number_digits,first_sign_position,other_sign_position,other,this);
		convert_digits_to_string(number1,first_number_digits,this->get_isnegative(),first_sign_position);
		convert_digits_to_string(number2,other_number_digits,this->get_isnegative(),other_sign_position);
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
		convert_digits_to_string(number1,first_number_digits,this->get_isnegative(),first_sign_position);
		convert_digits_to_string(number2,other_number_digits,this->get_isnegative(),other_sign_position);
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
Bignum& operator+=(Bignum& number,double double_number){
	Bignum temp(double_number);
	number+=temp;
	return number;
}
Bignum& operator+=(double& double_number,Bignum& number){
	Bignum temp(double_number);
	number+=temp;
	return number;	
}