#include <bits/stdc++.h>
using namespace std;

#define MAXN 200005
#define ll long long
#define vi vector<int>
#define LSOne(s) ( s & (-s) )

class FenwickTree {
	private:
		vi ft;
	public:
		FenwickTree( int n ) { ft.assign( n + 1, 0 ); }
		int rsq( int b ) {
			int sum = 0;
			for( ; b; b -= LSOne( b ) ) sum += ft[b];
			return sum;
		}
		int rsq( int a, int b ) {
			return rsq( b ) - ( a == 1 ? 0 : rsq( a - 1 ) );
		}
		void update( int k, int v ) {
			for( ; k<(int)ft.size(); k += LSOne( k ) )
				ft[k] += v;
		}
};

int round( ll num ) {
	if( num < 0 ) return 0;
	if( num < 10 ) return 1;
	ll i = num%10;
	while( num >= 10 ) num /= 10;
	return i == num;
}

int main() {
	int n, q, t, j, k, v[MAXN];
	ll num;

	scanf( "%d%d", &n, &q );
	FenwickTree ft( n );
	for( int i = 1; i <= n; i++ ) {
		scanf( "%lld", &num );
		v[i] = round( num );
		if( v[i] ) ft.update( i, 1 );
	}
	for( int i = 0; i < q; i++ ) {
		scanf( "%d", &t );
		if( t == 1 ) {
			scanf( "%d%d", &j, &k );
			printf( "%d\n", ft.rsq( j, k ) );

		} else {
			scanf( "%d%lld", &j, &num );
			if( v[j] ) ft.update( j, -1 );
			v[j] = round( num );
			if( v[j] ) ft.update( j, 1 );
		}
	}

	return 0;
}