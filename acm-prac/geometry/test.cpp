#include<bits/stdc++.h>
using namespace std;

const int maxn = 10005;
const int mod = 0xff;
const int ans = 0x7e ^ mod;
int f(int a, int b) {
    return (a & b) ^ mod;
}
void output(int a) {            
    for(int i = 7; i >= 0; --i) {
        printf(((1<<i)&a) ? "1 " : "0 ");
    }
    printf("\n");
}

int vec[maxn], step[maxn], tot;
inline void add(int x) {
    vec[tot++] = x;
}
bool dfs(int t) {
    if(vec[tot - 1] == ans) return true;
    if(!t) return false;
    int res, n = tot;
    for(int i = 0; i < n; ++i) {
        for(int j = i; j < n; ++j) {
            res = f(vec[i], vec[j]);
            add(res);
            if(dfs(t - 1)) {
                printf("%d: %d ++ %d: %d\n", i, vec[i], j, vec[j]);
                return true;
            }
            --tot;
        }
    }
    return false;
}
int main() {
    int a = 0xf0, aa = 0xff;
    int b = 0xcc, bb = b ^ mod;
    int c = 0xaa, cc = c ^ mod;
    add(a); add(aa); add(b); add(bb); add(c); add(cc);
    if(!dfs(4)) printf("-1\n");
}
