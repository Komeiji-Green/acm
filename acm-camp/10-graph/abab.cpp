
int dfn[N], vis[N], sta[N], low[N], top, clk;
void tarjan(int x) {
    vis[x] = 0; sta[++top] = x; dfn[x] = ++clk; low[x] = clk;
    for(int i = last[x]; i; i = e[i].pre) {
        int y = e[i].to;
        if(!dfn[y]) {   // 树边
            tarjan(y);
        } else if(!vis[y]) { // 非横边
            if(dfn[y] < dfn[x])
            low[x] = min(low[x], dfn[y]);

        }
    }
}