#include <bits/stdc++.h>
using namespace std;

#define LIM 100000000
#define vi vector<int>
#define ull unsigned long long

bitset<LIM+10> bs;
vi prime;

void sieve() {
    bs.set();
    bs[0] = bs[1] = false;
    prime.push_back(2);

    for( ull j = 2*2; j < LIM; j += 2 )
        bs[j] = false;

    for( ull i = 3; i < LIM; i += 2 )
        if( bs[i] ) {
            for( ull j = i*i; j < LIM; j += i )
                bs[j] = false;
        	
            prime.push_back( (int)i );
        }
}

bool isPrime( ull N ) {
	if( N <= LIM ) return bs[N];
	for( int i = 0; i < (int)prime.size(); i++ )
		if( N % prime[i] == 0 )
			return false;
	
	return true;
}

int main() {
	sieve();

	cout << "Qantidade de primos gerados: " << prime.size() << endl; 
	for( int i = 0; i < 20/*prime.zie()*/; i++ )
		cout << prime[i] << " ";
	cout << endl;

	return 0;
}