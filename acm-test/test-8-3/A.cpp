#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
int N, M;

const int INF = 0x3f3f3f3f;
int ans = INF;

int sum_1[30];
int sum_2[30];
int sum_3[30];




void dfs(int m, int r, int h, int S, int V)
{
    if (m == 0) {
        if (V == 0) ans = min(S, ans);
        return;
    }
    if (h <= m) return;
    if (r <= m) return;
    if (sum_3[m] > V) return;
    if (S + 2 * sum_2[m] > ans) return;
    //if (V != 0 && 1.0 * S + 2.0 * sqrt((double)sum_1[m] / V) > ans) return;
    if (r > 1 && 2ll * V > 1ll * (ans - S) * (r - 1)) return;
    for (int i = r - 1; i >= m; i--) {
        for (int j = h - 1; j >= m; j--) {
            dfs(m - 1, i, j, (S == 0 ? i * i + 2 * i * j : S + 2 * i * j), V - i * i * j);
        }
    }
}

int main()
{
    cin >> N >> M;
    sum_2[0] = 0;
    for (int i = 1; i <= M; i++) {
        sum_1[i] = sum_1[i - 1] + i;
        sum_2[i] = sum_2[i - 1] + i * i;
        sum_3[i] = sum_3[i - 1] + i * i * i;
    }
    dfs(M, 101, 10001, 0, N);
    //cout << ans << endl;
    cout << (ans == INF ? 0 : ans) << endl;
}