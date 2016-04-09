#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>

class SegmentTree {
	private:
		vi st, lazy, A;
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

		int update( int p, int L, int R, int i, int j, int v ) {
			if( lazy[p] != 0 ) {
				st[p] = ( R - L + 1 )*lazy[p];
				if( L != R ) {
					lazy[ left(p) ] = lazy[p];
					lazy[ right(p) ] = lazy[p];
				}
		   		lazy[p] = 0;
		  	}
			if( i > R || j < L ) return st[p];
		  	if( L >= i && R <= j ) {
		  		st[p] = ( R - L + 1 )*v;
		  		if( L != R ) {
					lazy[ left(p) ] = v;
					lazy[ right(p) ] = v;
				}
	    		return st[p];
			}

			int p1 = update( left(p), L, ( L+R )/2, i, j, v );
			int p2 = update( right(p), ( L+R )/2 + 1, R, i, j, v );

			/*menor*/   //return st[p] = ( A[p1] <= A[p2] ) ? p1 : p2;
			/*maior*/   //return st[p] = ( A[p1] >= A[p2] ) ? p1 : p2;
			/*soma*/    return st[p] = p1 + p2;
			/*produto*/ //return st[p] = p1*p2;
		}

		int rmq( int p, int L, int R, int i, int j ) {
			if( i > R || j < L ) return -1;
			if( lazy[p] != 0 ) {
				st[p] = ( R - L + 1 )*lazy[p];
				if( L != R ) {
					lazy[ left(p) ] = lazy[p];
					lazy[ right(p) ] = lazy[p];
				}
				lazy[p] = 0;
			}
			if( L >= i && R <= j ) return st[p];

			int p1 = rmq( left(p), L, ( L + R )/2, i, j );
			int p2 = rmq( right(p), ( L + R )/2 + 1, R, i, j );

			if( p1 == -1 ) return p2;
			if( p2 == -1 ) return p1;
			
			/*menor*/  //return ( A[p1] <= A[p2] ) ? p1 : p2;
			/*maior*/  //return ( A[p1] >= A[p2] ) ? p1 : p2;
			/*soma*/   return p1 + p2;
			/*poduto*/ //return p1*p2;
		}

	public:
		SegmentTree( const vi &_A ) {
			A = _A; n = (int)A.size();
			st.assign( 4*n, 0 );
			lazy.assign( 4*n, 0 );
			build( 1, 0, n-1 );
		}
		int rmq( int i, int j ) { return rmq( 1, 0, n-1, i, j ); }
		void update( int i, int v ) { update( 1, 0, n-1, i, i, v ); }
		void update( int i, int j, int v ) { update( 1, 0, n-1, i, j, v ); }
		void print() {
			printf( "st: " );
			for( int i = 1; i <= 2*n; i++ )
				printf( "%d ", st[i] );
			printf( "\n" );
			printf( "lazy: " );
			for( int i = 1; i <= 2*n; i++ )
				printf( "%d ", lazy[i] );
			printf( "\n" );
		}
};

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8 }, i, j;
	vi A( arr, arr + 8 );
	SegmentTree st( A );
	scanf( "%d%d", &i, &j );
	printf( "RMQ( %d, %d ) = %d\n", i, j, st.rmq( i, j ) );
	st.print();
	printf( "UPDATE( 0, 3, 9 )\n" );
	st.update( 0, 3, 9 );
	st.print();
	printf( "RMQ( %d, %d ) = %d\n", i, j, st.rmq( i, j ) );
	st.print();
	printf( "UPDATE( 1, 1, 10 )\n" );
	st.update( 1, 1, 10 );
	st.print();

	return 0;
}