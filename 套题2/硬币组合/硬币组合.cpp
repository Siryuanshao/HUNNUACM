#include<bits/stdc++.h>
 
using namespace std;  
 
const int maxn = 1111;  
int arr[maxn];  
int main(){
    int m, n;  
    scanf("%d%d", &m, &n);  
    for(int i=1; i<=n; i++){
        scanf("%d", &arr[i]);  
    }
    arr[n+1]=m+1;  
    sort(arr+1, arr+n+2);  
    if(arr[1] != 1) {
        printf("-1\n");  
        return 0;  
    }
    int tot=0;  //前0个可以 
    int ans =0;  //0个硬币 
    for(int i=2; i<=n+1 && arr[i] <= m+1; i++){  //i时算i-1要多少个，算到arr[i]-1要多少个 
        if(arr[i] <= tot+1) continue;  //tot+1也不要，在这里没用，下面的t会是0 
        int t= ceil((arr[i]-1.0-tot)/arr[i-1]);  
        ans += t;  //t个arr[i-1]
        tot += t*arr[i-1];   
    }
    printf("%d\n", ans);  
} 