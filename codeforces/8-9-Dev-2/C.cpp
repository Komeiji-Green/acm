#include<iostream>
#include<string>
using namespace std;

// 快速幂 计算 a^k % p
// a <= 1e9, k <= 1e9

const int mod = 1e9 + 7;
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}

int Fact(int n, int mod) {
    int ans = 1;
    for(int i = 1; i <= n; i++)
        ans = 1ll * ans * i % mod;
    return ans;
}


int main()
{
    int n;
    cin >> n;
    int a = Pow(2, n - 1, mod);
    int b = Fact(n, mod);
    int ans = (b - a) % mod;
    cout << (ans < 0 ? ans + mod : ans) << endl;
}