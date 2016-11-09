int pi[MAXN][25], d[MAXN];

int LCA( int U, int V ) {
	int D = 0;

	while( U != V ) {
		if( d[U] == d[V] )
			U = pi[U][1], V = pi[V][1], D += 2;

		else if( d[U] > d[V] ) {
			for( int i = 20; i >= 1; i-- )
				if( pi[U][i] != -1 && d[ pi[U][i] ] >= d[V] )
					U = pi[U][i], D += pow( 2, i-1 );

		} else {
			for( int i = 20; i >= 1; i-- )
				if( pi[V][i] != -1 && d[U] <= d[ pi[V][i] ] )
					V = pi[V][i], D += pow( 2, i-1 );
		}
	}
	return D;
}

for( V = 1; V <= n; V++ )
	for( int i = 2; i <= 20; i++ )
		if( pi[V][i-1] != -1 )
			pi[V][i] = pi[ pi[V][i-1] ][i-1];