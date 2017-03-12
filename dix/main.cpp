#include <iostream>
#include <cmath>
#include "VeryBigInt.h"
#include <cstdlib>
#include <fstream>
#include <bitset>
#include <vector>
void dixon(BigInt &N, unsigned long long int B, BigInt *mass, unsigned long long int *mass2);
BigInt euclid(BigInt &f, BigInt &g);
bool miller_rabin (BigInt &n);
using namespace std;
int main()
{	
	BigInt uno(1);
	uno.coef_[0] = 1;
	ifstream fin1;
	ifstream fin;
	int N1;
	int N;
	fin.open("input.txt");
	fin1.open("input2.txt");
	fin1>>N1;
	unsigned long long int *b = new unsigned long long int [N1];
	unsigned long long int *a = new unsigned long long int [N];
	for(int i = N1-1; i>=0; i--){
		fin1>>b[i];
	}
	fin>>N;
	for(int i = N-1; i>=0; i--){
		fin>>a[i];
	}
	fin1.close();
	BigInt big2(b, N1);
	BigInt big(a, N);
	/*big2.output();
	big.output();
	big = big.divide(big2,big);
	big.output();*/
	unsigned long long int h = 50;
	BigInt *mass = new BigInt[10];
	unsigned long long int *mass2 = new unsigned long long int[20];
	for(int i = 0; i<20;i++)
		mass2[i] = 1;
	for(int i = 0; i<10;i++)
		mass[i] = uno;
	if(miller_rabin(big2))
		cout<<"true"<<endl;
	ofstream fout;
	fout.open("output.txt");
	while(!((big2.size_==1)&&(big2.coef_[0] == 1))){
		dixon(big2, h,mass,mass2);
		big2.output();
	}
	for(int i = 0; i<20;i++)
		fout<<mass2[i]<<" * ";

	for(int i = 0; i<10;i++){
		for(int j = mass[i].size_ - 1; j>=0; j--){
			fout<<mass[i].coef_[j]<<" ";
		}
		fout<<" * ";
	}
	fout.close();
	return 0; 
}