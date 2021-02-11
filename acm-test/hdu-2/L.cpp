#include<bits/stdc++.h>
using namespace std;
typedef int ll;

const int maxn = 100007;

struct Mat {
    Mat() {}
    Mat(ll *list, int _m, int _n):
        m(_m), n(_n) 
    {
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                a[i][j] = list[i * n + j];
            }
        }
    }
    Mat operator* (const Mat& rhs) {
        Mat ans;
        int p = rhs.n;
        ans.m = m; ans.n = p;
        ll sum;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < p; j++) {
                sum = -1;
                for(int k = 0; k < n; k++) {
                    if(a[i][k] >= 0 && rhs.a[k][j] >= 0)
                        sum = max(sum, a[i][k] + rhs.a[k][j]);
                }
                ans.a[i][j] = sum;
            }
        }
        return ans;
    }
    int m, n;
    ll a[21][21];
} Z;

int n, m;

Mat mat[maxn<<2], M[maxn];
void pushup(int k) {
    mat[k] = mat[k<<1|1] * mat[k<<1];
}
void build(int k, int l, int r) {
    if(l == r) mat[k] = M[l];
    else {
        int m = ((l + r) >> 1);
        build(k<<1, l, m);
        build(k<<1|1, m + 1, r);
        pushup(k);
    }
}

int li[505], tot = 0;
void query(int k, int L, int R, int l, int r) {
    if(L <= l && r <= R) {
        li[++tot] = k;
    } else {
        int m = ((l + r) >> 1);
        if(L <= m) query(k<<1, L, R, l, m);
        if(R > m) query(k<<1|1, L, R, m + 1, r);
    }
}

char s[maxn], t[maxn];
int pre[21][26];

int main() {
    int T;
    cin >> T;
    Mat Y;
    while(T--) {
        scanf("%s %s", s + 1, t + 1);
        n = strlen(s + 1);
        m = strlen(t + 1);
        Z.m = m+1; Z.n = 1;
        for(int j = 0; j < 26; ++j) {
            for(int i = 1; i <= m; ++i) {
                pre[i][j] = pre[i-1][j];
                if(t[i]-'a'==j) pre[i][j] = i;
            }
        }
        for(int i = 1; i <= n; ++i) {
            int c = s[i] - 'a';
            M[i].m = M[i].n = m + 1;
            for(int j = 0; j <= m; ++j) for(int k = 0; k <= m; ++k) M[i].a[j][k] = -1;
            M[i].a[0][0] = 0;
            for(int j = 1; j <= m; ++j) {
                M[i].a[j][j] = 0;
                int k = pre[j][c];
                if(k) M[i].a[j][k-1] = 1;
            }
        }
        build(1, 1, n);
        int q, l, r;
        scanf("%d", &q);
        while(q--) {
            scanf("%d %d", &l, &r);
            tot = 0;
            query(1, l, r, 1, n);
            Y = Z;
            for(int i = 1; i <= tot; ++i) {
                Y = mat[li[i]] * Y;
            }
            int ans = (r-l+1)-Y.a[m][0]+m-Y.a[m][0];
            printf("%d\n", ans);
        }
    }
}