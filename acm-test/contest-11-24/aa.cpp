#include<bit/stdc++.h>
using namespace std;
typedef unsigned long long ll;

unsigned long long k1, k2;
unsigned long long xorShift128Plus() {
    unsigned long long k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3>>17) ^ (k4 >> 26);
    return k2 + k4;
}

int n, m;
struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge &b) {
        return w < b.w;
    }
} e[100001];

void gen() {
    scanf("%d%d%llu%llu", &n, &m, &k1, &k2);
    for(int i = 1; i <= m; ++i) {
        e[i].u = xorShift128Plus() % n + 1;
        e[i].v = xorShift128Plus() % n + 1;
        e[i].w = xorShift128Plus();
    }
}

const int N = 100500;
int f[N];
int find(int x) { return f[x] == x ? x : f[x] = find(f[x]);}
void merge(int x, int y) {
    int fx = find(x); int fy = find(y);
    f[fx] = fy;
}
int main() {
    int T;
    cin >> T;
    while(T--) {
        gen();
        sort(e + 1, e + m + 1);
        for(int i = 1; i <= m; ++i) 
        bool flag = false;
        for(int i = 1; i < m; ++i) {
            if(e[i].w == e[i + 1].w) {
                flag = true;
                break;
            }
        }
        if(flag) {

        } 
    }
}   