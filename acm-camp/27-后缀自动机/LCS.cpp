#include<bits/stdc++.h>
#include<cstring>
using namespace std;

const int maxn = 550000;   // 字符串长度的两倍
struct Suffix_Automata {
    int trans[maxn][26], len[maxn], link[maxn], sz, last;
    Suffix_Automata() { sz = 1, last = 1; }
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
    // 查询s每一个前缀的能匹配到一个子串的最长后缀
    int query(char *s) {
        int ans = 0, l = 0, p = 1, id;
        for(int i = 0; s[i]; ++i) {
            id = s[i] - 'a';
            for(; p && !trans[p][id]; p = link[p]) l = len[link[p]];
            if(!p) p = 1;
            else p = trans[p][id], (++l);
            ans = max(ans, l);
        }
        return ans;
    }
} T;

char s[maxn], t[maxn];
int main() {
    scanf("%s%s", s, t);
    for(int i = 0; s[i]; ++i) {
        T.extend(s[i] - 'a');
    }
    printf("%d\n", T.query(t));
}