#include <bits/stdc++.h>
using namespace std;

#define vc vector<caractere>
#define LSOne(s) ( s & (-s) )

struct caractere {
	int l[26];
	caractere() { memset( l, 0, sizeof l ); }
	caractere operator-( const caractere &B ) const {
		caractere C;
		for( int j = 0; j < 26; j++ ) C.l[j] = l[j] - B.l[j];
		return C;
	}
};

class FenwickTree {
	private:
		vc ft;
	public:
		FenwickTree( int n ) { ft.assign( n+1, caractere() ); }
		caractere rsq( int b ) {
			caractere sum;
			for( ; b; b -= LSOne( b ) )
				for( int j = 0; j < 26; j++ )
					sum.l[j] += ft[b].l[j];
			return sum;
		}
		caractere rsq( int a, int b ) {
			caractere c;
			return rsq( b ) - ( a == 1 ? c : rsq( a - 1 ) );
		}
		void update( int k, int i, int v ) {
			for( ; k < (int)ft.size(); k += LSOne( k ) )
				ft[k].l[i] += v;
		}
};

int main() {
	int n, q, t, j, k, impar;
	char c;
	string s;

	cin >> n >> q >> s;
	FenwickTree ft( n );
	for( int i = 0; i < n; i++ )
		ft.update( i+1, (int)s[i]-'a', 1 );

	for( int i = 0; i < q; i++ ) {
		cin >> t;
		if( t == 1 ) {
			cin >> j >> c;
			ft.update( j, (int)s[j-1]-'a', -1 );
			ft.update( j, (int)c-'a', 1 );
			s[j-1] = c;

		} else {
			cin >> j >> k;
			caractere C = ft.rsq( j, k );
			impar = 0;
			for( int l = 0; l < 26; l++ )
				impar += C.l[l]&1;
			cout << ( impar > 1 ? "no" : "yes" ) << endl;
		}
	}

	return 0;
}