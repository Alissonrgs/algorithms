#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define vll vector<ll>
#define LSOne(s) ( s & (-s) )

class FenwickTree {
	private:
		vll ft;
	public:
		FenwickTree( int n ) { ft.assign( n + 1, 0 ); }
		ll rsq( int b ) {
			ll sum = 0;
			for( ; b; b -= LSOne( b ) ) sum += ft[b];
			return sum;
		}
		ll rsq( int a, int b ) {
			return rsq( b ) - ( a == 1 ? 0 : rsq( a - 1 ) );
		}
		void update( int k, ll v ) {
			for( ; k<(int)ft.size(); k += LSOne( k ) )
				ft[k] += v;
		}
};

class FenwickTree {
	private:
		vll ft;
	public:
		FenwickTree( int n ) { ft.assign( n+1, 0 ); }
		ll rsq( int b ) {
			ll sum = 0;
			for( ; b; b -= LSOne( b ) ) sum += ft[b];
			return sum;
		}
		ll rsq( int a, int b ) {
			return rsq( b ) - ( a == 1 ? 0 : rsq( a - 1 ) );
		}
		void update( int p, ll v ) {
			for( ; p<(int)ft.size(); p += LSOne( p ) )
				ft[p] += v;
		}
		void update( int a, int b, ll v ) {
			update( a, v );
			update( b+1, -v );
		}
};

class FenwickTree {
	private:
		vll ft1, ft2;
	public:
		FenwickTree( int n ) {
			ft1.assign( n+1, 0 );
			ft2.assign( n+1, 0 );
		}
		ll rsq( vll &ft, int b ) {
			ll sum = 0;
			for( ; b; b -= LSOne( b ) ) sum += ft[b];
			return sum;
		}
		ll rsq( int b ) {
			return rsq( ft1, b )*b - rsq( ft2, b );
		}
		ll rsq( int a, int b ) {
			return rsq( b ) - ( a == 1 ? 0 : rsq( a - 1 ) );
		}
		void update( vll &ft, int p, ll v ) {
			for( ; p<(int)ft.size(); p += LSOne( p ) )
				ft[p] += v;
		}
		void update( int a, int b, ll v ) {
			update( ft1, a, v );
			update( ft1, b+1, -v );
			update( ft2, a, v*( a-1 ) );
			update( ft2, b+1, -v*b );
		}
};