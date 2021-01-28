#include<iostream>
using namespace std;

const int maxn = 100000 + 100;
const int MOD = 1e9 + 7;


// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}



int pre1[maxn];
int pre0[maxn]; // 前缀和
int main()
{
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') {
            pre1[i + 1] = pre1[i] + 1;
            pre0[i + 1] = pre0[i];
        } else {
            pre0[i + 1] = pre0[i] + 1;
            pre1[i + 1] = pre1[i];
        }
    }
    while(q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        int cnt1 = pre1[r] - pre1[l - 1];
        int cnt0 = pre0[r] - pre0[l - 1];

        cout << 1ll * (Pow(2, cnt1, MOD) - 1) * (Pow(2, cnt0, MOD)) % MOD << endl;
    }
}