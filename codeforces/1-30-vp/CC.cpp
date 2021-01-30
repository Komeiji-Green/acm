#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> vec[30];
int S[21][(1<<20) + 5];
int Len[21];

void dfs(int x) {
    for(auto y : vec[x]) {
        dfs(y);
    }
    int &len = Len[x]; int *s = S[x];
    len = 1; s[0] = x;
    int l = 0, sz = vec[x].size();
    vector<int>& ch = vec[x];
    for(int i = 0; i < sz; ++i) {
        for(int j = 0; j < Len[ch[i]]; ++j) {
            s[len++] = S[ch[i]][j];
            if(j % 2) {
                for(int k = 1; k < l; ++k) {
                    s[len++] = s[k];
                }
            } else {
                for(int k = l - 1; k >= 1; --k) {
                    s[len++] = s[k];
                }
            }
        }
        l = len;
    }
}
int main() {
    int n;
    cin >> n;
    for(int i = 2, fa; i <= n; ++i) {
        scanf("%d", &fa);
        vec[fa].push_back(i);
    }
    dfs(1);
    cout << Len[1] - 1 << endl;
    for(int i = 1; i < Len[1]; ++i) {
        printf("%d ", S[1][i]);
    }
    printf("\n");
}