#typedef long long ll;

struct Edge
{
    int from, to, w;

} e[M];

int last[N];
void ine(int a, int b, ll w) {
    es++;
    e[es].from = a; e[es].to = b; e[es].w =w;
    e[es].pre = last[a];
    last[a] = es;
} 

inline void ine2(int a, int b, ll w) { ine(a, b, w); ine(b, a, w); }
void init() { es = 0; fill(pre, 0); fill(maxv, 0); }
#define reg(i, x) for (int i = pre[x]; i; i = e[i].pre)
#define rep(i, a, b) for (int i = a; i <= b; i++)

// 无根树转有根树
void change(int x, int dad, int dept) {
    dep[x] = dept;
    size[x] = 1;
    fa[x] = dad;
    for(int i = pre[x]; i; i = e[i].pre) {
        int y = G[x][i];
        if(y == dad) continue;
        change(y, x, dept + 1);
        size[x] += size[y];
    }
}

int n, m, q;
void floyd() {
    
}