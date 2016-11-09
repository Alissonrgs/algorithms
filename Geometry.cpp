#define EPS 1e-9

struct point {
    double x, y;
    point() { x = y = 0.0; }
    point( double _x, double _y ) : x(_x), y(_y) {}
    bool operator <( point p )  const {
        if( fabs( x - p.x ) > EPS )
            return x < p.x;
        return y < p.y;
    }
    bool operator ==( point p ) {
        return fabs( x - p.x ) < EPS && fabs( y - p.y ) < EPS;
    }
};
double dist( point p1, point p2 ) { return hypot( p1.x - p2.x, p1.y - p2.y ); }

struct vec {
    double x, y;
    vec( double _x, double _y ) : x(_x), y(_y) {}
};
vec toVec( point a, point b ) { return vec( b.x - a.x, b.y - a.y ); }

double dot( vec a, vec b ) { return a.x * b.x + a.y * b.y; }
double norm_sq( vec v ) { return v.x * v.x + v.y * v.y; }

double cross( vec a, vec b ) { return a.x * b.y - a.y * b.x; }
bool ccw( point p, point q, point r ) { return cross( toVec( p, q ), toVec( p, r ) ) > 0; }
bool collinear( point p, point q, point r ) { return fabs( cross( toVec( p, q ), toVec( p, r ) ) ) < EPS; }

double distToLine( point p, point a, point b ) {
    vec ap = toVec( a, p ), ab = toVec( a, b );
    return fabs( cross( ap, ab ) )/sqrt( norm_sq( ab ) );
}

double distToLineSegment( point p, point a, point b ) {
    vec ap = toVec( a, p ), ab = toVec( a, b );
    double u = dot( ap, ab )/norm_sq( ab );
    if( u < 0.0 )
        return dist( p, a );
    if( u > 1.0 )
        return dist( p, b );

    return fabs( cross( ap, ab ) )/sqrt( norm( ab ) );
}

vector<point> P;

bool angleCmp( point a, point b ) { 
    if( collinear( pivot, a, b ) )
        return dist( pivot, a ) < dist( pivot, b );
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y,
           d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return ( atan2( d1y, d1x ) - atan2( d2y, d2x ) ) < 0;
}

vector<point> CH( vector<point> P ) {
    int i, j, n = (int)P.size();
 
    if( n <= 3 ) {
        if( !( P[0] == P[n-1] ) ) P.push_back( P[0] );
        return P;
    }
    int P0 = 0;
    for( i=1; i<n; i++ )
        if( P[i].y < P[P0].y || ( P[i].y == P[P0].y && P[i].x > P[P0].x ) )
            P0 = i;
 
    swap( P[0], P[P0] );
 
    pivot = P[0];
    sort( ++P.begin(), P.end(), angleCmp );
 
    vector<point> S;
    S.push_back( P[n-1] ); S.push_back( P[0] );
    i = 1;
    while( i < n ) {
        j = (int)S.size()-1;
        if( ccw( S[j-1], S[j], P[i] ) ) S.push_back( P[i++] );
        else S.pop_back();
    }
    return S;
}