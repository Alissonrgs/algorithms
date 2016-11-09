#define ll long long
#define vll vector<ll>

bitset<LIM> bs;
vll prime;

void sieve() {
    bs.set();
    bs[0] = bs[1] = false;
    prime.push_back(2);

    for( ll j = 2*2; j < LIM; j += 2 )
        bs[j] = false;

    for( ll i = 3; i < LIM; i += 2 )
        if( bs[i] ) {
            for( ll j = i*i; j < LIM; j += i )
                bs[j] = false;
        	
            prime.push_back( i );
        }
}

bool isPrime( ll N ) {
	if( N < LIM ) return bs[N];
	for( int i = 0; i < (int)prime.size(); i++ )
		if( N % prime[i] == 0 )
			return false;
	return true;
}