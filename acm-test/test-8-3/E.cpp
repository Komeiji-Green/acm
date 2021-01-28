#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdlib>
using namespace std;
int N, M;

int a[40];
int sum[1 << 21];
int ans = 0;

int main()
{
    while(scanf("%d", &N) != EOF) {
        cin >> M;
        for(int i = 0; i < N; i++)
            cin >> a[i];
        int n = min(N, 15);
        int m = 1 << n;
        for(int i = 0; i < m; i++) {
            int s = 0;
            for(int j = 0; j < n; j++) {
                if(i & (1 << j)) s += a[j];
            }
            sum[i] = s;
        }
        sort(sum, sum + (m));

        int ans = 0;
        for(int i = 0; i < (1 << (N - n)); i++) {
            int sum2 = 0;
            for(int j = 0; j < (N - n); j++) {
                if(i & (1 << j)) sum2 += a[j + n];
            }
            if(sum2 > M) continue;
            int idx = upper_bound(sum, sum + m, M - sum2) - sum;
            if(idx == 0) ans = max(ans, sum2);
            else ans = max(ans, sum2 + sum[idx - 1]);
        }

        cout << ans << endl;
    }
}