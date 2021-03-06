#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 0x3f3f3f3f3f3f3f3f;

int Cnt = 0;

int a[13][13];
struct state {
    int w[13], n;
    int getline(int *stk) {
        int top = 0;
        for(int i = 1; i <= n; ++i) {
            ++Cnt;
            if(w[i] > n) continue;
            while(top && w[stk[top]] >= w[i]) --top;
            stk[++top] = i;
        }
        return top;
    }
    void move(int r) {
        int c = w[r] + 1;
        for(; c <= n; ++c) {
            if(a[r][c]) break;
        }
        w[r] = c;
    }
    void back(int r) {
        int c = w[r] - 1;
        for(; c >= 1; --c) {
            if(a[r][c]) break;
        }
        w[r] = c;
    }
    int hsh() {
        
    }
} st;

struct cmp {
    bool operator()(const state& a, const state& b) const {
        int n = a.n;
        for(int i = 1; i <= n; ++i) {
            if(a.w[i] != b.w[i]) return false;
        }
        return true;
    }
};

struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.w[1];
        int n = st.n;
        for(int i = 2; i <= n; ++i) {
            res *= 19260817;
            res += st.w[i];
        }
        return res;
    }
};

unordered_map <state, ll, _hash, cmp> mp; 

int n;
char s[13][13];

ll dfs() {
    int stk[13], top;
    top = st.getline(stk);
    if(!top) return 0;
    if(mp.count(st)) return mp[st];
    ll res = INF;
    for(int i = 1, r, c, cost; i <= top; ++i) {
        //++Cnt;
        r = stk[i]; c = st.w[r];
        cost = abs(a[r][c]);
        st.move(r);
        res = min(res, cost + dfs());
        st.back(r);
    } 
    for(int i = 1, r1, r2, c1, c2, w1, w2; i <= top; ++i) {
        r1 = stk[i]; c1 = st.w[r1]; w1 = a[r1][c1];
        for(int j = i + 1; j <= top; ++j) {
            //++Cnt;
            r2 = stk[j]; c2 = st.w[r2]; w2 = a[r2][c2];
            if(w1 * w2 < 0) {
                st.move(r1); st.move(r2);
                res = min(res, abs(w1+w2) + dfs());
                st.back(r1); st.back(r2);
            }
        }
    }
    return mp[st] = res;
}

int main() {
    cin >> n;
    mp.reserve(1e7);
    for(int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    for(int i = 1, tmp; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            scanf("%d", &tmp);
            if(s[i][j] == 'W') a[i][j] = tmp;
            else a[i][j] = -tmp;
        }
    }
    st.n = n;
    for(int i = 1; i <= n; ++i) st.w[i] = 0;
    for(int i = 1; i <= n; ++i) {
        st.move(i);
    }
    ll res = dfs();
    printf("%lld\n", res);
    printf("%d\n", Cnt);
}

/*
12
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
WBWBWBWBWBWB
BWBWBWBWBWBW
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 1 1 1
*/