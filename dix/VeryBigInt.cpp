#include "VeryBigInt.h"
#include <iostream>
#include <string>   
#include <cmath>
#include <cstddef>
int glob = 0;
//enum {BASE = 10};
int counter1 = 0;
BigInt::BigInt():
coef_(NULL)
{
	if(coef_ != NULL)
		delete [] coef_;
	size_= maxSize_;
	coef_ = new unsigned long long int [maxSize_];
	for(int i = 0; i<maxSize_; i++){
		coef_[i] = 0;
	}
	//sign_ = true;
}

BigInt::~BigInt() {
	//counter1++;
	//cout<<"counter1 = "<<counter1<<endl;
	//if(counter1 == 126)
	//	cout<<endl;
	//this->output();
	if(coef_ != NULL)
		delete[] coef_;
}

BigInt::BigInt(unsigned long long int *A, int N):
coef_(NULL)
{
	if(coef_ != NULL)
		delete[] coef_;
	size_=N;
	//sign_ = true;

	coef_ = new unsigned long long int [maxSize_];
	for(int i = 0; i<size_; i++){
		coef_[i] = A[i];
	}

}

BigInt::BigInt(int N):
coef_(NULL)
{
	if(coef_ != NULL)
		delete[] coef_;
	size_=N;
	coef_ = new unsigned long long int [maxSize_];
	for(int i = 0; i<maxSize_; i++){
		coef_[i] = 0;
	}
}

bool BigInt::iszero() {
	for (int i = 0; i < size_; i++)
		if (coef_[i] != 0) return false;
	return true;
}

BigInt BigInt::operator = (BigInt &A) { 
	if (this == &A) return *this; 
	if (size_ < A.size_ ) { 
		if(coef_ != NULL)
			delete [] coef_; 
		coef_ = new unsigned long long int[A.size_]; 
		size_=A.size_;
	} else 
	{
		for(int l=0; l<size_; l++) 
			coef_[l] = 0; 
		size_=A.size_;
	}
	for(int l=0; l<size_; l++) 
		coef_[l] = A.coef_[l]; 
	return *this; 
} 

BigInt::BigInt (BigInt &A):
coef_(NULL)
{ 
	BigInt *p = &A;
	if (this != p){
		if(coef_ != NULL)
			delete [] coef_;
		coef_ = new unsigned long long int[A.size_]; 
		size_=A.size_;
		for(int l=0; l<size_; l++) 
			coef_[l] = A.coef_[l]; 
	}
}

void
BigInt::add(BigInt &a, BigInt &b){ // удалять элементы или проверять на размер?
	if(a.size_<b.size_){
		add(b, a);
		return;
	}
	int carry = 0;
	int size = max(a.size_,b.size_)+1;
	coef_ = new unsigned long long int [size];
	size_=size;
	int i;
	for (i=0; i<a.size_; i++) {
		coef_[i] = a.coef_[i] + carry + (i < b.size_ ? b.coef_[i] : 0);
		if(coef_[i] >= BASE)
			carry = 1;
		else
			carry = 0;
		if(carry == 1)
			coef_[i] -= BASE;
	}
	if(carry == 1)
		coef_[i]=1;
	else
		size_--;
}



void BigInt::output(){
	for(int i = size_ - 1; i>=0; i--){
		cout<<coef_[i]<<" ";
	}
	cout<<endl;
}
int max_func(int a, int b)
{
	return a > b ? a : b;
}
void BigInt::zero(){
	delete coef_; 
	coef_ = new unsigned long long int[1]; 
	size_ = 1;
	coef_[0] = 0;
}
void BigInt::zero2(){
	int i;
	i = max_func(size_, maxSize_);
	for(i = 0; i < max_func(size_, maxSize_); i++)
		coef_[i] = 0;
}

void
BigInt::multiply(BigInt &a, BigInt &b){
	if(a.size_<b.size_){
		multiply(b, a);
		return;
	}
	if(coef_ != NULL)
		delete [] coef_;
	size_= maxSize_;
	coef_ = new unsigned long long int [maxSize_];
	for(int i = 0; i<maxSize_; i++){
		coef_[i] = 0;
	}
	unsigned long long int  temp;
	unsigned long long int j,i, carry;
	for ( i = 0; i < a.size_; i++) { 
		carry = 0;
		for (j = 0; j < b.size_; j++) { 
			temp = a.coef_[i] * b.coef_[j] + coef_[i+j] + carry;
			carry = temp/BASE;
			coef_[i+j] = temp - carry*BASE; 
		}
		coef_[i+j] = carry; 
	}
	i = a.size_ + b.size_ - 1; 
	if ( coef_[i] == 0 ) i--; 
	size_ = i+1; 
}
BigInt BigInt::operator + (BigInt& b){
	int carry = 0;
	BigInt c;
	int size = max(size_,b.size_);
	c.coef_ = new unsigned long long int [size];
	c.size_=size;
	for (int i=0; i<size; i++) {
		c.coef_[i] = coef_[i] + carry + (i < b.size_ ? b.coef_[i] : 0);
		if(c.coef_[i] >= BASE)
			carry = 1;
		else
			carry = 0;
		if(carry == 1)
			c.coef_[i] -= BASE;
	}
	return c;
}
BigInt BigInt::operator * (BigInt& ob){
	BigInt c(size_+ob.size_);
	unsigned long long int j,i, carry, temp;
	for ( i = 0; i < size_; i++) { 
		carry = 0;
		for (j = 0; j < ob.size_; j++) { 
			temp = coef_[i] * ob.coef_[j] + c.coef_[i+j] + carry;
			carry = temp/BASE;
			c.coef_[i+j] = temp - carry*BASE; 
		}
		c.coef_[i+j] = carry; 
	}
	i = size_ + ob.size_ - 1; 
	if ( c.coef_[i] == 0 ) i--; 
	c.size_ = i+1; 
	return c;
}

BigInt BigInt::operator * (unsigned long long int& ob){
	BigInt c(size_+1);
	unsigned long long int  i, temp;
	unsigned long long int carry = 0;
	for (i=0; i<size_; i++){
		temp = coef_[i]*ob + carry; 
		carry = temp / BASE;
		c.coef_[i] = temp - carry*BASE;
	}
	if (carry) { 
		c.coef_[i] = carry; 
		c.size_ = size_+1; 
	}  
	else  c.size_ = size_; 
	return c;
}
void BigInt::multiply(BigInt &a, unsigned long long int &b){
	unsigned long long int  i, temp;
	unsigned long long int carry = 0;
	for (i=0; i<a.size_; i++){
		temp = a.coef_[i]*b + carry; 
		carry = temp / BASE;
		coef_[i] = temp - carry*BASE;
	}
	if (carry) { 
		coef_[i] = carry; 
		size_ = a.size_+1; 
	}  
	else  size_ = a.size_; 
}
BigInt BigInt::operator * (int& ob){
	BigInt c(size_+1);
	long  i;
	unsigned long long temp;
	unsigned long long carry = 0;
	for (i=0; i<size_; i++){
		temp = coef_[i]*ob + carry; 
		carry = temp / BASE;
		c.coef_[i] = temp - carry*BASE;
	}
	if (carry) { 
		c.coef_[i] = carry; 
		c.size_ = size_+1; 
	}  
	else  c.size_ = size_; 
	return c;
}

BigInt BigInt::divide(BigInt &a, BigInt &b){
	if(b.size_ == 1){
		unsigned long long int temp = b.coef_[0];
		BigInt uno(1);
		uno.divide(a, temp);
		return uno;
	}

	if(isLess(a, b))
		return BigInt(1);
	BigInt temp_for_bas;
	BigInt a2(a.size_+1);
	bool negFlag;
	BigInt bas(1);// для степени 
	bas.coef_[0] = 1;
	unsigned long long int base = BASE;
	bas = bas * base;
	a2.coef_[a.size_] = 0;
	BigInt b2(b.size_);
	int n = b.size_;
	BigInt temp(n+1);
	BigInt temp10;
	BigInt zero_b(n+1);
	zero_b = b;
	BigInt q(a.size_ - b.size_ + 1);
	unsigned long long int d = BASE/(b.coef_[b.size_-1]+1);
	a2.multiply(a,d); 
	b2.multiply(b,d); 
	int j = a.size_ - b.size_;
	unsigned long long int  r1;
	unsigned long long int q1;


	while (j>=0){
		q1 = (a2.coef_[j+n]*BASE + a2.coef_[j+n-1])/b2.coef_[n-1];
		r1 = (a2.coef_[j+n]*BASE + a2.coef_[j+n-1])%(b2.coef_[n-1]);
		if((q1==BASE)||(q1*b2.coef_[n-2]>BASE*r1+a2.coef_[j+n-2]))
		{
			q1--;
			r1=r1+b2.coef_[n-1];
		}
		while (r1 < BASE) {
			if((q1==BASE)||(q1*b2.coef_[n-2]>BASE*r1+a2.coef_[j+n-2]))
			{
				q1--;
				r1=r1+b2.coef_[n-1];
			}
			else break;
		}
		for(int k = 0; k<n+1; k++){// перепись числа
			temp.coef_[k] = a2.coef_[k+j]; 

		}
		temp10.multiply(b2,q1);
		temp.size_ = n+1;
		if(isLess(temp,temp10)){
			negFlag = true;
			temp_for_bas =  bas^(n+1);
			temp = temp_for_bas + temp;
			temp.minus(temp,temp10);
		}
		else{
			negFlag = false;
			temp.minus(temp,temp10);
		}
		q.coef_[j] = q1;
		if(negFlag == true){
			q.coef_[j]--;
			temp = temp + b2;
		}
		for(int k = 0; k<n+1; k++)
			a2.coef_[k+j] = temp.coef_[k];
		j--;
	}
	while (q.coef_[q.size_ - 1] == 0)
		q.size_--;
	return q;
}
BigInt BigInt::operator / (int& ob){ // не надо учитывать знак?
	cout<<"short div"<<endl;
	unsigned long long int r = 0;
	unsigned long long int i, temp;
	BigInt q(size_);
	for(i = size_-1; i >= 0; i--) {
		temp = r*BASE + coef_[i];
		q.coef_[i] = temp / ob;
		r = temp%ob;
	}
	i = size_-1; 
	while ( (i>0) && (q.coef_[i]==0) ) i--; 
	q.size_ = i+1; 
	return q;
}

unsigned long long int mod(BigInt &a, unsigned long long int &b){
	unsigned long long int r = 0;
	unsigned long long int temp;
	int i;
	for(i = a.size_-1; i >= 0; i--) {
		temp = r*BASE + a.coef_[i];
		r = temp%b;
	}
	return r;
}

BigInt BigInt::res1(BigInt &a, int b){
	BigInt c;
	unsigned long long int b2 = b;
	BigInt res;
	BigInt temp;
	c.divide(a, b2);
	temp.multiply(c,b2);
	res = a - temp;
	*this = res;
	return 0;
}
BigInt res(BigInt &a, int b){
	BigInt c;
	unsigned long long int b2 = b;
	BigInt res;
	BigInt temp;
	c.divide(a, b2);
	temp.multiply(c,b2);
	res = a - temp;
	return res;
}
unsigned long long int BigInt::divide(BigInt &a, unsigned long long int &b){
	unsigned long long int r = 0;
	unsigned long long int temp;
	int i;
	for(i = a.size_-1; i >= 0; i--) {
		temp = r*BASE + a.coef_[i];
		coef_[i] = temp / b;
		r = temp%b;
	}
	i = a.size_-1; 
	while ( (i>0) && (coef_[i]==0) ) i--; 
	size_ = i+1; 
	return r;
}

unsigned long long int BigInt::operator % (unsigned long& ob){ // не надо учитывать знак?
	unsigned long long int r = 0;
	long long i, temp;
	BigInt q(size_);
	for(i = size_-1; i >= 0; i--) {
		temp = r*BASE + coef_[i];
		q.coef_[i] = temp / ob;
		r = temp%ob;
	}
	return r;
}
BigInt BigInt::operator ^ (int ob){
	long long n = ob;
	BigInt y(1);
	y.coef_[0] = 1;
	BigInt z = *this;
	int f;
	while(n > 0){
		f = n % 2;
		n = n/2;
		if(f == 1)
			y = z*y;
		z = z*z;}
	return y;
}

void BigInt::power(BigInt &a, int b){
	int n = b;
	BigInt y(1);
	y.coef_[0] = 1;
	BigInt z = a;
	int f;
	while(n > 0){
		f = n % 2;
		n = n/2;
		if(f == 1)
			y = z*y;
		z = z*z;}
	*this = y;
}

void BigInt::minus (BigInt& a, BigInt& b){
	long i;

	long long temp, carry=0; 
	for (i=0; i<b.size_; i++) { 

		if (a.coef_[i] < b.coef_[i] - carry) { 
			coef_[i] = a.coef_[i] + BASE - b.coef_[i] + carry;
			carry = -1; }
		else{
			coef_[i] = a.coef_[i] - b.coef_[i] + carry; 
			carry = 0; 
		}
	}
	for (; i<size_; i++) { 
		temp = a.coef_[i] + carry; 
		if (temp < 0) { 
			coef_[i] = temp + BASE; 
			carry = -1; 
		} else { 
			coef_[i] = temp; 
			carry = 0; 
		} 
	} 
	i = a.size_-1; 
	while ( (i>0) && (coef_[i]==0) ) i--; 
	size_ = i+1; 
} 
BigInt BigInt::operator - (BigInt& ob){
	long i;
	BigInt c(size_);
	long long temp, carry=0; 
	for (i=0; i<ob.size_; i++) { 
		//костыли для отрицательных чисел
		if (coef_[i] < ob.coef_[i] - carry) { 
			c.coef_[i] = coef_[i] + BASE - ob.coef_[i] + carry;
			carry = -1; }
		else{
			c.coef_[i] = coef_[i] - ob.coef_[i] + carry; 
			carry = 0; 
		}
	}
	for (; i<size_; i++) { 
		temp = coef_[i] + carry; 
		if (temp < 0) { 
			c.coef_[i] = temp + BASE; 
			carry = -1; 
		} else { 
			c.coef_[i] = temp; 
			carry = 0; 
		} 
	} 
	i = size_-1; 
	while ( (i>0) && (c.coef_[i]==0) ) i--; 
	c.size_ = i+1; 
	return c; 
} 
bool BigInt::operator < (BigInt &ob) 
{
	if (size_!=ob.size_)
		return size_<ob.size_;
	for (int i=size_-1; i>=0; i--)
	{
		if (coef_[i]!=ob.coef_[i])
			return coef_[i]<ob.coef_[i];
	}
	return false; 
} 
bool BigInt::isLess(BigInt &a, BigInt &b){ //a<b?

	int first1 = a.size_-1;
	while(a.coef_[first1] == 0)
		first1--;
	int first2 = b.size_-1;
	while(b.coef_[first2] == 0)
		first2--;
	if(first1<first2)
		return true;
	if(first1>first2)
		return false;
	for (int i=first1; i>=0; i--)
	{
		if (a.coef_[i]!=b.coef_[i])
			return (a.coef_[i]<b.coef_[i]);
	}
	return false;
}
BigInt mod(BigInt &a, BigInt &b){
	BigInt q;
	BigInt w;
	BigInt temp;
	q = q.divide(a,b);
	w.multiply(q,b);
	temp = a - w;
	return temp;
}
void BigInt::powmod(BigInt &a, BigInt &b, BigInt &N){
	BigInt n = b;
	BigInt y(1);
	y.coef_[0] = 1;
	BigInt z = a;
	BigInt temp;
	BigInt temp2;
	BigInt res_;
	unsigned long long int two = 2;
	while(!n.iszero()){
		res_.res1(n,2);
		n.divide(n,two);
		if((res_.size_ == 1)&&(res_.coef_[0] == 1)){
			temp2.multiply(y,z);
			y = temp2;
		}
		temp.multiply(z,z);
		z = temp;
		z = mod(z,N);
		y = mod(y,N);
	}
	*this = y;
}
