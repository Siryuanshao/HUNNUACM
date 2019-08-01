

https://www.cnblogs.com/CQzhangyu/p/6911914.html
// BZOJ4403,Lucas∂®¿Ì


#include <cstdio>
#include <cstring>
#include <iostream>
#define mod 1000003ll
typedef long long ll;
ll n,m;
ll jc[mod+10],jcc[mod+10];
ll pm(ll x,ll y)
{
    if(jcc[x])  return jcc[x];
    ll z=1;
    while(y)
    {
        if(y&1) z=z*x%mod;
        x=x*x%mod,y>>=1;
    }
    return jcc[x]=z;
}
ll dfs(ll a,ll b)
{
    if(!b)  return 1;
    if(a<b)  return 0;
    if(a<mod&&b<mod)  return jc[a]*pm(jc[b],mod-2)%mod*pm(jc[a-b],mod-2)%mod;
    return dfs(a%mod,b%mod)*dfs(a/mod,b/mod)%mod;
}
int main()
{
    int T,i;
    ll a,b;
    scanf("%d",&T);
    for(jc[0]=jcc[0]=1,i=1;i<mod;i++)    jc[i]=jc[i-1]*i%mod;
    while(T--)
    {
        scanf("%lld%lld%lld",&n,&a,&b);
        printf("%lld\n",(dfs(n+b-a+1,n)+mod-1)%mod);
    }
    return 0;
}
