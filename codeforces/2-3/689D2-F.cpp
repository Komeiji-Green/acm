#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxn = 233333;
ll a[maxn], tmp[maxn];
char s[maxn], ans[maxn];

void gao(int l, int r) {
    for(; l <= r && a[l] == 1; ++l) ans[l + 1] = '+';
    for(; l <= r && a[r] == 1; --r) ans[r] = '+';
    if(l > r) return;
    int len = r - l + 1;
    ll maxv = 5 * len;
    ll cur = 1;
    for(int i = l; i <= r; ++i) {
        cur *= a[i];
        if(cur >= maxv) break;
    }
    if(cur >= maxv) {
        for(int i = l + 1; i <= r; ++i) ans[i] = '*'; 
        return;  
    }
    vector<int> vec;
    for(int i = l; i <= r; ++i) {
        if(a[i] > 1) vec.push_back(i);
    }
    int sz = vec.size();
    int m = (1 << (sz - 1));
    ll sum; maxv = 0; int id = 0;
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < sz; ++j) tmp[j] = a[vec[j]];
        sum = 0;
        for(int j = 0; j < (sz - 1); ++j) {
            if((1<<j)&i) {
                tmp[j + 1] *= tmp[j];
            } else {
                sum += tmp[j] + vec[j + 1] - vec[j] - 1;
            }
        }
        sum += tmp[sz - 1];
        if(sum >= maxv) {
            maxv = sum;
            id = i;
        }
    }
    for(int j = 0; j < (sz - 1); ++j) {
        if((1<<j) & id) {
            for(int k = vec[j] + 1; k <= vec[j + 1]; ++k) {
                ans[k] = '*';
            } 
        } else {
            for(int k = vec[j] + 1; k <= vec[j + 1]; ++k) {
                ans[k] = '+';
            } 
        }
    }
}
int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
    scanf("%s", s);
    bool f1 = 0, f2 = 0, f3 = 0;
    for(int i = 0; s[i]; ++i) {
        if(s[i] == '+') f1 = 1;
        if(s[i] == '*') f2 = 1;
        if(s[i] == '-') f3 = 1;
    }
    if(f1 && !f2) {
        for(int i = 1; i <= n; ++i) {
            printf("%lld", a[i]);
            if(i < n) printf("+");
        }
        printf("\n");
    } else if(!f1 && f2) {
        if(f3 == 0) {
            for(int i = 1; i <= n; ++i) {
                printf("%lld", a[i]);
                if(i < n) printf("*");
            }
        } else {
            int j = 0;
            a[n+1] = 0;
            for(j = 1; j <= n; ++j) if(!a[j]) break;
            for(int i = 2; i < j; ++i) ans[i] = '*';
            ans[j] = '-';
            for(int i = j + 1; i <= n; ++i) ans[i] = '*';
            for(int i = 1; i <= n; ++i) {
                if(i > 1) printf("%c", ans[i]);
                printf("%lld", a[i]);
            }
        }

        printf("\n");
    } else if(!f1 && !f2) {
        for(int i = 1; i <= n; ++i) {
            printf("%lld", a[i]);
            if(i < n) printf("-");
        }
        printf("\n");
    } else {
        a[n + 1] = 0;
        for(int i = 1, j = 1; i <= n + 1; ++i) {
            if(a[i] == 0) {
                gao(j, i - 1);
                ans[i] = '+';
                ans[i + 1] = '+';
                j = i + 1;
            }
        }
        ans[n+1] = '\0';
        //printf("%s\n", ans + 2);
        for(int i = 1; i <= n; ++i) {
            if(i > 1) printf("%c", ans[i]);
            printf("%lld", a[i]);
        }
        printf("\n");
    }
}

/*
20
2 1 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1
+*
*/