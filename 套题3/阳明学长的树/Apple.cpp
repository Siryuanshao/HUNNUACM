#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
 
using namespace std;
const int MOD = 1e9 + 7;
const int maxn = 2e5 + 111;
long long dp[maxn][2];
 
int col[maxn];
vector<int> tree[maxn];
 
// 这里要求是每一块必须恰好一个黑块
// dp[u][0] 表示这颗子树全是白色节点的不安全状态,可以转化为安全状态
// dp[u][1] 表示这颗子树恰好有一个黑色节点的安全状态,剩余的节点必须都是白色节点

void dfs(int u)
{
    unsigned long sz = tree[u].size();
    dp[u][col[u]] = 1;
    for(int i = 0; i < sz; i++)
    {
        int v = tree[u][i];
        dfs(v);
        long long temp0 = dp[u][0], temp1 = dp[u][1];
        // 对于每一个子节点,都可以分为这条边鸽或者不鸽
        dp[u][0] = temp0 * ((dp[v][1] + dp[v][0]) % MOD) % MOD;
        dp[u][1] = (temp1 * ((dp[v][1] + dp[v][0]) % MOD) % MOD + temp0 * dp[v][1]) %MOD;
    }
}
 
 
int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; i++)
            tree[i].clear();
        for(int i = 1; i < n; i++)
        {
            int fa;
            scanf("%d", &fa);
            tree[fa].push_back(i);
        }
        for(int i = 0; i < n; i++)
            scanf("%d", &col[i]);
 
        memset(dp, 0, sizeof(dp));
        dfs(0);
        printf("%lld\n", dp[0][1]);
    }
    return 0;
}