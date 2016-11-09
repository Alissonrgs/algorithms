int binary_search( int i, int f, int k ) {
	int m;

	while( i <= f ) {
		m = ( i + f ) / 2;

		if( v[m] < k )
			i = m+1;
		else if( v[m] > k )
			f = m-1;
		else
			return m;
	}
	return -1;
}