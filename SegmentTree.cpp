#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define vll vector<ll>

class SegmentTree {
	private:
		vll st, A;
		int n;
		int left( int p ) { return p << 1; }
		int right( int p ) { return ( p << 1 ) + 1; }

		void build( int p, int L, int R ) {
			if( L == R )
				/*menor*/        //st[p] = L;
				/*soma,produto*/ st[p] = A[L];
			else {
				build( left(p), L, ( L + R )/2 );
				build( right(p), ( L + R )/2 + 1, R );
				int p1 = st[ left(p) ], p2 = st[ right(p) ];
				/*menor*/   //st[p] = ( A[p1] <= A[p2] ) ? p1 : p2;
				/*maior*/   //st[p] = ( A[p1] >= A[p2] ) ? p1 : p2;
				/*soma*/    st[p] = p1 + p2;
				/*produto*/ //st[p] = p1*p2;
			}
		}

		ll update( int p, int L, int R, int i, int j, ll v ) {
			if( i > R || j < L ) return st[p];
		  	if( L == R ) {
	    		A[L] = v;
	    		return st[p] = A[L];
			}
			ll p1 = update( left(p), L, ( L+R )/2, i, j, v );
			ll p2 = update( right(p), ( L+R )/2 + 1, R, i, j, v );

			/*menor*/   //return st[p] = ( A[p1] <= A[p2] ) ? p1 : p2;
			/*maior*/   //return st[p] = ( A[p1] >= A[p2] ) ? p1 : p2;
			/*soma*/    return st[p] = p1 + p2;
			/*produto*/ //return st[p] = p1*p2;
		}

		ll rmq( int p, int L, int R, int i, int j ) {
			if( i > R || j < L ) return -1;
			if( L >= i && R <= j ) return st[p];

			ll p1 = rmq( left(p), L, ( L + R )/2, i, j );
			ll p2 = rmq( right(p), ( L + R )/2 + 1, R, i, j );

			if( p1 == -1 ) return p2;
			if( p2 == -1 ) return p1;
			
			/*menor*/  //return ( A[p1] <= A[p2] ) ? p1 : p2;
			/*maior*/  //return ( A[p1] >= A[p2] ) ? p1 : p2;
			/*soma*/   return p1+p2;
			/*poduto*/ //return p1*p2;
		}

	public:
		SegmentTree( const vll &_A ) {
			A = _A; n = (int)A.size();
			st.assign( 4*n, 0 );
			build( 1, 0, n-1 );
		}
		ll rmq( int i, int j ) { return rmq( 1, 0, n-1, i, j ); }
		void update( int i, ll v ) { update( 1, 0, n-1, i, i, v ); }
		void update( int i, int j, ll v ) { update( 1, 0, n-1, i, j, v ); }
};

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7 }, i, j;
	vll A( arr, arr + 7 );
	SegmentTree st( A );
	scanf( "%d%d", &i, &j );
	printf( "RMQ( %d, %d ) = %d\n", i, j, st.rmq( i, j ) );
	printf( "UPDATE( 0, 2 ) = %d\n", st.update( 0, 2 ) );
	printf( "RMQ( %d, %d ) = %d\n", i, j, st.rmq( i, j ) );

	return 0;
}