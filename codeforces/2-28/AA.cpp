#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
const int inf = 0x3f3f3f3f;

int a[maxn];
int main() {
    int n, q, op;
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    int x, k;
    int cnt[2] = {};
    for(int i = 1; i <= n; ++i) {
        cnt[a[i]]++;
    }
    while(q--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &x);
            cnt[a[x]]--;
            a[x] = 1 - a[x];
            cnt[a[x]]++;
        } else {
            scanf("%d", &k);
            if(k <= cnt[1]) {
                printf("1\n");
            } else {
                printf("0\n");
            }
        }
    }
}