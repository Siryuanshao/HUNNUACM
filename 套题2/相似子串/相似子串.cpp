//bzoj 3230 相似子串
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ll long long
#define M(a) memset(a,0,sizeof a)
#define fo(i,j,k) for(i=j;i<=k;i++)
using namespace std;
const int mxn=100005;
int m,q;
char s[mxn];
ll cnt[mxn];
ll sum,len,u,v;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
struct node  //大家好我是黑箱 
{
    int st[mxn][30],rank[mxn],height[mxn];
    int a[mxn],b[mxn],x[mxn],y[mxn],sa[mxn];
    inline bool comp(int i,int j,int l)
    {
        return y[i]==y[j]&&(i+l>len?-1:y[i+l])==(j+l>len?-1:y[j+l]);
    }
    inline void work()
    {
        int i,j,k,p;m=128;
        fo(i,0,m) b[i]=0;
        fo(i,1,len) b[x[i]=a[i]]++;
        fo(i,1,m) b[i]+=b[i-1];
        for(i=len;i>=1;i--) sa[b[x[i]]--]=i;
        for(k=1;k<=len;k<<=1)
        {
            p=0;
            fo(i,len-k+1,len) y[++p]=i;
            fo(i,1,len) if(sa[i]>k) y[++p]=sa[i]-k;
            fo(i,0,m) b[i]=0;
            fo(i,1,len) b[x[y[i]]]++;
            fo(i,1,m) b[i]+=b[i-1];
            for(i=len;i>=1;i--) sa[b[x[y[i]]]--]=y[i];
            swap(x,y),p=2,x[sa[1]]=1;
            fo(i,2,len)
              x[sa[i]]=comp(sa[i-1],sa[i],k)?p-1:p++;
            if(p>len) break;
            m=p;
        }
        p=k=0;
        fo(i,1,len) rank[sa[i]]=i;
        for(i=1;i<=len;height[rank[i++]]=k)
          for(k?k--:0,j=sa[rank[i]-1];a[i+k]==a[j+k];k++);
    }
    inline void init()
    {
        int i,j;
        fo(i,1,len) st[i][0]=height[i];
        fo(j,1,28)
          fo(i,1,len) if((i+(1<<j)-1)<=len)
            st[i][j]=min(st[i][j-1],st[i+(1<<j-1)][j-1]);
    }
    inline int lcp(int x,int y)
    {
        if(x==y) return len-x+1;
        x=rank[x],y=rank[y];
        if(x>y) swap(x,y);
        x++;
        int k=0;
        while(x+(1<<k+1)<=y) k++;
        return min(st[x][k],st[y-(1<<k)+1][k]);
    }
}A,B;
int main()
{
    int i,j,k;
    len=read(),q=read();
    scanf("%s",s+1);
    fo(i,1,len) A.a[i]=s[i];
    fo(i,1,len) B.a[i]=s[len-i+1];
    A.work(),A.init();
    B.work(),B.init();
    sum=len*(len+1)/2;
    fo(i,1,len) sum-=A.height[i];
    fo(i,1,len)
      cnt[i]=cnt[i-1]+len-A.sa[i]+1-A.height[i];
    while(q--)
    {
        u=read(),v=read();
        if(v>sum)
        {
            printf("-1\n");
            continue;
        }
        int Tu=lower_bound(cnt+1,cnt+len+1,u)-cnt;
        int Tv=lower_bound(cnt+1,cnt+len+1,v)-cnt;
        int tu=u-cnt[Tu-1]+A.sa[Tu]+A.height[Tu]-1;
        int tv=v-cnt[Tv-1]+A.sa[Tv]+A.height[Tv]-1;
        ll start=min(A.lcp(A.sa[Tu],A.sa[Tv]),min(tu-A.sa[Tu]+1,tv-A.sa[Tv]+1));
        ll end=min(B.lcp(len-tu+1,len-tv+1),min(tu-A.sa[Tu]+1,tv-A.sa[Tv]+1));
        printf("%lld\n",start*start+end*end);
    }
    return 0;
}