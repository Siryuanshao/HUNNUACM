#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 1e5+5;
const int INF = 0x3f3f3f3f;
int tree[maxn*4], set[maxn*4], a[maxn];
int cmd[maxn], L[maxn], R[maxn];
int n, m, p;

void pushup(int root)
{
    tree[root] = tree[root*2]+tree[root*2+1];
}

void pushdown(int root, int l, int r)
{
    int mid = (l+r)/2;
    if(set[root] != -1)
    {
        set[root*2] = set[root*2+1] = set[root];
        tree[root*2] = set[root]*(mid-l+1);
        tree[root*2+1] = set[root]*(r-mid);
        set[root] = -1;
    }
}

void update(int root, int l, int r, int pos, int val)
{
    if(l == r)
    {
        tree[root] = val;
        return ;
    }
    int mid = (l+r)/2;
    if(pos <= mid) update(root*2, l, mid, pos, val);
    else update(root*2+1, mid+1, r, pos, val);
    pushup(root);
}

void Set(int root, int l, int r, int i, int j, int val)
{
    if(i <= l && j >= r)
    {
        set[root] = val;
        tree[root] = val*(r-l+1);
        return ;
    }
    pushdown(root, l, r);
    int mid = (l+r)/2;
    if(i <= mid) Set(root*2, l, mid, i, j, val);
    if(j > mid) Set(root*2+1, mid+1, r, i, j, val);
    pushup(root);
}

int query(int root, int l, int r, int i, int j)
{
    if(i <= l && j >= r)
        return tree[root];
    pushdown(root, l, r);
    int sum = 0;
    int mid = (l+r)/2;
    if(i <= mid) sum += query(root*2, l, mid, i, j);
    if(j > mid) sum += query(root*2+1, mid+1, r, i, j);
    return sum;
}


bool judge(int x)
{
    memset(set, -1, sizeof(set));
    for(int i = 1; i <= n; i++)
    {
        if(a[i] >= x) update(1, 1, n, i, 1);
        else update(1, 1, n, i, 0);
    }
    for(int i = 1; i <= m; i++)
    {
        int num = R[i]-L[i]+1;
        int big = query(1, 1, n, L[i], R[i]);
        if(cmd[i])
        {
            if(L[i]+big-1 >= L[i])
                Set(1, 1, n, L[i], L[i]+big-1, 1);
            if(L[i]+big <= R[i])
                Set(1, 1, n, L[i]+big, R[i], 0);
        }
        else
        {
            if(R[i]-big+1 <= R[i])
                Set(1, 1, n, R[i]-big+1, R[i], 1);
            if(R[i]-big >= L[i])
                Set(1, 1, n, L[i], R[i]-big, 0);
        }
    }
    return query(1, 1, n, p, p);
}

int main(void)
{
    while(cin >> n >> m)
    {
        int l = INF, r = -INF;
        for(int i = 1; i <= n; i++)
            scanf("%d", &a[i]), l = min(l, a[i]), r = max(r, a[i]);
        for(int i = 1; i <= m; i++)
            scanf("%d%d%d", &cmd[i], &L[i], &R[i]);
        scanf("%d", &p);
        int ans = a[1];
        while(l <= r)
        {
            int mid = (l+r)/2;
            if(judge(mid)) ans = mid, l = mid+1;
            else r = mid-1;
        }
        printf("%d\n", ans);
    }
    return 0;
}
