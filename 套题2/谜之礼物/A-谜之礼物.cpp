#include <bits/stdc++.h>
#define llt long long 
using namespace std;

const int N=4;
const int n=4,m=4;

char s[N][N];

int finish=0;
int offset[][2]={
    0,1,
    0,-1,
    1,0,
    -1,0
};
bool vis[N][N][N][N][(1<<16)+1]={false};
    //vis[i][j][u][v][status] 记录巨巨走到(i,j)、
    //小洁昊走到(u,v),status这种情况是否搜过 

struct Node{
    int x[2],y[2];//记录两人的坐标
    int status;// 走过点的状态数
    int mixn;//走到此状态花费最少时间
    Node(int a,int b,int c,int d,int e,int f): x({a,c}),y({b,d}),status(e),mixn(f){}
};

queue <Node> q;

int nx[2],ny[2],nstatus;
bool is_ok(Node node,int a,int b){// 监测  越界 or  为障碍物  or 访问过
    int arr[2];
    arr[0]=a;
    arr[1]=b;
    nstatus = node.status;
    for(int i=0;i<2;++i){
        nx[i]=node.x[i]+offset[arr[i]][0];
        ny[i]=node.y[i]+offset[arr[i]][1];
        nstatus |= 1<<(nx[i]*m+ny[i]);
        if(nx[i]<0||nx[i]>=n||ny[i]<0||ny[i]>=m||s[nx[i]][ny[i]]=='#') return true;
    }
    return vis[nx[0]][ny[0]][nx[1]][ny[1]][nstatus];
}


int bfs(int sx,int sy){//'S'的坐标
    memset(vis,false,sizeof vis);
    vis[sx][sy][sx][sy][1<<(sx*m+sy)]=1;

    q.push(Node(sx,sy,sx,sy,1<<(sx*m+sy),0));
    while(!q.empty()){
        Node node=q.front();
        q.pop();
        if(node.status==finish)
            return node.mixn;
        for(int i=0;i<4;++i)
            for(int j=0;j<4;++j){
                if(is_ok(node,i,j))continue;
                q.push(Node(nx[0],ny[0],nx[1],ny[1],nstatus,node.mixn+1));
                vis[nx[0]][ny[0]][nx[1]][ny[1]][nstatus]=1;
            }
    }
    return -1;//题目保证有解，所以这个其实多余
}
int main(){
    for(int i=0;i<n;++i)
        scanf("%s",s[i]);
    int sx,sy;
    for(int i=0;i<n;++i)
        for(int j=0;j<m;++j)
            if(s[i][j]=='S'){
                sx=i;
                sy=j;
                finish|=1<<(i*m+j);
            }else if(s[i][j]=='.')
                finish|=1<<(i*m+j);
    cout<<bfs(sx,sy)<<endl;
    return 0;
}