#include<bits/stdc++.h>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;

const int maxn = 2000500;   // 字符串长度的两倍
struct Suffix_Automata {
    int trans[maxn][36], len[maxn], link[maxn], tag[maxn], sz, last, lg;
    Suffix_Automata() { sz = 1, last = 1; }
    void setlg(int _lg) { lg = _lg; }
    void extend(int id, int bit) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        tag[cur] = (1 << bit);
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
    vector<int> G[maxn];
    void dfs(int x) {
        for(auto y : G[x]) {
            dfs(y);
            tag[x] |= tag[y];
        }
    }
    void build() {
        for(int i = 2; i <= sz; ++i) {
            G[link[i]].push_back(i);
        }
        dfs(1);
    }
    int gao() {
        build();
        int ans = 0, uu = (1 << lg);
        for(int x = 1; x <= sz; ++x) {
            if((tag[x] + 1) == uu) ans = max(ans, len[x]);
        }
        return ans;
    }
} T;

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
            T.extend(s[i][j] - 'a', i);
        }
    }
    T.setlg(n);
    printf("%d\n", T.gao());
}