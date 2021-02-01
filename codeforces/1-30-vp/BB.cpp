#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 333333;
char a[20], b[20], s[maxn][20];
int tr[maxn][26], cnt[maxn], tot;

int v[maxn];    // 字符串在trie上对应的结点
int insert(char *t, int len) {
    int p = 0;
    for(int i = len - 1, c; i >= 0; --i) {
        c = t[i] - 'A';
        if(!tr[p][c]) tr[p][c] = ++tot;
        p = tr[p][c];
    }
    return p;
}

int m, la, lb;
int tab[105], vis[10], ans[maxn];
int ha, hb;
void dfs(int k, int p, int C) { // 第 k 位， trie 上结点p, 进位
    printf("%d %d %d\n", k, p, C);
    if(tab[ha]==0||tab[hb]==0) return;
    if(k == m) {
        if(!C) ++cnt[p];
        else {
            int c;
            if(vis[1]) {
                c = vis[1] - 'A';
                if(tr[p][c]) ++cnt[tr[p][c]];
            } else {
                for(c = 'A'; c <= 'Z'; ++c) {
                    if(tab[c] == -1 && tr[p][c-'A']) {
                        ++cnt[tr[p][c-'A']];
                    }
                }
            }
        }
        return;
    }
    int S, nxtC, y;
    int sza, szb;
    sza = (~tab[a[k]]) ? 1 : 10; 
    for(int i = 0; i < sza; ++i) {
        if(sza!=1) {
            if(vis[i]) continue;
            tab[a[k]] = i; vis[i] = a[k];
        }
        szb = (~tab[b[k]]) ? 1 : 10;
        for(int j = 0; j < szb; ++j) {
            if(szb != 1) {
                if(vis[j]) continue;
                tab[b[k]] = j; vis[j] = b[k];
            }
            S = tab[a[k]] + tab[b[k]] + C;
            nxtC = (S >= 10) ? 1 : 0;
            S = (S >= 10) ? S - 10 : S;
            if(vis[S]) {
                y = tr[p][vis[S]-'A'];
                if(y) dfs(k+1,y,nxtC);
            } else {
                for(int c = 'A'; c <= 'Z'; ++c) {
                    if(!(y = tr[p][c-'A'])) continue;
                    if((~tab[c]) && tab[c] != S) continue;
                    //if(!(~tab[c]) && vis[S]) continue;
                    if(!(~tab[c])) {tab[c] = S; vis[S] = c;}
                    dfs(k+1,y,nxtC);
                    if(!(~tab[c])) tab[c] = -1, vis[S] = 0;
                }
            }
            if(szb != 1) {tab[b[k]] = -1, vis[j] = 0;}
        }
        if(sza!=1) {tab[a[k]] = -1, vis[i] = 0;}
    }


    /*if(tab[a[k]] == -1) {
        if(tab[b[k]] == -1) {
            s = tab[a[k]] + tab[b[k]] + c;
            c = (s >= 10) ? 1 : 0;
            s = (s >= 10) ? s - 10 : s;
            
        }
        for(int j = 0; j < 10; ++j) {
            if()
        }
    } else {
        for(int i = 0; i < 10; ++i) {
            if(vis[i]) continue;
            tab[a[k]] = i; vis[i] = 1;
            if(~tab[b[k]]) {
                for(int j = 0; j < 10; ++j) {
                    if(vis[j]) continue;
                    tab[b[k]] = j; vis[j] = 1;
                    
                }
            }
            tab[a[k]] = -1; vis[i] = 0;
        }
    }*/
    
}
int main() {
    //freopen("brainteaser-2.in", "r", stdin);
    scanf("%s %s", &a, &b);
    la = strlen(a); lb = strlen(b);
    for(int i = 0; i < la - 1 - i; ++i) swap(a[i], a[la - 1 - i]);
    for(int j = 0; j < lb - 1 - j; ++j) swap(b[j], b[lb - 1 - j]);
    m = max(la, lb);
    ha = a[la-1]; hb = b[lb-1];

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s[i]);
        int len = strlen(s[i]);
        v[i] = insert(s[i], len);
    }
    for(int i = 'A'; i <= 'Z'; ++i) tab[i] = -1;
    for(int i = 0;  i < 10; ++i) vis[i] = 0;
    dfs(0, 0, 0);

    int num = 0;
    for(int i = 1; i <= n; ++i) {
        //printf("tst: %d\n", v[i]);
        if(cnt[v[i]] == 1) {
            ans[++num] = i;
        }
    }
    cout << num << endl;
    for(int i = 1; i <= num; ++i) {
        printf("%s\n", s[ans[i]]);
    }
}