                   原题之ACMer蒟蒻的机智

2019年7月31号，蒟蒻正在实习摸鱼，突然发现自己出题目的任务还没用完成，蒟蒻灵机一动，找到了一个Original question。蒟蒻拿给龙神看，龙神说这是Stupid Problem，蒟蒻自闭了，但还是给了出来。
题目如下：
    给出正整数n和k，计算j(n, k)=k mod 1 + k mod 2 + k mod 3 + … + k mod n的值，其中k mod i表示k除以i的余数。
    例如j(5, 3)=3 mod 1 + 3 mod 2 + 3 mod 3 + 3 mod 4 + 3 mod 5=0+1+0+3+3=7
Input
输入仅一行，包含两个整数n, k。
1<=n ,k<=10^9
Output
输出仅一行，即j(n, k)。

Sample Input
5 3
Sample Output
7