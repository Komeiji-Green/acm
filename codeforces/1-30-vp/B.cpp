#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 333333;
char a[20], b[20], s[333333][20];
bool ans[maxn];
bool vis[30];


int li[30], p[30], val[30], ival[30], c[30];
int in[30], es, num, tot;
node tab[30];

struct node {
    int x, y;
};

struct {
    int val[26];
    ll sum;
} tt[maxn*12];

ll calc(char *t) {
    ll res = 0;
    for(int i = 0; t[i]; ++i) {
        res = res * 10 + val[t[i]-'A'];
    }
    return res;
}

int main() {
    //freopen("brainteaser-2.in", "r", stdin);
    scanf("%s %s", a, b);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s[i]);
    }
    for(int i = 0; a[i]; ++i) vis[a[i]-'A']=1;
    for(int i = 0; b[i]; ++i) vis[b[i]-'A']=1;
    for(int i = 0; i < 26; ++i) if(vis[i]) li[num++] = i;
    for(int i = 0 i < 10; ++i) p[i] = i;

    ll aa, bb, cc, tmp;
    int d = 0; // 位数
    do {
        ++tot;
        sort(p + num, p + 10);
        for(int i = 0; i < 10; ++i) ival[i] = -1, in[i] = 0;
        for(int i = 0; i < num; ++i) {
            val[li[i]] = p[i];
            ival[p[i]] = li[i];
        }
        aa = calc(a);
        bb = calc(b);
        cc = aa + bb;
        tmp = cc;
        es = d = 0;
        while(tmp) {
            int x = tmp % 10;
            if(ival[x] == -1) {
                in[x] = 1;
                c[d] = ;
            } else {
                c[d] = ival[x];
            }
            ++d;
        }
        
        
        

    } while(next_permutation(p, p + 10));



    if(num <= 5) {
        int tot = 0;
        for(int i = 1; i <= num; ++i) p[0][i] = i;
        do {
            ++tot;
            for(int i = 1; i <= num; ++i) p[tot][i] = p[0][i];
        } while(next_permutation(p[0] + 1, p[0] + num + 1));
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= tot; ++j) {
                for(int k = 1; k <= num; ++k) {
                    val[li[p[j][k]]-'A']=
                }
            }
        }
    }
}