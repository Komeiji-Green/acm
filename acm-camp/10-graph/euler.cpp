#include<bits/stdc++.h>
#include<ctime>
using namespace std;

const int N = 2333;
int G[N][N], nxt[N], n;


void dfs(int x) {
    int y = nxt[x];
    while(y <= n) {
        if(G[x][y]) {   // 还存在未遍历的边，要向下递归
            nxt[x] = y + 1; // 调整当前弧, 对于以后结点不用从头遍历邻接矩阵
            G[x][y] = G[y][x] = 0;  // 删边，每个边只遍历一次
            dfs(y);
            y = nxt[x];
        } else {
            y = y + 1;
        }
    }
    //printf("%d %d\n", x, prev); // 走到死路，回溯并输出结果  
}

void euler(int x) { // 从x开始的欧拉回路
    for(int i = 1; i <= n; ++i) nxt[i] = 1;
    for(int i = 1; i <= n; ++i) for(int j = 1; j <= n; ++j) {
        if(i != j) G[i][j] = 1;
    }
    dfs(1);
}

int main() {
    clock_t st = clock(), ed;
    n = 305;
    euler(1);
    ed = clock();
    cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;
}