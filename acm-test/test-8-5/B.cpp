#include<iostream>
using namespace std;

const int maxn = 1000 + 5;
int A[maxn][maxn], C[maxn][maxn], n;  // 二维树状数组
// C[i][j] 看管 (i - lowbit(i), j - lowbit(j)) 到 (i, j) 间的点
void add(int x, int y, int v) {
    for(int i = x; i <= n; i += i & (-i))
        for(int j = y; j <= n; j += j & (-j))
            C[i][j] ^= v;
}
int query(int x, int y) {
    int ans = 0;
    for(int i = x; i > 0; i -= i & (-i))
        for(int j = y; j > 0; j -= j & (-j))
            ans ^= C[i][j];
    return ans;
}

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int q;
        cin >> n >> q;
        for(int i = 0; i <= n; i++) {
            for(int j = 0; j <= n; j++) {
                C[i][j] = 0;
            }
        }
        char op[4];
        int x, y, xx, yy;
        while(q--) {
            scanf("%s", op);
            if(op[0] == 'C') {
                scanf("%d%d%d%d", &x,&y,&xx,&yy);
                add(x, y, 1);
                if(yy != n) add(x, yy + 1, 1);
                if(xx != n) add(xx + 1, y, 1);
                if(xx != n && yy != n) add(xx + 1, yy + 1, 1);
            } else if(op[0] == 'Q') {
                scanf("%d%d", &x,&y);
                printf("%d\n", query(x, y));
            }
        }
        cout << endl;
    }
}