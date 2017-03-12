#ifndef VERYBIGINT_H
#define VERYBIGINT_H
#include <iostream>
//#include "base.h"
using namespace std;
const unsigned long long int BASE = 4294967296;
class BigInt
{
public:
	int size_; 
	static  const int  maxSize_= 100000;
	unsigned long long int *coef_;  
	BigInt(unsigned long long int *A, int N);
	BigInt();
	~BigInt();
	BigInt(int N);
	BigInt(BigInt& A);
	bool iszero();
	void add(BigInt &a, BigInt &b);
	void minus(BigInt &a, BigInt &b);
	void multiply(BigInt &a, BigInt &b);
	void multiply(BigInt &a, unsigned long long int &b);
	BigInt divide(BigInt &a, BigInt &b);
	void power(BigInt &a, int b);
	void powmod(BigInt &a, BigInt &b, BigInt &N);
	BigInt res1(BigInt &a, int b);
	friend BigInt res(BigInt &a, int b);
	friend BigInt mod(BigInt &a, BigInt &b);
	unsigned long long int divide(BigInt &a, unsigned long long int &b);
	friend unsigned long long int mod(BigInt &a, unsigned long long int &b);
	void output();
	void zero();
	void zero2();
	BigInt operator = (BigInt& ob);
	BigInt operator + (BigInt& ob);//есть
	BigInt operator * (BigInt& ob);//есть
	BigInt operator * (unsigned long long int& ob);
	BigInt operator * (int& ob);//перегрузка 
	BigInt operator / (BigInt& ob);
	BigInt operator - (BigInt& ob);
	BigInt operator /  (int& ob);

	unsigned long long int operator %  (unsigned long& ob);
	BigInt operator ^ (int ob);
	bool operator < (BigInt& ob);
	bool isLess(BigInt& a, BigInt& b);	
};
#endif