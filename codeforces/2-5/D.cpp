#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;
char s[N][N];
int ind[N], oud[N];
int ans1[100005], ans2[100005];
int main() {
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 1; i<= n; ++i) {
            scanf("%s", s[i] + 1);
        }
        int l = 0, r = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                if(i == j) continue;
                if(s[i][j] == s[j][i]) {
                    l = i; r = j;
                }
            }
        }
        bool f = 0;
        if(l && r) {
            printf("YES\n");
            for(int i = 1; i <= m + 1; ++i) {
                if(i % 2) printf("%d ", l);
                else printf("%d ", r);
            }
            printf("\n");
            continue;
        }
        if(n == 2) {
            if(m % 2 == 0) printf("NO\n");
            else {
                printf("YES\n");
                for(int i = 1; i <= m+1; ++i) {
                    if(i % 2) printf("%d ", 1);
                    else printf("%d ", 2);
                }
                printf("\n");
            }
        } else {
            for(int i =1; i<= n; ++i) ind[i]=oud[i]=0;
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= n; ++j) {
                    if(s[i][j] == 'a') {
                        oud[i]++; ind[j]++;
                    }
                }
            }
            int mid = 0;
            for(int i = 1; i <= n; ++i) if(oud[i] && ind[i]) mid = i;
            for(int j = 1; j <= n; ++j) {
                if(s[mid][j] == 'a') r = j;
                if(s[j][mid] == 'a') l = j;
            }
            printf("YES\n");
            if(m % 2) {
                for(int i = 1; i <= m + 1; ++i) {
                    if(i % 2) printf("%d ", l);
                    else printf("%d ", mid);
                }
                printf("\n");
            } else {
                int hf = m / 2;
                for(int i = 1; i <= hf; ++i) {
                    if(i % 2) ans2[i] = r;
                    else ans2[i] = mid;
                }
                for(int i = 1; i <= hf; ++i) {
                    if(i % 2) ans1[i] = l;
                    else ans1[i] = mid;
                }
                for(int i = hf; i >= 1; --i) {
                    printf("%d ", ans1[i]);
                }
                printf("%d ", mid);
                for(int i = 1; i <= hf; ++i) {
                    printf("%d ", ans2[i]);
                }
                printf("\n");
            }
        }
    }
}