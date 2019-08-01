#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;

#define MAX 50100
#define Sum( l , r ) ( sum[ r ] - sum[ l - 1 ] )
bool f[MAX] ;
int u[MAX], sum[ MAX ], maxd = 0, n, A[ MAX ], B[ MAX ], C[ MAX ] ;

void Init(  )
{
    scanf( "%d", &n ) ;
    for ( int i = 0 ; i ++ < n ; )
    {
        scanf( "%d%d%d", &A[ i ], &B[ i ], &C[ i ] ) ;
        maxd = max( maxd, max( A[ i ], B[ i ] ) / C[ i ] ) ;
    }
    memset( f, true, sizeof( f ) ) ;
    f[ 0 ] = f[ 1 ] = false ;
    memset( u, 0, sizeof( u ) ) ;
    u[ 1 ] = 1 ;
    for ( int i = 1 ; i ++ < maxd ; ) if ( f[ i ] )
        {
            u[ i ] = - 1 ;
            for ( int j = i << 1 ; j <= maxd ; j += i )
            {
                if ( ! ( ( j / i ) % i ) ) u[ j ] = 0 ;
                else u[ j ] = u[ j / i ] * - 1 ;
                f[ j ] = false ;
            }
        }
    sum[ 0 ] = 0 ;
    for ( int i = 1 ; i <= maxd ; ++ i ) sum[ i ] = sum[ i - 1 ] + u[ i ] ;
}

void Solve(  )
{
    for ( int j = 0 ; j ++ < n ; )
    {
        int a, b, c, ans = 0 ;
        a = A[j], b = B[j], c = C[ j ] ;
        a /= c, b /= c ;
        if ( a > b ) swap( a, b ) ;
        for ( int i = 1 ; i <= a ; )
        {
            int pos = min( a / ( a / i ), b / ( b / i ) ) ;
            ans += Sum( i, pos ) * ( a / i ) * ( b / i ) ;
            i = pos + 1 ;
        }
        printf( "%d\n", ans ) ;
    }
}

int main(  )
{
    Init(  ) ;
    Solve(  ) ;
    return 0 ;
}