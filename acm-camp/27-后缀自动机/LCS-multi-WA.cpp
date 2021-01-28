#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;

const int maxn = 2000500;   // 字符串长度的两倍
struct Suffix_Automata {
    int trans[maxn][36], len[maxn], link[maxn], sz, last, lg;
    Suffix_Automata() { sz = 1, last = 1; }
    void setlg(int _lg) { lg = _lg; }
    void extend(int id) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        for(p = last; p && !trans[p][id]; p = link[p]) trans[p][id] = cur;
        if(!p) link[cur] = 1;
        else {
            int q = trans[p][id];
            if(len[p] + 1 == len[q]) link[cur] = q;
            else {
                int clone = (++sz);
                len[clone] = len[p] + 1;
                memcpy(trans[clone], trans[q], sizeof(trans[q]));
                link[clone] = link[q];
                for(; p && trans[p][id] == q; p = link[p]) trans[p][id] = clone;
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }
    int tag[maxn];
    void search(char *s, int bit) {
        int p = 1, id;
        for(int i = 0; s[i]; ++i) {
            id = s[i] - 'a';
            p = trans[p][id];
        }
        for(; p; p = link[p]) {
            tag[p] = (1 << bit);
        }
    }
    int v[maxn], deg[maxn], cnt;
    void topo() {
        cnt = 0;
        for(int x = 1; x <= sz; ++x)
            for(int i = 0; i < 36; ++i)
                if(trans[x][i]) ++deg[trans[x][i]];
        queue<int> Q;
        Q.push(1);
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            v[++cnt] = x;
            for(int i = 0, y; i < 36; ++i) {
                y = trans[x][i];
                if(!y) continue;
                --deg[y];
                if(deg[y] == 0) Q.push(y);
            }
        }
    }
    int dp() {
        topo();
        for(int i = cnt, x; i >= 1; --i) {
            x = v[i];
            for(int j = 0, y; j < 36; ++j) {
                y = trans[x][j];
                if(y) tag[x] |= tag[y];
            }
        }
        int ans = 0;
        int uu = (1 << lg);
        for(int i = cnt, x; i >= 2; --i) {
            x = v[i];
            if((tag[x] + 1) == uu) ans = max(ans, len[x]);
        }
        return ans;
    }
} T;

// 错了！
char s[10][maxn];
int main() {
    int n = 0;
    for(int i = 0; scanf("%s", s[i]) != EOF; ++i) {
        ++n;
        for(int j = 0; ; ++j) {
            if(!s[i][j]) {
                s[i][j] = 'a' + 26 + i;
                s[i][j + 1] = '\0';
                break;
            }
        }
        for(int j = 0; s[i][j]; ++j) {
            T.extend(s[i][j] - 'a');
        }
    }
    T.setlg(n);
    for(int i = 0; i < n; ++i) {
        T.search(s[i], i);
    }
    printf("%d\n", T.dp());
}