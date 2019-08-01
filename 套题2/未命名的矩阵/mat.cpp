#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
//大概解法:枚举左上角和右下角,然后是经典的最大字段和加上长度限制的做法
typedef long long llt;
const int maxn = 555;
//sum记录的是矩阵和和零个数的前缀和
int mat[maxn][maxn];
llt sum[maxn][maxn];
int num[maxn][maxn];
//加了额外长度限制的最大字段和问题
//并且有趣的地方就是，也就是说满足Dp条件的就是
//必须前面合法,后面才可能合法,所以可以用DP解决此类问题
llt getsum(int lx, int ly, int rx, int ry)
{
    return sum[rx][ry] - sum[lx - 1][ry] - sum[rx][ly - 1] + sum[lx - 1][ly - 1];
}
int getzerocnt(int lx, int ly, int rx, int ry)
{
    return num[rx][ry] - num[lx - 1][ry] - num[rx][ly - 1] + num[lx - 1][ly - 1];
}
//l和r记录的是上边ly和ry的位置
//每个位置都一定想减去前缀和最小的位置对吧......
llt Stack[maxn];
int pos[maxn];
llt dp1[maxn];
int dp2[maxn];
llt solve(int l, int r, int n, int limit, int k)
{
    llt ans = 0;
    int tail = 0, top = 0;
    for (int i = 1; i <= n; i++)
    {
        dp1[i] = dp1[i - 1] + getsum(i, l, i, r);
        dp2[i] = dp2[i - 1] + getzerocnt(i, l, i, r);
    }
    Stack[top] = 0, pos[top] = 0, top++;
    for (int i = 1; i <= n; i++)
    {
        while (top > tail && (dp2[i] - dp2[pos[tail]] > k || i - pos[tail] > limit)) tail++;
        while (top > tail && dp1[i] <= Stack[top - 1]) top--;
        Stack[top] = dp1[i], pos[top] = i, top++;
        ans = max(ans, dp1[i] - Stack[tail]);
    }
    return ans;
}
int main()
{
    int r, c, x, y, z;
    while (scanf("%d%d%d%d%d", &r, &c, &x, &y, &z) != EOF) {
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                scanf("%d", &mat[i][j]);
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
            {
                sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + mat[i][j];
                num[i][j] = num[i - 1][j] + num[i][j - 1] - num[i - 1][j - 1] + (mat[i][j] == 0);
            }
        llt ans = 0;
        for (int i = 1; i <= c; i++)
            for (int j = 1; j <= y; j++)
            {
                int to = i + j - 1;
                if (to > c) break;
                ans = max(ans, solve(i, to, r, x, z));
            }
        printf("%lld\n", ans);
    }
    return 0;
}