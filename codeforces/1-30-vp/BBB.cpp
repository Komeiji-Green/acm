#include<bits/stdc++.h>
#include<ctime>
using namespace std;
typedef long long ll;
const int maxn = 3333333;
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

void test() {
    printf("ttt: ");
    for(int i = 0; i < 10; ++i) printf("%c ", (char)vis[i]);
}

void dfs(int k, int j, int p, int C) {
    if(k == m) {
        int ch, y, S = C;
        if(C == 0) {
            ++cnt[p]; //test(); printf("%d\n", p);
        } else if(vis[S]) {
            ch = vis[S];
            if(!(y = tr[p][ch-'A'])) return;
            ++cnt[y];
            //test(); printf("%d\n", y);
        } else {
            for(ch = 'A'; ch <= 'Z'; ++ch) {
                if(tab[ch] != -1) continue;
                if(!(y = tr[p][ch-'A'])) continue;
                ++cnt[y]; //test(); printf("%d\n", y);
            }
        }
    } else if(j <= 1) {
        int ch = (j == 0 ? a[k] : b[k]);
        if(tab[ch] != -1) { // tab[0] == 0;
            dfs(k, j + 1, p, C);
        } else {
            for(int i = 0; i < 10; ++i) {
                if(vis[i]) continue;
                if(!i && (ch == ha || ch == hb)) continue;
                tab[ch] = i; vis[i] = ch;
                dfs(k, j + 1, p, C);
                tab[ch] = -1; vis[i] = 0;
            }
        }
    } else {
        int S = tab[a[k]] + tab[b[k]] + C;
        int nxtC = S / 10; S = S % 10;
        int ch, y;
        if(vis[S]) {
            ch = vis[S];
            if(!(y = tr[p][ch-'A'])) return;
            dfs(k + 1, 0, y, nxtC);
        } else {
            for(ch = 'A'; ch <= 'Z'; ++ch) {
                if(tab[ch] != -1) continue;
                if(!(y = tr[p][ch-'A'])) continue;
                if(!S && (ch == ha || ch == hb)) continue;
                tab[ch] = S; vis[S] = ch;
                dfs(k + 1, 0, y, nxtC);
                tab[ch] = -1; vis[S] = 0;
            }
        }
    }
}

int main() {
    //clock_t st = clock(), ed;
    //freopen("brainteaser-2.in", "r", stdin);
    scanf("%s %s", &a, &b);
    la = strlen(a); lb = strlen(b);
    for(int i = 0; i < la - 1 - i; ++i) swap(a[i], a[la - 1 - i]);
    for(int j = 0; j < lb - 1 - j; ++j) swap(b[j], b[lb - 1 - j]);
    m = max(la, lb);
    for(int i = la; i <= m; ++i) a[i] = '\0';
    for(int j = lb; j <= m; ++j) b[j] = '\0';
    ha = a[la-1]; hb = b[lb-1];

    //printf("%s\n%s\n", a, b);

    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%s", s[i]);
        int len = strlen(s[i]);
        v[i] = insert(s[i], len);
    }
    for(int i = 'A'; i <= 'Z'; ++i) tab[i] = -1;
    for(int i = 0;  i < 10; ++i) vis[i] = 0;

    //for(int i = 1; i <= n; ++i) printf("(%d: %d) ", i, v[i]);
    //printf("\nttt: ");
    //for(int i = 0; i < 10; ++i) printf("%d ", i);
    //printf("\n");
    dfs(0, 0, 0, 0);

    int num = 0;
    for(int i = 1; i <= n; ++i) {
        //printf("tst: %d\n", cnt[v[i]]);
        if(cnt[v[i]] == 1) {
            ans[++num] = i;
        }
    }
    cout << num << endl;
    for(int i = 1; i <= num; ++i) {
        printf("%s\n", s[ans[i]]);
    }
    //ed = clock();
    //cout << (double)(ed - st)/ 1000 << endl;
}