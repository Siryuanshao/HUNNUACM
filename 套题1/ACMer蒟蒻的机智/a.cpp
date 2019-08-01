#include <iostream>
#define ll long long

using namespace std ;

ll n,k,ans = 0 ;
int main(  )
{
    cin >> n >> k ;
    for ( ll i = 1 ; i <= n ; )
    {
        if ( i > k )
        {
            ans += ( n - i + 1 ) * k ;
            break ;
        }
        ll pos = min( k / ( k / i ), n ) ;
        ans += ( k * ( pos - i + 1 ) - ( k / i ) * ( pos - i + 1 ) * ( i + pos ) / 2 ) ;
        i = pos + 1 ;
    }
    cout << ans << endl ;
    return 0 ;
}
