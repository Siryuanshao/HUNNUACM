#include <bits/stdc++.h>
using namespace std;

int uniqueLetterString(char S[]) {
        int len = strlen(S);
        if(len < 2) return len;
        int res = 0;
        long long mod = 1e9+7;

        vector<int> pre(26, -1), prev_prev(pre);
        for(int i=0; i<len; i++){
            int cur = S[i] - 'A';
            res = ( res + (i - pre[cur]) * (pre[cur] - prev_prev[cur])) % mod;
            prev_prev[cur] = pre[cur];
            pre[cur] = i;
        }

        for(int i=0; i<26; i++)
            res = (res + (len - pre[i]) * (pre[i] - prev_prev[i])) % mod;

        return res;
}

int main()
{
    char str[10010];
    while(~scanf("%s",str))
    {
        int res=uniqueLetterString(str);
        printf("%d\n",res);
    }
	return 0;
}
