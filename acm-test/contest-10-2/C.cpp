#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 2000000 + 5;
const int inf = 0x7fffffff;
int x[maxn], c[maxn], a[maxn];
int que[maxn], head, tail;
int D[maxn], t1;
int d[maxn], t2;

int getd(int ii) {
    int idx = upper_bound(d, d + t2, ii) - d;
    return a[d[idx]];
}
int getD(int ii) {
    int idx = upper_bound(D, D + t1, ii) - D;
    return a[D[idx]];
}
int main() {
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &x[i]);
    }
    int maxv = 0, minv = inf;
    c[0] = 0;
    head = 0, tail = 0;
    for(int i = 1; i <= n; ++i) {
        a[i] = x[i] ^ c[i-1];
        if(i > k) {
            while(t1 && a[D[t1-1]] <= a[i]) --t1;
            D[t1++] = i;
            while(t2 && a[d[t2-1]] >= a[i]) --t2;
            d[t2++] = i;
        }
        int jj = i - k;
        if(jj >= k) {
            while(head < tail && c[que[tail - 1]] >= c[jj]) --tail;
            que[tail++] = jj;
        }
        if(i < 2 * k) {
            maxv = max(maxv, a[i]);
            minv = min(minv, a[i]);
            if(i < k) c[i] = 0;
            else c[i] = maxv - minv;
        } else {
            int le = head, ri = tail - 1;
            int mid = (le + ri + 1) >> 1;
            while(le < ri) {
                if(c[que[mid]] <= (getD(que[mid]) - getd(que[mid]))) {
                    le = mid;
                } else {
                    ri = mid - 1;
                }
                mid = (le + ri + 1) >> 1;
            }
            c[i] = max(c[que[mid]], getD(que[mid]) - getd(que[mid]));
            if(mid + 1 < tail) {
                c[i] = min(c[i], max(c[que[mid+1]], getD(que[mid+1]) - getd(que[mid+1])));
            } 
        }
    }
    for(int i = 1; i <= n; ++i) {
        printf("%d\n", c[i]);
    }
}