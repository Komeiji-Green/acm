#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 233333;

int a[maxn], nxt[maxn], pos[maxn];
int s, t, ns, nt;
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int tot = 0;
    for(int i = 1; i <= n; ++i) {
        if(a[i] != a[tot]) {
            a[++tot] = a[i];
        }
    }
    for(int i = 1; i <= n; ++i) pos[i] = n + 1;
    for(int i = tot; i >= 1; --i) {
        nxt[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    ns = nt = n + 1;
    int cnt = 0;
    for(int i = 1; i <= tot; ++i) {
        int x = a[i];
        if(s != x && t != x) {
            //printf("??: %d %d %d %d\n", i, x, s, t);
            if(ns < nt) t = x;
            else s = x;
            ++cnt;
        }
        if(s == x) ns = nxt[i];
        if(t == x) nt = nxt[i];
       // printf("%d %d %d %d\n", s, t, ns, nt);
    }
    printf("%d\n", cnt);
}