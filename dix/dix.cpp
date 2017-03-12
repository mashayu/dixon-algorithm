#include <iostream>
#include <fstream>
#include "VeryBigInt.h"
#include <bitset>
#include<time.h>
#include<cmath>
#include<stdlib.h>
using namespace std;
int counter = 0;
	int counter2 = 0;
BigInt euclid(BigInt &f, BigInt &g){ // может быть сделать деление бигинтов с остатком сюда?
	if(f.iszero())
		return g;
	if(g.iszero())
		return f;
	BigInt r_1;
	BigInt r_0;
	if(f<g){
		r_1 = g;
		r_0 = f;
	}
	else
	{
		r_1 = f;
		r_0 = g;
	}
	BigInt r;
	BigInt temp;
	BigInt temp2;
	while(true){
		temp = temp.divide(r_1,r_0);
		temp2.multiply(r_0, temp); // можно записать в 1 строку после minus
		r = r_1 - temp2;
		if(r.iszero()) {
			return r_0;}
		r_1 = r_0;
		r_0 = r;
	}
}


void transform_num (BigInt &n, int & p, BigInt & q)
{
	unsigned long long int two = 2;
	int p_res = 0;
	while (res(n,2).iszero())
	{
		++p_res;
		n.divide(n,two);
	}

	p = p_res;
	q = n;
}

bool miller_rabin (BigInt &n)
{BigInt b;
int i;
srand( time( 0 ) );
b.size_ = n.size_;
b.coef_[0]=1 + rand() % (BASE-1);
for(i = 1; i < n.size_; i++)
b.coef_[i]=rand()%(BASE);
while(b.coef_[n.size_-1] >= n.coef_[n.size_-1])
b.coef_[n.size_-1]=rand()%BASE;
while(b.coef_[b.size_ -1] == 0){
	b.size_--;
}
BigInt one(1);
one.coef_[0] = 1;
BigInt two(1);
two.coef_[0] = 2;
// сначала проверяем тривиальные случаи
if ((n.size_==1)&&(n.coef_[0] == 2))
return true;
if (n < two || (res(n,2).iszero()))
return false;
BigInt g;
BigInt temp;
BigInt temp2;
// проверяем, что n и b взаимно просты (иначе это приведет к ошибке)
// если они не взаимно просты, то либо n не просто, либо нужно увеличить b
g = euclid(n,b);
while(!((g - one).iszero())){
	if (g<n)
		return false;
	temp.add(b,one);
	b = temp;
	g = euclid(n,b);
}
// разлагаем n-1 = q*2^p
BigInt n_1 = n;
BigInt n1;
n_1 = n_1-one;
n1 = n_1;
int p;
BigInt q;
transform_num (n_1, p, q);

// вычисляем b^q mod n, если оно равно 1 или n-1, то n, вероятно, простое
BigInt rem;
rem.powmod(b,q,n);
if (((rem.size_ == 1)&&(rem.coef_[0] == 1)) || ((rem - n1).iszero()))
return true;
temp = rem;
n_1 = n-one;
for (int i=1; i<p; i++)
{
	rem.power(rem, 2);
	rem = mod(rem, n);	
	if ((rem-n1).iszero())
		return true;
}

return false;

}



void swap(int **a, int row1, int row2, int m){
	int w;
	for(int i = 0; i < m; i++){
		w = a[row1][i];
		a[row1][i] = a[row2][i];
		a[row2][i] = w;
	}
}

void swap_col (int **a, int col1, int col2, int n){
	int w;
	for(int i = 0; i < n; i++){
		w = a[i][col1];
		a[i][col1] = a[i][col2];
		a[i][col2] = w;
	}
}
bool xor(int **a, int row1, int row2, int m){
	bool flag = false;
	for(int i = 0; i < m; i++){
		if(((a[row1][i] == 1)&&(a[row2][i] == 1)) || ((a[row1][i] == 0) && (a[row2][i] == 0)))
			a[row2][i] = 0;
		else{
			a[row2][i] = 1;
			flag = true;
		}
	}
	return flag;
}
void showMatrix(int **a, int m, int n){
	for (int count_row = 0; count_row < m; count_row++)
	{
		for (int count_column = 0; count_column < n; count_column++)
			cout << a[count_row][count_column] << "   ";
		cout << endl;
	}
}
void gauss(int n, int m, int **a, int *ans, int *where_){
	for(int j = 0; j < m; j++)
		where_[j] = j;
	int sum = 0;
	bool flag;
	int i,j;
	int r;
	int q;
	int temp;
	bool flag2 = false;
	int nullStr = 0;
	for(i = 0; i<(n-nullStr); i++){
		flag2 = false;
		for(j=0;j<m; j++)
			if(a[i][j] == 1)
				flag2 = true;
		if(flag2 == false){
			nullStr++;
			for(q = i; q < n-1; q++)
				swap(a, q, q+1, m);
			i--;
		}
	}
	for (int col=0, row=0; col<m && row<(n-nullStr); ++col) {
		for (int i=row; i<n; ++i)
			if (a[i][col] == 1) {
				swap (a, i, row, m);
				break;
			}
			if (a[row][col] == 0){
				for(r = col+1; r < m; r++){
					if(a[row][r] == 1){
						//	cout<<"SWAPING COLOMNS: "<<r<<"  "<<col<<endl;
						swap_col(a, r, col, n);
						temp = where_[r];
						where_[r] = where_[col];
						where_[col] = temp;
						break;
					}
				}
				col--;
				continue;}
			for (int i=0; i<n; ++i)
				if ((i != row) && (a[i][col] == 1)){
					flag = xor(a,row,i,m);
					if(flag == false){
						nullStr++;
						for(q = i; q < n-1; q++){
							swap(a, q, q+1, m);
						}
						i--;
					}
				}
				++row;
	}
	i = m - 1;
	ans[i] = 1;

	// добавить проверку, что последний столбец не нулевой?

	for(i = 0; i < m - 1; i++){
		ans[i] = a[i][m-1];
	}

}

bool isprime(BigInt &N){
	return miller_rabin(N);
}
void dixon(BigInt &N, unsigned long long int B, BigInt *mass, unsigned long long int *mass2){
	//int counter = 0;
	//int counter2 = 0;
	//BigInt *mass = new BigInt[10];
	//unsigned long long int *mass2 = new unsigned long long int[10];
	cout<<"NEW DIXON_______________"<<endl;
	ifstream fin;
	ofstream fout;
	fout.open("output.txt");
	fin.open("primes.txt");
	BigInt uno(1);
	BigInt temp;
	BigInt temp2;
	unsigned long long int tmp3;
	BigInt a;
	bool flag2;
	int nullStr = 0;
	int h = 0;
	BigInt S(1);
	S.coef_[0] = 1;
	BigInt T(1);
	T.coef_[0] = 1;
	uno.coef_[0] = 1;
	unsigned long long int *P = new unsigned long long int[B/2];
	unsigned long long int p_i;
	unsigned long long int d, i, w;
	int j;
	int NumOfPrimes = 0;
	fin>>p_i;

	if(isprime(N)){
		cout<<"prime ";
		N.output();
		mass[counter] = N;
				counter++;
		N.size_ = 1;
		N.coef_[0] = 1;
		return;}
	while(p_i<B){ //можно убрать p_i; 
		if(mod(N,p_i) == 0){
			cout<<"look! It's (0)"<<p_i<<endl;
			cout<<"g = "<<p_i<<endl;
			//fout<<p_i;
			mass2[counter2] = p_i;
			counter2++;
			temp.divide(N,p_i);

			N = temp;
			return;

		}
		P[NumOfPrimes] = p_i;
		fin>>p_i;
		NumOfPrimes++;
	}
	int **A= new int* [NumOfPrimes]; 
	for (int count = 0; count < NumOfPrimes; count++)
		A[count] = new int [NumOfPrimes+1]; 

	int **ABit= new int* [NumOfPrimes]; 
	for (int count = 0; count < NumOfPrimes; count++)
		ABit[count] = new int [NumOfPrimes+1];

	int *alpha = new int [NumOfPrimes];
	int *where_ = new int [NumOfPrimes+1];
	for(int j = 0; j < NumOfPrimes+1; j++)
		where_[j] = j;
	int *ans = new int [NumOfPrimes+1];
	int *gamma = new int [NumOfPrimes];
	srand( time( 0 ) );
	BigInt b (N.size_);
	BigInt g;
	BigInt *a_vect = new BigInt[NumOfPrimes+1];
	BigInt *b_vect = new BigInt[NumOfPrimes+1];
	while(h<=NumOfPrimes){
		a.zero();
		while( a.iszero()){
			b.size_ = N.size_;
			b.coef_[0]=2 + rand() % (BASE-2);
			for(i = 1; i < N.size_; i++)
				b.coef_[i]=rand()%(BASE);

			while(b.coef_[N.size_-1] >= N.coef_[N.size_-1])
				b.coef_[N.size_-1]=rand()%BASE;
			while(b.coef_[b.size_ -1] == 0){
				b.size_--;
			}
			if((b.size_ == 2) && (b.coef_[1] == 0))
				b.size_ = 1;
			g = euclid(b, N);
			if(uno<g){
				cout<<"look! It's (1) ";
				g.output();
				//for(int i = g.size_ - 1; i>=0; i--){
					//fout<<g.coef_[i]<<" ";
				//}
				//fout<<" * ";
				mass[counter] = g;
				counter++;
				temp = temp.divide(N,g);
				N = temp;
				return;
			}

			a.power(b,2);
			temp = temp.divide(a, N);
			temp2.multiply(temp, N);
			a = a - temp2;
		}
		for(i = 0; i< NumOfPrimes; i++){
			alpha[i] = 0;
			while( mod(a, P[i]) == 0){
				alpha[i]++;
				a.divide(a, P[i]);
			}
		}
		if((a.size_ == 1) && (a.coef_[0] == 1)){
			a_vect[h] = a;
			b_vect[h] = b;
			cout<<"b = ";
			b.output();
			for(j = 0; j<NumOfPrimes; j++)
			{	A[j][h] = alpha[j];

			}
			h++;
		}
	}
	for (int count_row = 0; count_row < NumOfPrimes; count_row++) // копирование матриц. можно сюда провекрку на нулевые ст.?
	{
		for (int count_column = 0; count_column < NumOfPrimes+1; count_column++)
			ABit[count_row][count_column] = A[count_row][count_column]%2;
	}
	//showMatrix(ABit, NumOfPrimes, NumOfPrimes+1);	
	gauss(NumOfPrimes, NumOfPrimes+1, ABit, ans, where_);
	fin.close();
	for(w = 0; w<NumOfPrimes; w++){
		gamma[w] = 0;
		for(d = 0; d < NumOfPrimes+1; d++)
			gamma[w] = gamma[w] + 0.5*A[w][where_[d]]*ans[d];
	}
	for(i = 0; i < NumOfPrimes + 1; i++)
		if(ans[i] == 1){

			temp.multiply(S, b_vect[where_[i]]);
			S = temp;
		}
		for(i = 0; i < NumOfPrimes; i++){
			tmp3 = (pow((double)P[i],gamma[i]));
			temp2.multiply(T, tmp3);
			T = temp2;
		}
		temp.add(T,S);
		g = euclid(temp, N);
		if(g<N){
			cout<<"look! It's (2) ";
			g.output();
			//for(int i = g.size_ - 1; i>=0; i--){
			//	fout<<g.coef_[i]<<" ";
			//}
			//fout<<" * ";
			mass[counter] = g;
				counter++;
			temp = temp.divide(N,g);
			N = temp;
			return;
		}
		else
			return;
}

