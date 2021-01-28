#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;


const int maxn = 50500;

// 带权并查集
int f[maxn];

int w[maxn];
// val:获得与根节点的关系
int find(int x, int&val)
{
    if(f[x] == x) {
        val = w[x];
        return x;
    } 
    int res = find(f[x], val);  // 此后val为f[x]与根节点的关系
    int v = val + w[x];
    if(v < 0) v += 3;
    val = w[x] = v;             // w[x] 总是存储与父节点的关系
    return f[x] = res;          // 路径压缩，使得上条性质不变
}

// v: x-->y 的关系值
void merge(int x, int y, int v)
{
    int wx, wy;
    int fx = find(x, wx);
    int fy = find(y, wy);
    f[fx] = fy;
    w[fx] = (v + wy - wx) % 3;
    if(w[fx] < 0) w[fx] += 3;
}


int main()
{
    int cnt = 0;
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        f[i] = i;
    int d, x, y, fx, fy, wx, wy;
    while(k--) {
        scanf("%d%d%d", &d,&x,&y);
        if(x > n || y > n) {
            cnt++;
            continue;
        }
        fx = find(x, wx);
        fy = find(y, wy);
        if(fx != fy) {
            merge(x, y, (d == 1 ? 0 : 1));
        } else {
            int v = (d - 1 + wy - wx) % 3;
            if(v < 0) v += 3;
            if(v) cnt++;
        }
    }
    cout << cnt << endl;
}