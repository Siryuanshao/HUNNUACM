#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+777;
int num[11][11];// i 为 花费 ， j 为 收益 ， num 记录个数
int dp[N];

int bag;
/************************************背包板子*/
inline void ZeroOnePack(int weight,int value){
    for(int i = bag; i>=weight ; --i)
        dp[i] = max(dp[i],dp[i-weight]+value);
}

inline void CompletePack(int weight,int value){
    for(int i = weight ; i <= bag ; ++i)
        dp[i] = max(dp[i],dp[i-weight]+value);
}

inline void MultiplePack(int weight,int value , int number){
    if(number*weight >= bag){
        CompletePack(weight,value);
        return;
    } 

    int k = 1;
    while(number > k){
        ZeroOnePack(weight*k,value*k);
        number -= k;
        k <<= 1;
    }
    if(number > 0)
        ZeroOnePack(weight*number,value*number);

}
/********************************************/
int main(){
    int n;
    scanf("%d%d",&n,&bag);
    while(n--){
        int x,y;
        scanf("%d%d",&x,&y);
        ++num[x][y];//统计物品
    }

    for(int i=1;i<=10;++i)
        for(int j=1;j<=10;++j)
            MultiplePack(i,j,num[i][j]);

    printf("%d\n",dp[bag]);
}