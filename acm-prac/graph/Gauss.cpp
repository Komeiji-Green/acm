const int N = 20;
struct Mat {
    int a[N][N], n, m;
    // 小模数int，记得改溢出！！！
    void set(int _n, int _m, int val) {
        n = _n, m = _m;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) a[i][j] = val;
    }
    int guass() { // 行初等变换
        int ans = 1; // 行列式
        for(int j = 0, sig; j < m; ++j) {
            sig = -1;
            for(int i = j; i < n; ++i) if(a[i][j]) {
                sig = i; break;
            }
            if(sig == -1) break;
            if(sig != j) { // 换法变换
                for(int k = j; k < m; ++k) swap(a[j][k], a[sig][k]);
                ans = -ans;
            }
            int inv = Pow(a[j][j], mod - 2, mod);
            for(int i = j + 1; i < n; ++i) { // 消法变换
                int ratio = a[i][j] * inv % mod; // a[i][j] / a[j][j]
                a[i][j] = 0;
                for(int k = j + 1; k < m; ++k) {
                    a[i][k] = (a[i][k] - a[j][k] * ratio % mod) % mod;
                }
            }            
        }
        for(int i = 0; i < m && i < n; ++i) {
            ans = ans * a[i][i] % mod;
        }
        printf("\n");
        for(int i = 0; i <= n; ++i) {
            for(int j = 0; j <= m; ++j) printf("%d ", a[i][j]);
            printf("\n");
        }
        printf("ans: %d\n", (ans + mod) % mod);

        return ans;
    }
} mat;


const int N = 20;
struct Mat {
    int a[N][N], n, m;
    void set(int _n, int _m, int val) {
        n = _n, m = _m;
        for(int i = 0; i < n; ++i) for(int j = 0; j < m; ++j) a[i][j] = val;
    }
    int guass() { // 辗转相除化简(当mod大时可能会溢出)
        int ans = 1;
        for(int j = 0; j < m; ++j) {
            for(int i = j + 1; i < n; ++i) {
                while(a[i][j]) {
                    int t = a[j][j] / a[i][j];
                    for(int k = j; k < m; ++k)
                        a[j][k] = (a[j][k] - t * a[i][k] % mod + mod) % mod; 
                    swap(a[i], a[j]);
                    ans = -ans;
                }
            }
        }
        for(int i = 0; i < m && i < n; ++i) ans = ans * a[i][i] % mod;
        return (ans + mod) % mod;
    }
} mat;

const int L = 512;
ll a[L][L+1], ans[L];
void gauss(int n, int m) { // 消增广矩阵
    vector<int> pos(m, -1);
    ll inv, del;
    for(int r = 0, c = 0; c < m; ++c) {
        int sig = -1;
        for(int i = r; i < n; ++i) 
            if(a[i][c]) {
                sig = i; break;
            }
        if(sig == -1) continue;
        pos[c] = r;
        if(sig != r) swap(a[sig], a[r]);
        inv = Pow(a[r][c], mod - 2);
        for(int i = 0; i < n; ++i) {
            if(i == r) continue;
            del = inv * a[i][c] % mod;
            for(int j = c; j <= m; ++j) a[i][j] = (a[i][j] - del * a[r][j] % mod) % mod; 
        }
        ++r;
    }
    for(int i = 0; i < m; ++i) {
        if(pos[i] != -1) {
            ans[i] = Pow(a[pos[i]][i], mod - 2) * a[pos[i]][m] % mod;
        }
    }
}