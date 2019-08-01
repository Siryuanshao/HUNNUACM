#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+100;
const int MAXM=1e5+100;
int arr[MAXN];
int num[MAXN],unit;
int answer[MAXM];
struct qnode_t{
    int l,r,id;
    bool operator < (const qnode_t &b) const {
        if(l/unit!=b.l/unit) return l/unit<b.l/unit;
        else return r<b.r;
    }
}quest[MAXM];
void work(int n,int q){
    int temp=0;
    memset(num,0,sizeof(num));
    int L=quest[1].l,R=quest[1].r;
    for(int i=1;i<=L;i++)  //算第一个的左边 
    {
        if(num[arr[i]]==0) temp++;
        num[arr[i]]++;
    }
    for(int i=R;i<=n;i++)  //算第一个的右边 
    {
        if(num[arr[i]]==0) temp++;
        num[arr[i]]++;
    }
    answer[quest[1].id]=temp;
    for(int i=2;i<=q;i++)  //算第二个到第q个 
    {
        while(R<quest[i].r)
        {
            num[arr[R]]--;
            if(num[arr[R]]==0) temp--;
            R++;
        }
        while(R>quest[i].r)
        {
            R--;
            if(num[arr[R]]==0) temp++;
            num[arr[R]]++;
        }
        while(L<quest[i].l)
        {
            L++;
            if(num[arr[L]]==0) temp++;
            num[arr[L]]++;
        }
        while(L>quest[i].l)
        {
            num[arr[L]]--;
            if(num[arr[L]]==0) temp--;
            L--;
        }
       /* printf("L->R id :%d :%d %d %d\n",quest[i].id,L,R,temp);*/
        answer[quest[i].id]=temp;
    }
}
int main()
{
    int n,q;
    while(scanf("%d%d",&n,&q)!=EOF)
    {
        for(int i=1;i<=n;i++)
            scanf("%d",&arr[i]);
        for(int i=1;i<=q;i++)
        {
            quest[i].id=i;  //记录 id 
            scanf("%d%d",&quest[i].l,&quest[i].r);
        }
        unit=500+1;  //标准采用sqrt(n)，这里过不了，采用500+1反而能过 
        sort(quest+1,quest+q+1);
        work(n,q);
        for(int i=1;i<=q;i++)
            printf("%d\n",answer[i]);
    }
    return 0;
}