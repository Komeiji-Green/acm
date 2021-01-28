#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef unsigned long long ll;
const ll mod = 100000007;
#define eps 1e-7

// 快速幂 计算 a^k % p
ll Pow(ll a, ll k, ll p) {
    ll ans = 1;
    while(k) {
        if(k & 1) ans = ans * a % p;
        k >>= 1; a = a * a % p;
    }
    return ans;
}

struct matrix {
  static const int maxn = 1001;
  int n, m;
  ll mat[maxn][maxn];
  matrix() { memset(mat, 0, sizeof(mat)); }
  void print() {
    cout << "MATRIX " << n << " " << m << endl;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << mat[i][j] << "\t";
      }
      cout << endl;
    }
  }
  void random(int n) {
    this->n = n;
    this->m = n;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) mat[i][j] = rand() % 100;
  }
  void initSquare() {
    this->n = 4;
    this->m = 4;
    memset(mat, 0, sizeof(mat));
    mat[0][1] = mat[0][3] = 1;
    mat[1][0] = mat[1][2] = 1;
    mat[2][1] = mat[2][3] = 1;
    mat[3][0] = mat[3][2] = 1;
    mat[0][0] = mat[1][1] = mat[2][2] = mat[3][3] = -2;
    this->n--;  // 去一行
    this->m--;  // 去一列
  }
  ll gauss() {
    ll ans = 1;
    for (int i = 0; i < n; i++) {
      int sid = -1;
      for (int j = i; j < n; j++)
        if (mat[j][i]) {
          sid = j;
          break;
        }
      if (sid == -1) continue;
      if (sid != i) {
        for (int j = 0; j < n; j++) {
          swap(mat[sid][j], mat[i][j]);
          ans = -ans;
        }
      }
      for (int j = i + 1; j < n; j++) {
        ll ratio = mat[j][i] * Pow(mat[i][i], mod-2, mod) % mod;
        for (int k = 0; k < n; k++) {
          mat[j][k] = (mat[j][k] - mat[i][k] * ratio % mod) % mod;
        }
      }
    }
    for (int i = 0; i < n; i++) ans = ans * mat[i][i] % mod;
    return ans;
  }
};

unsigned long long k1, k2;
unsigned long long xorShift128Plus() {
    unsigned long long k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3>>17) ^ (k4 >> 26);
    return k2 + k4;
}

struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge &b) {
        return w < b.w;
    }
} e[100001];
int n, m;

void gen() {
    scanf("%d%d%llu%llu", &n, &m, &k1, &k2);
    for(int i = 1; i <= m; ++i) {
        e[i].u = xorShift128Plus() % n + 1;
        e[i].v = xorShift128Plus() % n + 1;
        e[i].w = xorShift128Plus();
    }
}

const int N = 100005;
int f[N];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]);}
void merge(int x, int y) {
    int fx = find(x); int fy = find(y);
    f[fx] = fy;
}

int cc[N], t1; // cc: 当前的所有连通分量
int ncc[N], t2; // 下一刻所有的连通分量
vector<int> li[N]; // 从属于新连通分量的所有子分量

vector<int> G[N];
int cc[N], id[N], t1;

int main() {
    gen();
    sort(e + 1, e + m + 1);
    bool flag = false;
    int last = 1;
    for(int i = 1; i <= m; ++i) {
        if(i == m || e[i].w != e[i+1].w) {
            for(int j = 0; j < t1; ++j) {

            }
            for(int j = last; j <= i; ++j) {
                int fu = find(e[j].u), fv = find(e[j].v);
                if(fu == fv) continue;
                G[fu].push_back(fv);
                G[fv].push_back(fu);
                ++deg[fu]; ++deg[fv];
            }
            for(int j = last; j <= i; ++j) {
                merge(e[j].u, e[j].v);
            }
            t2 = 0;
            for(int j = 0; j < t1; ++j) {
                li[f[cc[j]]].push_back(cc[j]);
                ncc[t2++] = f[cc[j]];
            }
            sort(ncc, ncc + t2);
            t2 = unique(ncc, ncc + t2) - ncc;
            for(int j = 0; j < t2; ++j) {
                vector<int>& list = li[ncc[j]];
                for(int k = 0; k < list.size(); ++k) {
                    id[list[k]] = k;
                }
                
            }
            for(int j = 0; j < t1; ++j) {
                cc[j]
            }
        }
    }
}