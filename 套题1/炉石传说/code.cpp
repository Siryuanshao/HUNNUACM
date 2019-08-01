#include <bits/stdc++.h>
#define ll long long
#define show(x) cout<<#x<<"="<<x<<endl
using namespace std;
const int N=2e6;
struct Node{
    ll hp,da;
    bool operator<(const Node&b){
        return hp-da>b.hp-b.da;
    }
}cr[N];
ll fuck(ll a,ll b,int k,bool flag)
{
    if(!a)return 0;
    ll ret=0;
    if(!flag)//==
    {
        if(k<b)
            ret-=cr[k].hp;
        else
        {
            ret-=cr[k].da;
            ret-=cr[b-1].hp;
            ret+=cr[b-1].da;
        }
        ret+=(1<<a)*cr[k].hp;
    }
    else
    {
        if(k<b)
            ret-=cr[k].hp;
        else
        {
            ret-=cr[k].da;
        }
        ret+=(1<<a)*cr[k].hp;
    }
    return ret;
}
int main()
{
    ll n,a,b,ans,now;
    int pos;
    while(cin>>n>>a>>b)//a是翻倍 b是相等
    {
        pos=b;
        ans=0;
        for(int i=0;i<n;i++)
        {
            cin>>cr[i].hp>>cr[i].da;
        }
        sort(cr,cr+n);
        for(int i=0;i<b;i++)
        {
            if(cr[i].hp>cr[i].da)
                ans+=cr[i].hp;
            else
            {
                pos=i;
                break;
            }
        }
        for(int i=pos;i<n;i++)
            ans+=cr[i].da;
        if(b)
        {
            now=ans;
            for(int i=0;i<n;i++)
            {
                ans=max(ans,now+fuck(a,pos,i,pos!=b));
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}