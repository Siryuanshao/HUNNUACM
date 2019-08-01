#include <iostream>

using namespace std;
typedef long long ll;
const ll MOD = 998244353, inv = (MOD + 1) / 2;

int dp[1 << 20][20];
bool Graph[20][20];
int ans[25];



#ifdef _MSC_VER
#include <intrin.h>
#define __builtin_popcount __popcnt
static inline int __builtin_ctz(uint32_t x) {
    unsigned long ret;
    _BitScanForward(&ret, x);
    return (int)ret;
}


static inline int __builtin_clz(uint32_t x) {
    //unsigned long ret;
    //_BitScanReverse(&ret, x);
    //return (int)(31 ^ ret);
    return (int)__lzcnt(x);
}
#endif

int main()
{
    int n, m, z;
    while (scanf("%d%d%d", &n, &m, &z) == 3) {
        memset(dp, 0, sizeof(dp));
        memset(Graph, false, sizeof(Graph));
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < m; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            Graph[u][v] = Graph[v][u] = true;
        }
        for (int i = 0; i < n; i++) dp[1 << i][i] = 1;
        for (int i = 1; i < (1 << n); i++)
        {
            int from = __builtin_ctz(i);
            for (int j = from; j < n; j++)
            {
                if (dp[i][j] == 0) continue;
                int cnt = __builtin_popcount(i);
                if (Graph[from][j] && cnt > 2) (ans[cnt % z] += dp[i][j]) %= MOD;
                for (int k = from + 1; k < n; k++)
                {
                    if (((1 << k) & i) || !Graph[j][k]) continue;
                    int newst = (1 << k) | i;
                    (dp[newst][k] += dp[i][j]) %= MOD;
                }
            }
        }
        for (int i = 0; i < z; i++)
            printf("%lld\n", 1LL * inv * ans[i] % MOD);
    }
    return 0;
}