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
} T;

int main() {

}