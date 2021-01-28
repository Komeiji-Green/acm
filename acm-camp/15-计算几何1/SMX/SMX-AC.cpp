
// 模板

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 100050;

int ch[maxn*60][2], tot;
int sum[maxn*60], len[maxn*60];
int lnum[maxn*60], rnum[maxn*60], num[maxn*60];
int root;
void pushup(int k, int l, int r) {
    if(sum[k]) {
        len[k] = r - l + 1;
        lnum[k] = rnum[k] = num[k] = 1;
    }
    else if(l == r) len[k] = lnum[k] = rnum[k] = num[k] = 0;
    else {
        int lch = ch[k][0], rch = ch[k][1];
        len[k] = len[lch] + len[rch];
        num[k] = num[lch] + num[rch] - (rnum[lch] && lnum[rch]);
        lnum[k] = lnum[lch]; rnum[k] = rnum[rch];
    }
}
void add(int &k, int L, int R, int v, int l, int r) {
    if(!k) k = ++tot;
    if(L <= l && r <= R) {
        sum[k] += v;
        pushup(k, l ,r);
    } else {
        int mid = l + ((r - l) >> 1);
        if(L <= mid) add(ch[k][0], L, R, v, l, mid);
        if(R > mid) add(ch[k][1], L, R, v, mid + 1, r);
        pushup(k, l, r);
    }
} 

struct Line {
    ll l, r, h;
    int tag;
    bool operator< (const Line& b) {
        return h < b.h || h == b.h && tag > b.tag;
    }
} lx[maxn], ly[maxn];

const int MAXL = 30000;
ll gao(Line* lx, int m) {
    ll last_h = 0, last_len = 0, last_num = 0;
    ll cur_h = lx[1].h, cur_len, cur_num;
    ll ans = 0;
    for(int i = 1; i <= m; ++i) {
        add(root, lx[i].l, lx[i].r - 1, lx[i].tag, 1, MAXL);
        cur_len = len[root], cur_num = num[root], cur_h = lx[i].h;
        ans += 2 * (cur_h - last_h) * last_num;
        ans += abs(cur_len - last_len);
        last_len = cur_len, last_num = cur_num, last_h = cur_h;
    }
    return ans;
}
int main() {
    int m;
    cin >> m;
    ll x1, y1, x2, y2;
    for(int i = 1; i <= m; ++i) {
        scanf("%lld%lld%lld%lld", &x1, &y1, &x2, &y2);
        x1 += 10001; x2 += 10001; y1 += 10001; y2 += 10001;
        lx[i].tag = 1; lx[i].l = x1; lx[i].r = x2; lx[i].h = y1;
        lx[m + i].tag = -1; lx[m + i].l = x1; lx[m + i].r = x2; lx[m + i].h = y2;
        ly[i].tag = 1; ly[i].l = y1; ly[i].r = y2; ly[i].h = x1;
        ly[m + i].tag = -1; ly[m + i].l = y1; ly[m + i].r = y2; ly[m + i].h = x2;
    }
    m = 2 * m;
    sort(lx + 1, lx + m + 1);
    sort(ly + 1, ly + m + 1);
    ll ans = 0;
    ans = gao(lx, m);
    cout << ans << endl;
}