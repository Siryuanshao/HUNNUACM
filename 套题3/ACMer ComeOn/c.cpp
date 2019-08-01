#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std ;

#define Sum( l , r ) ( sum[ r ] - sum[ l - 1 ] )
#define MAX 51000

int n , A[ MAX ] , B[ MAX ] , C[ MAX ] , D[ MAX ] , K[ MAX ] ;
int u[ MAX ] , sum[ MAX ] , maxd = 0 ;
bool f[ MAX ] ;

void Init(  ) {
    scanf( "%d" , &n ) ;
    for ( int i = 0 ; i ++ < n ; )
    {
        scanf( "%d%d%d%d%d" , A + i , B + i , C + i , D + i , K + i ) ;
        maxd = max( maxd , max( B[ i ] , D[ i ] ) / K[ i ] ) ;
    }
    memset( f , true , sizeof( f ) ) ;
    memset( u , 0 , sizeof( u ) ) ;
    memset( sum , 0 , sizeof( sum ) ) ;
    f[ 0 ] = f[ 1 ] = false , u[ 1 ] = 1 ;
    for ( int i = 1 ; i ++ < maxd ; ) if ( f[ i ] )
    {
        u[ i ] = - 1 ;
        for ( int j = i << 1 ; j <= maxd ; j += i )
        {
            if ( ! ( ( j / i ) % i ) ) u[ j ] = 0 ; else u[ j ] = u[ j / i ] * - 1 ;
            f[ j ] = false ;
        }
    }
    for ( int i = 0 ; i ++ < maxd ; ) sum[ i ] = sum[ i - 1 ] + u[ i ] ;
}

int query( int a , int b ) {
    int ans = 0 ;
    for ( int i = 1 ; i <= min( a , b ) ; )
    {
        int pos = min( a / ( a / i ) , b / ( b / i ) ) ;
        ans += Sum( i , pos ) * ( a / i ) * ( b / i ) ;
        i = pos + 1 ;
    }
    return ans ;
}

void Solve(  )
{
    for ( int i = 0 ; i ++ < n ; )
    {
        A[ i ] -- , C[ i ] -- ;
        A[ i ] /= K[ i ] , B[ i ] /= K[ i ] , C[ i ] /= K[ i ] , D[ i ] /= K[ i ] ;
        printf( "%d\n" , query( B[ i ] , D[ i ] ) - query( A[ i ] , D[ i ] ) - query( B[ i ] , C[ i ] ) + query( A[ i ] , C[ i ] ) ) ;
    }
}

int main(  )
{
    Init(  ) ;
    Solve(  ) ;
    return 0 ;
}
