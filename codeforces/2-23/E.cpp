#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 250007;
bool in[N]; int t[N];
vector<int> a[N], d[N];
int cnt[N];
int o[N];
int n, m;

int chk1() {
    for(int i = 1; i <= n; ++i) {
        int cur = 0;
        for(int j = 0; j < 4; ++j) {
            if(a[i][t[j]] != o[t[j]]) ++cur;
        }
        if(cur + cnt[i] > 2) return 0;
    }
    return 1;
}

int C[N];

int chk2(int k) {
    int p = t[k];
    map<int, int> mp;
    for(int i = 1; i <= n; ++i) {
        C[i] = cnt[i];
        int cur = 0;
        for(int j = 0; j < 3; ++j) {
            if(j == k) continue;
            if(a[i][t[j]] != o[t[j]]) ++cur;
        }
        C[i] += cur;
    }
    for(int i = 1; i <= n; ++i) {
        int val = a[i][p];
        if(!mp.count(val)) mp[val] = C[i];
        else {
            mp[val] = max(mp[val], C[i]);
        }
    }
    int bad = 0;
    int res = 0;
    for(auto pr : mp) {
        if(pr.second > 2) return 0;
        if(pr.second == 2) ++bad, res = pr.first;
    }
    if(bad > 1) return 0;
    else if(bad == 0) return 1;
    else return res;
}
int main() {
    cin >> n >> m;
    int tmp;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j < m; ++j) {
            scanf("%d", &tmp);
            a[i].push_back(tmp);
        }
    }
    int p = 0, sz = 0;
    for(int i = 2; i <= n; ++i) {
        for(int j = 0; j < m; ++j) {
            if(a[i][j] != a[1][j]) d[i].push_back(j);
        }
        if(d[i].size() > sz) sz = d[i].size(), p = i;
    }
    if(sz <= 2) {
        printf("Yes\n");
        for(int i = 0; i < m; ++i) printf("%d ", a[1][i]);
        printf("\n");
    } else if(sz >= 5) {
        printf("No\n");
    } else if(sz == 4) {
        if(p != 2) {
            swap(a[p], a[2]); swap(d[p], d[2]);
        }
        int tot = 0;
        for(auto pos : d[2]) {
            in[pos] = 1; t[tot++] = pos;
        }
        for(int i = 3; i <= n; ++i) {
            for(auto pos : d[i]) {
                if(!in[pos]) ++cnt[i];
            }
        }
        bool f = 0;
        for(int i = 0; i < m; ++i) o[i] = a[1][i];
        for(int i = 0; i < 16 && !f; ++i) {
            for(int j = 0; j < 4; ++j) {
                if((1<<j)&i) o[t[j]] = a[2][t[j]];
                else o[t[j]] = a[1][t[j]];
            }
            if(chk1()) {
                printf("Yes\n");
                for(int ii = 0; ii < m; ++ii) printf("%d ",o[ii]);
                printf("\n");
                f = 1;
                break;
            }
        }
        if(!f) printf("No\n");
    } else if(sz == 3) {
        if(p != 2) {
            swap(a[p], a[2]); swap(d[p], d[2]);
        }
        int tot = 0;
        for(auto pos : d[2]) {
            in[pos] = 1; t[tot++] = pos;
        }
        for(int i = 3; i <= n; ++i) {
            for(auto pos : d[i]) {
                if(!in[pos]) ++cnt[i];
            }
        }
        for(int i = 0; i < m; ++i) o[i] = a[1][i];
        bool f = 0;
        for(int i = 0; i < 3 && !f; ++i) for(int j = 0; j < 3; ++j) {
            if(i == j) continue;
            o[t[i]] = a[1][t[i]];
            o[t[j]] = a[2][t[j]];
            int k;
            for(k = 0; k < 3; ++k) {
                if(k != i && k != j) break;
            }
            int res;
            if(res = chk2(k)) {
                o[t[k]] = res;
                printf("Yes\n");
                for(int ii = 0; ii < m; ++ii) printf("%d ",o[ii]);
                printf("\n");
                f = 1;
                break;
            }
        }
        if(!f) printf("No\n");
    }
}