#include<bits/stdc++.h>
#define mod 998244353
#define LL long long
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define INF 0x3f3f3f3f
#define sf(x) scanf("%lld",&x)
#define sc(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define clr(x,n) memset(x,0,sizeof(x[0])*(n+5))
#define file(x) freopen(#x".in","r",stdin),freopen(#x".out","w",stdout)
using namespace std;
 
const int N = 32;
 
LL n,m,up;
 
struct Matrix
{
    LL a[N][N];
    Matrix(){memset(this,0,sizeof(Matrix));}
 
    Matrix operator *(const Matrix x) const
    {
        Matrix ans;
        for(int i=0;i<up;i++)
            for(int j=0;j<up;j++)
            {
                for(int k=0;k<up;k++)
                    ans.a[i][j]+=a[i][k]*x.a[k][j]%mod;
                ans.a[i][j]%=mod;
            }
        return ans;
    }
 
    friend Matrix operator ^(Matrix x,LL y)
    {
        Matrix ans;
        for(int i=0;i<up;i++)
            ans.a[i][i]=1;
        while(y)
        {
            if (y&1) ans=ans*x;
            x=x*x; y>>=1;
        }
        return ans;
    }
} x;
 
inline bool check(int x)
{
    assert(x<up);
    return __builtin_popcount(x)>=(m+1)/2;
}
 
void init()
{
    for(int i=0;i<up;i++)
    {
        if (!check(i)) continue;
        int j=i>>1;
        if (check(j)) x.a[i][j]=1;
        j|=up>>1;
        if (check(j)) x.a[i][j]=1;
    }
}
 
int main()
{
    while(cin >> n >> m)
    {
        LL ans = 0;
        x = Matrix();

        up = (1 << m); 
        init();
        
        x = x ^ (n - m);


        for (int i = 0; i < up; i++)
        {
            if (!check(i)) continue;
            for (int j = 0; j < up; j++)
            {
                if (!check(j)) continue;
                int tmp = (j << m) | i, flag = 0;
                for (int k = 1, s = up - 1; k < m; k++)
                    if (!check((tmp & (s << k)) >> k)) { flag = 1; break; }
                if (!flag)
                    ans = (ans + x.a[j][i]) % mod;
            }
        }
        cout << (ans + mod) % mod << endl;
    }
    return 0;
}