#include <bits/stdc++.h>
#define llt long long 
using namespace std;

int T,n,m;
int BLOCK_SIZE;
struct node {
    int l,r,id;
    node(int l, int r, int id): l(l), r(r), id(id){}
    bool operator < (const node &rhs) const{
        int ln = l / BLOCK_SIZE;
        int rn = rhs.l / BLOCK_SIZE;
        return ln < rn || ( ln == rn && r < rhs.r );
    }
};

vector<node> query;
int a[20005],L,R;
llt ans[20005], cnt[20005], sum[20005];
llt cursum;

inline int lowbit(int x) {return x&(-x);}

void ins(int k){
    for(int i=a[k];i <= 20005; i+=lowbit(i)) {
        cnt[i] += 1; 
        sum[i] += a[k];
    }

    int tmpC = 0;
    int preSum = 0;
    for(int i=a[k];i > 0;i-=lowbit(i)) {
        tmpC += cnt[i];
        preSum += sum[i];
    }
    cursum +=a[k] * (R-L+1-tmpC) + preSum;
}

void rmv(int k){
    for(int i=a[k];i <= 20005; i+=lowbit(i)) {
        cnt[i] -= 1; //sgn 為 1，增加； sgn為 0 ， 刪除；
        sum[i] -= a[k];
    }

    int tmpC = 0;
    int preSum = 0;
    for(int i=a[k];i > 0;i-=lowbit(i)) {
        tmpC += cnt[i];
        preSum += sum[i];
    }
    cursum -= a[k] * (R-L+1-tmpC) + preSum;
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        query.clear();
        BLOCK_SIZE = sqrt(n);
        for (int i = 1; i <= n; i++) 
            scanf("%d",&a[i]);
        for (int i = 1; i <= m; i++) {
            int l,r;
            scanf("%d%d",&l,&r);
            query.push_back(node(l,r,i));
        }
        sort(query.begin(), query.end());
        
        L=1;  R=0;
        cursum = 0;
        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < m; i++) {
            node tmp = query[i];
            while (tmp.r > R) ins(++R);
            while (tmp.l < L) ins(--L);
            while (tmp.r < R) rmv(R),R--;
            while (tmp.l > L) rmv(L),L++;
            ans[tmp.id] = cursum;
        }
        
        
        for (int i = 1; i <= m; i++) 
            printf("%lld\n",ans[i]);
    }
   
    return 0;
}