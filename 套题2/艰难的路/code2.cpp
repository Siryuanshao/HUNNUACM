#include <algorithm>
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;
const int N=1e6+100;
struct Point{
    int id;
    ll x,y;
    Point(ll _x,ll _y){x=_x;y=_y;}
    Point(){}
    Point operator-(const Point&b)const
    {
        return Point(x-b.x,y-b.y);
    }
    Point operator+(const Point&b)const
    {
        return Point(x+b.x,y+b.y);
    }
    ll operator^(const Point&b)const
    {
        return x*b.y-y*b.x;
    }
    ll operator*(const Point&b)const
    {
        return x*b.x+y*b.y;
    }
    bool operator<(const Point&b)
    {
        if(x==b.x)
        {
            if(y==b.y)
                return id<b.id;
            return y<b.y;
        }
        return x<b.x;
    }
    bool operator==(const Point&b)
    {
        return x==b.x&&y==b.y;
    }
}p[N];
Point ch[N];
bool Che(Point a,Point b,Point c)
{
    if(((c-a)^(b-a))<0)return 1;
    if(((c-a)^(b-a))==0)return c.id<b.id;
    return 0;
}
int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        {
            scanf("%lld%lld",&p[i].x,&p[i].y);
            p[i].id=i+1;
        }
        sort(p,p+n);
        int m=0;
        for(int i=0;i<n;i++)
        {
            if(i&&p[i]==p[i-1])continue;
            while(m>1&&Che(ch[m-2],ch[m-1],p[i]))
                m--;
            ch[m++]=p[i];
        }
        for(int i=0;i<m-1;i++)
            printf("%d ",ch[i].id);
        printf("%d\n",ch[m-1].id);
    }
    return 0;
}