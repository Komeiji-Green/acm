#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
typedef int ll;

const int INF = 0x3f3f3f3f;
const int N = 100500;

int mm[N];
int dp[N][25];
int a[N]; // 数i出现的位置
int num[N]; // 序列中第i个数

void initrmq(int n) {
    mm[0] = -1;
    for(int i = 1; i <= n; i++) {
        if(i & (i - 1)) mm[i] = mm[i - 1];
        else mm[i] = mm[i - 1] + 1;
    }

    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++) {
        dp[i][0] = a[i];
    }

    for(int k = 1; k <= 20; k++) {
        for(int i = 1; i <= n; i++) {
            if((i + (1 << k)) > (n + 1)) break;
            dp[i][k] = max(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
        }
    }
}

int rmq(int l, int r) {
    int k = mm[r - l + 1];
    return max(dp[l][k], dp[r + 1 - (1 << k)][k]);
}

bool check(int r, int k, int mid) {
    int maxv = rmq(k, mid);
    if(maxv > r) return true;
    else return false;
}

int main() {
    //freopen("BOUT.txt", "w", stdout);
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        scanf("%d %d", &n, &m);

        for(int i = 1, v; i <= n; i++) {
            scanf("%d", &v);
            num[i] = v;
            a[v] = i; 
        }
        a[n + 1] = INF;
        initrmq(n + 1);

        set<int> remove;    // 记录被移除的数
        remove.insert(n + 1);

        int last = 0, op, t1, t2, t3;
        while(m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d", &t1);
                int idx = t1 ^ last;
                //printf("fact: %d %d\n", op, idx);
                remove.insert(num[idx]);
                //update(num[idx], num[idx], INF, 1, 1, n);
            } else {
                scanf("%d %d", &t2, &t3);
                int r = t2 ^ last;
                int k = t3 ^ last;
                //printf("fact: %d %d %d\n", op, r, k);

                int le = k, ri = *remove.lower_bound(k);
                int mid = (le + ri) >> 1;
                while(le < ri) {
                    if(check(r, k, mid)) {
                        ri = mid;
                    } else {
                        le = mid + 1;
                    }
                    mid = (le + ri) >> 1;
                }
                last = mid;
                printf("%d\n", mid);
            }
        }

    }
}