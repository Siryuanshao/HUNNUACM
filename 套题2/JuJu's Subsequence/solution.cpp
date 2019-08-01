#include <bits/stdc++.h>

using namespace std;

int sumSubseqWidths(int A[],int n) {
    long long sum = 0;
    int p = 1000000007;
    sort(A, A+n);
    long long *subSetNums = new long long[n];
    subSetNums[0] = 1;
    for (int i = 1; i < n; ++i) {
        subSetNums[i] = subSetNums[i - 1] * 2 % p;
    }
    int length = n;
    for (int i = 0; i < length; ++i) {
        // for (int j = i + 1; j < A.size(); ++j) {
        //     // int subSetNum = 1 << (j - i - 1);
        //     long long subSetNum = 1;
        //     int shift = j - i - 1;
        //     sum = sum % p + ((long long)(A[j] - A[i]) * subSetNums[shift]) % p;
        // }
        sum = (sum % p + (A[i] * (subSetNums[i] - subSetNums[length - i - 1])) % p) % p;
    }
    return (int)sum;
}

int main()
{
    int a[21000],n;
    while(cin>>n)
    {

        for(int i=0;i<n;++i) scanf("%d",&a[i]);
        int res=sumSubseqWidths(a,n);
        printf("%d\n",res);
    }

	return 0;
}

