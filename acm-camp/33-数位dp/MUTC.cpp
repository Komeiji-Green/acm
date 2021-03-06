#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 2020 MUTC-3 F
int a[20];
struct state {
    int d, w[10], cnt[11];
    bool chk() {
        return !cnt[10];
    }
    bool test() {
        for(int i = 0; i <= 9; ++i) {
            if(i != d && w[i] >= w[d]) return 0;
        }
        return 1;
    }
    state add(int i) const {
        state res = *this;
        if(i!=d) res.cnt[w[i]]--, res.cnt[w[i]+1]++;
        res.w[i]++;
        return res;
    }
    void print() {
        for(int i = 0; i < 9; ++i) printf("(%d, %d) ", i, w[i]);
        printf("\n");
    }
};

struct cmp {
    bool operator()(const state& a, const state& b) const {
        if(a.w[a.d]!=b.w[b.d]) return false;
        for(int i = 0; i < 10; ++i) {
            if(a.cnt[i]!=b.cnt[i]) return false;
        }
        return true;
    }
};

struct _hash {
    size_t operator()(const state& st) const {
        size_t res = st.cnt[0];
        for(int i = 1; i < 10; ++i) {
            res *= 19260817;
            res += st.cnt[i];
        }
        return res;
    }
};

unordered_map <state, ll, _hash, cmp> dp[20][20];
//ll l,r,dp[20][15][25][25][20];

ll dfs(int pos, state st, int lead, int limit)
//pos搜到的位置
//st当前状态
//lead判断是否有前导0
//limit判断是否有最高位限制
{
    if(!st.chk()) return 0;
    if(pos<0) {
        if(st.chk() && st.test()) {
            //st.print();
            return 1;
        }
        else return 0;
    }
    // 记忆化搜索
    int wd = st.w[st.d];
    if((!limit) && (!lead) && dp[pos][wd].count(st)) return dp[pos][wd][st];

    ll res = 0;
    // 最高位最大值
    int cur = limit ? a[pos] : 9;
    for(int i = 0; i <= cur; ++i) {
        // 有前导0且当前位也是0
        if((!i) && lead) res += dfs(pos-1, st, 1, limit&&(i==cur));
        // 有前导0且当前位非0（出现最高位）
        else if(i && lead) res += dfs(pos-1, st.add(i), 0, limit&&(i==cur));
        else res += dfs(pos-1, st.add(i), 0, limit&&(i==cur));
    } 
    // 没有前导0和最高限制时可以直接记录当前dp值以便下次搜到同样的情况可以直接使用。 
    if(!limit&&!lead) dp[pos][wd][st] = res;
    return res;
}
ll gao(ll x, int d) {
    memset(a, 0, sizeof(a));
    int len=0;
    while(x) a[len++]=x%10,x/=10;
    state st; 
    for(int i = 0; i < 10; ++i) st.w[i] = 0;
    for(int i = 0; i < 11; ++i) st.cnt[i] = 0;
    st.cnt[0] = 9;
    st.d = d;
    return dfs(len-1, st, 1, 1);
}
int main()
{
    int T;
    ll l, r; int d;
    cin >> T;
    while(T--) {
        scanf("%lld %lld %d", &l, &r, &d);
        ll ans = gao(r, d) - gao(l - 1, d);
        printf("%lld\n", ans);
    }
}