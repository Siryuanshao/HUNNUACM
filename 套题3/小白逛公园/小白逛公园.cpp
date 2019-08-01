#include<iostream>
#include<cstdio>
#define N 500005
using namespace std;
int n,m,a[N];
struct tree{//用结构体便于保存
    int lmax,rmax,sum,maxn;
}tr[N<<2];
#define l(a) tr[a].lmax//懒癌患者专用
#define r(a) tr[a].rmax
#define s(a) tr[a].sum
#define m(a) tr[a].maxn
void push_up(int id){//更新
    s(id)=s(id<<1)+s(id<<1|1);
    l(id)=max(s(id<<1)+l(id<<1|1),l(id<<1));//左区间和+右区间左部
    r(id)=max(s(id<<1|1)+r(id<<1),r(id<<1|1));//右区间和+左区间右部
    m(id)=max(max(m(id<<1),m(id<<1|1)),r(id<<1)+l(id<<1|1));//左区间最大或右区间最大或
}                                                           //左区间右部+右区间左部
void build(int l,int r,int id){//正常建树
    if(l==r){
        l(id)=r(id)=s(id)=m(id)=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);
    build(mid+1,r,id<<1|1);
    push_up(id);
}
tree found(int nl,int nr,int l,int r,int id){//返回结构体
    if(nl<=l&&r<=nr)return tr[id];
    int mid=(l+r)>>1;                          //注意判断条件
    if(nr<=mid)return found(nl,nr,l,mid,id<<1);        //区间在左边
    else if(nl>mid)return found(nl,nr,mid+1,r,id<<1|1);//区间在右边
    else{                                              //区间跨越中点
        tree x=found(nl,nr,l,mid,id<<1),y=found(nl,nr,mid+1,r,id<<1|1),res;
        res.sum=x.sum+y.sum;
        res.lmax=max(x.sum+y.lmax,x.lmax);
        res.rmax=max(x.rmax+y.sum,y.rmax);
        res.maxn=max(max(x.maxn,y.maxn),x.rmax+y.lmax);
        return res;
    }
}
void add(int nx,int k,int l,int r,int id){//单点修改
    if(l==r){
        l(id)=r(id)=s(id)=m(id)=k;
        return;
    }
    int mid=(l+r)>>1;
    if(nx<=mid)add(nx,k,l,mid,id<<1);
    else add(nx,k,mid+1,r,id<<1|1);
    push_up(id);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]);
    build(1,n,1); 
    while(m--){
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if(op==1){
            if(x>y)swap(x,y);//VERY IMPORTANT!!!
            printf("%d\n",found(x,y,1,n,1).maxn);
        }
        else add(x,y,1,n,1);
    }
}