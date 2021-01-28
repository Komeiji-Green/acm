#include<bits/stdc++.h>
#include<cstring>
#include<queue> 
#include<vector>
using namespace std;
typedef long long ll;

const int maxn = 1000500;   // 字符串长度的两倍
char ans[maxn];
struct Suffix_Automata {
    int trans[maxn][26], len[maxn], link[maxn], val[maxn], sz, last;
    Suffix_Automata() { sz = 1, last = 1; }
    void extend(int id) {
        int cur = (++sz), p;
        len[cur] = len[last] + 1;   // len[1] == 0
        val[cur] = 1;
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
            val[x] += val[y];
        }
    }

    queue<int> Q;
    int v[maxn], deg[maxn], cnt;
    ll dp[maxn], dpp[maxn];
    void pre() {
        memset(deg, 0, sizeof(deg));
        for(int x = 1; x <= sz; ++x)
            for(int i = 0; i < 26; ++i)
                if(trans[x][i]) ++deg[trans[x][i]];
        cnt = 0;
        Q.push(1);
        while(!Q.empty()) {
            int x = Q.front(), y; Q.pop();
            v[++cnt] = x;
            for(int i = 0; i < 26; ++i) {
                y = trans[x][i];
                if(!y) continue;
                --deg[y];
                if(deg[y] == 0) Q.push(y);
            }
        }

        for(int x = 1; x <= sz; ++x) {
            G[link[x]].push_back(x);
        }
        dfs(1);

        for(int i = cnt, x; i > 0; --i) {
            x = v[i];
            dp[x] = 1; dpp[x] = val[x];
            for(int j = 0, y; j < 26; ++j) {
                y = trans[x][j];
                if(y) dp[x] += dp[y], dpp[x] += dpp[y];
            }
        }
    }
    // 寻找第k大
    bool search_lex(ll k, int op) {
        k += op == 0 ? 1 : val[1];
        ll idx = 1;
        int p = 1, tot = 0, q;
        if(k >= idx + (op == 0 ? dp[1] : dpp[1])) return false;
        while(k >= idx + (op ? val[p] : 1)) {
            idx += (op ? val[p] : 1);
            for(int i = 0; i < 26; ++i) {
                q = trans[p][i];
                if(!q) continue;
                if(idx + (op ? dpp[q] : dp[q]) > k) {
                    ans[tot++] = 'a' + i;
                    p = q;
                    break;
                }
                idx += (op ? dpp[q] : dp[q]);
            }
        }
        ans[tot] = '\0';
        return true;
    }
} T;

char s[maxn];
int main() {
    scanf("%s", s);
    for(int i = 0; s[i]; ++i) {
        T.extend(s[i] - 'a');
    }
    T.pre();
    int op; ll k;
    scanf("%d%lld", &op, &k);
    bool flag = T.search_lex(k, op);
    if(flag) {
        printf("%s", ans);
    } else {
        printf("-1\n");
    }
}