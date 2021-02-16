#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2007;
char s[N][N];

int f[N];
int find(int x) {
    return f[x] == x ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    f[fx] = fy;
}
int main() {
    int R, C;
    cin >> R >> C;
    int n = R + C;
    for(int i = 1; i <= n; ++i) f[i] = i;
    merge(1, R + 1); merge(1, R + C); merge(R, R + 1); merge(R, R + C);
    for(int i = 1; i <= R; ++i) {
        scanf("%s", s[i] + 1);
    }
    for(int i = 1; i <= R; ++i) {
        for(int j = 1; j <= C; ++j) {
            if(s[i][j] == '#') {
                merge(i, R + j);
            }
        }
    }

    set<int> rmp, cmp;
    for(int i = 1; i <= R; ++i) rmp.insert(find(i));
    for(int j = 1; j <= C; ++j) cmp.insert(find(R + j));
    int cnt = min(rmp.size(), cmp.size());
    printf("%d\n", cnt - 1);
}