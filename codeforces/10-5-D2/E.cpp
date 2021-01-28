#include<bits/stdc++.h>
#include<vector>
using namespace std;
typedef unsigned long long ull;

const int N = 300500;
const int lg = 25;
int anc[N][lg], ans[N], len[N];
ull hsh[N][lg], p[N];
char s[N];

int cmp(int i, int j) {
    int fi, fj;
    while(1) {
        if(!s[i] && !s[j]) return 0;
        if(s[i] != s[j]) return s[i] - s[j];
        for(int k = 0; anc[i][k] != -1 && anc[j][k] != -1 && hsh[i][k] == hsh[j][k]; ++k) {
            fi = anc[i][k], fj = anc[j][k];
        }
        i = fi, j = fj;
    }
}

bool vis[N];
vector<int> ch[N];
char oo[N][12], stk[N];
int top = 0;

void dfs(int x) {
    if(s[x]) stk[top++] = s[x];
    len[x] = top;
    if(top <= 10) {
        for(int i = 0; i < top; ++i) 
            oo[x][top - 1 - i] = stk[i];
        oo[x][top] = '\0';
    } else {
        for(int i = 0; i < 5; ++i) {
            oo[x][i] = stk[top - 1 - i];
        }
        for(int i = 5; i < 8; ++i) oo[x][i] = '.';
        oo[x][8] = stk[1], oo[x][9] = stk[0];
        oo[x][10] = '\0';
    }
    for(auto y : ch[x]) {
        //printf("%d:%d\n", x, y);
        dfs(y);
    }
    if(s[x]) top--;
}
int main() {
    scanf("%s", s);
    int n = strlen(s);
    memset(anc, 0xff, sizeof(anc));
    memset(ans, 0xff, sizeof(ans));
    const ull P = 83;
    p[0] = 1;
    for(ull i = 1; i <= (ull)(n); ++i) {
        p[i] = p[i-1] * P;
    }
    ans[n] = n;
    len[n] = 0;
    for(int i = n - 1, c, j; i >= 0; --i) {
        hsh[i][0] = s[i];
        anc[i][0] = ans[i+1];
        for(int k = 1, f; (f = anc[i][k-1]) != -1; ++k) {
            anc[i][k] = anc[f][k-1];
            hsh[i][k] = hsh[f][k-1] + hsh[i][k-1] * p[1<<(k-1)];
        }
        ans[i] = i, len[i] = len[i+1] + 1;
        if(s[i] == s[i+1]) {
            j = ans[i+2];
            c = cmp(i, j);
            //printf("%d %d: %d\n", i, j, c);
            if(c >= 0) ans[i] = j, len[i] = len[j];
        }
    }
    for(int i = 0; i <= n; ++i) vis[ans[i]] = true;
    for(int i = 0; i <= n; ++i) {
        if(vis[i] && anc[i][0] != -1) {
            ch[anc[i][0]].push_back(i);
        }  
    }
    top = 0;
    dfs(n);
    /*for(int i = 0; i < n; ++i) {
        printf("%d : %d\n", i, ans[i]);
    }*/
    for(int i = 0, j; i < n; ++i) {
        j = ans[i];
        printf("%d %s\n", len[j], oo[j]);
    }
}