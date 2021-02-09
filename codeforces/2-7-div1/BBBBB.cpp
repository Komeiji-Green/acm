#include<bits/stdc++.h>
using namespace std;

const int maxn = 233333;
int a[maxn], nxt[maxn], pos[maxn];
int s, t, ns, nt;
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) pos[i] = n + 1;
    for(int i = n; i >= 1; --i) {
        nxt[i] = pos[a[i]];
        pos[a[i]] = i;
    }
    int cnt = 0;
    ns = n + 1, nt = n + 1;
    for(int i = 1; i <= n; ++i) {
        int x = a[i];
        if(s == x || t == x) {
            if(s != x) {
                s = x; cnt++;
            } else if(t != x) {
                t = x; cnt++;
            }
        } else {
            if(ns < nt) {
                s = x; ns = nxt[i]; cnt++;
            } else {
                t = x; nt = nxt[i]; cnt++;
            }
        }
        if(s == x) ns = nxt[i];
        if(t == x) nt = nxt[i];
    }
    printf("%d\n", cnt);
}