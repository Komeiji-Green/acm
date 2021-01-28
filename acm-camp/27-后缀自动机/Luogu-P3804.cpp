#include<bits/stdc++.h>
#include<vector>
#include<cstring>
using namespace std;
typedef long long ll;

const int maxn = 2000050;   // 字符串长度的两倍
struct Suffix_Automata {
    int trans[maxn][26], len[maxn], link[maxn], w[maxn], sz, last;
    vector<int> G[maxn];
    bool tag[maxn];
    Suffix_Automata() { sz = 1, last = 1; }
    void extend(int id) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        tag[cur] = true;
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
    // 求endpos
    ll gao() {
        for(int i = 2; i <= sz; ++i) {
            G[link[i]].push_back(i);
        }
        dfs(1);
        ll ans = 0;
        for(int i = 2; i <= sz; ++i) {
            if(w[i] == 1) continue;
            ans = max(ans, 1ll * w[i] * len[i]);
        }
        return ans;
    }
    void dfs(int x) {
        w[x] = tag[x] ? 1 : 0;
        for(auto y : G[x]) {
            dfs(y);
            w[x] += w[y]; 
        }
    }
} T;

char s[maxn];
int main() {
    scanf("%s", s);
    for(int i = 0; s[i]; ++i) {
        T.extend(s[i] - 'a');
    }
    printf("%lld\n", T.gao());
}