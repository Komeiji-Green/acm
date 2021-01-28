#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 300500; 
int f[maxn], w[maxn];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]); }
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
    w[fy] += w[fx];
}
char s[maxn];
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%d", &n);
        scanf("%s", s);
        for(int i = 0; i < n; ++i) {
            f[i] = i; w[i] = 1;
        }
        bool cnc1 = true, cnc2 = true;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '<') cnc1 = false;
            if(s[i] == '>') cnc2 = false;
        }
        if(cnc1 || cnc2) printf("%d\n", n);
        else {
            for(int i = 0; i < n; ++i) {
                if(s[i] == '-') merge(i, (i + 1) % n);
            }
            int ans = 0;
            for(int i = 0; i < n; ++i) {
                if(f[i] == i && w[i] > 1) ans += w[i]; 
            }
            printf("%d\n", ans);
        }
    }
}