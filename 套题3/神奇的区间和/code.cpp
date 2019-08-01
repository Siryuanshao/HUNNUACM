#include <iostream>

using namespace std;
const int maxn=200010;
int father[maxn],Rank[maxn],n;
void init()
{
    for(int i=0;i<=n;i++)
    {
        father[i]=i;
        Rank[i]=0;
    }
}
int Find(int x)
{
    int tx=father[x];
    if(x==tx)return x;
    father[x]=Find(father[x]);
    Rank[x]+=Rank[tx];
    return father[x];
}
bool unite(int x,int y,int z)
{
    int tx=Find(x);
    int ty=Find(y);
    if(tx==ty)
    {
        if(Rank[x]==Rank[y]-z)return 0;
        return 1;
    }
    father[ty]=tx;
    Rank[ty]=Rank[x]-Rank[y]+z;
    return 0;
}
int main()
{
    int m,x,y,ans,z,T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m;
        ans=0;
        init();
        while(m--)
        {
            cin>>x>>y>>z;
            x--;
            ans+=unite(x,y,z);
        }
        if(ans)
            cout<<"false"<<endl;
        else
            cout<<"true"<<endl;
//        cout<<ans<<endl;
    }
    return 0;
}
