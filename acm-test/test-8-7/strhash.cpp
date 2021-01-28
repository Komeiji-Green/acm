#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;

// 快速幂 计算 a^k % p
int Pow(int a, int k, int p) 
{
    int ans = 1;
    while(k) {
        if(k & 1) ans = 1ll * ans * a % p;
        k >>= 1; a = 1ll * a * a % p;
    }
    return ans;
}


// 双哈希
const int p1 = 1e9 + 7, p2 = 998244353, mod1 = 1e9 + 9, mod2 = 1610612741;
inline int id(char a) { return a - 'a' + 1; }
inline pair<int, int> dhash(char *s, int len) {
    int ans1 = 0;
    int ans2 = 0;
    for(int i = 0; i < len; i++) {
        ans1 = (1ll * ans1 * p1 + 1ll * id(s[i])) % mod1;
        ans2 = (1ll * ans2 * p2 + 1ll * id(s[i])) % mod2;
    }
    return make_pair(ans1, ans2);
}

// 子串哈希
const int maxn = 1000000 + 100;
char s[maxn];
int preh[maxn][2];  // 双哈希前缀和

void prehash(int len) {
    int ans1 = 0;
    int ans2 = 0;
    for(int i = 0; i < len; i++) {
        ans1 = (1ll * ans1 * p1 + 1ll * id(s[i])) % mod1;
        ans2 = (1ll * ans2 * p2 + 1ll * id(s[i])) % mod2;
        preh[i][0] = ans1;
        preh[i][1] = ans2;
    }
}

void subhash(int l, int r, int &hs1, int &hs2) {
    if(l == 0) {
        hs1 = preh[r][0]; hs2 = preh[r][1];
    } else {
        hs1 = (1ll * preh[r][0] - 1ll * preh[l - 1][0] * Pow(p1, r - l + 1, mod1) % mod1) % mod1;
        if(hs1 < 0) hs1 = hs1 + mod1;
        hs2 = (1ll * preh[r][1] - 1ll * preh[l - 1][1] * Pow(p2, r - l + 1, mod2) % mod2) % mod2;
        if(hs2 < 0) hs2 += mod2;
    }
}


char t[maxn];
int tab0[maxn][2];
int tab1[maxn][2];

int ans = 0;

int main()
{
    scanf("%s", t);
    scanf("%s", s);

    int lens = strlen(s);
    prehash(lens);

    int ones = 0, zeros = 0;
    for(int i = 0; t[i]; i++) {
        if(t[i] == '1') ones++;
        else zeros++; 
    }
    int lent = ones + zeros;

    for(int x = 1, y; x < lens / zeros; x++) {
        if((lens - zeros * x) % ones) continue;
        y = (lens - zeros * x) / ones;
        if(y <= 0) continue;

        int tot = 0, p0 = 0, p1 = 0;
        bool check = true;
        for(int i = 0; i < lent; i++) {
            if(t[i] == '0') {
                ++p0;
                subhash(tot, tot + x - 1, tab0[p0][0], tab0[p0][1]);
                tot += x;
            }
            else {
                ++p1;
                subhash(tot, tot + y - 1, tab1[p1][0], tab1[p1][1]);
                tot += y;
            }
            if(p0 >= 2) {
                for(int j = 0; j < 2; j++)
                    if(tab0[p0][j] != tab0[p0 - 1][j]) check = false;
            }
            if(p1 >= 2) {
                for(int j = 0; j < 2; j++) {
                    if(tab1[p1][j] != tab1[p1 - 1][j]) check = false;
                }
            }
            if(p1 && p0) {
                if(tab1[p1][0] == tab0[p0][0] && tab1[p1][1] == tab0[p0][1])
                    check = false;
            }
            //if(check == false) break;
        }

        /*printf("%d %d\n", x, y);
        for(int i = 1; i <= p0; i++)
            printf("%d %d  ", tab0[i][0], tab0[i][1]);
        cout << endl;
        for(int i = 1; i <= p1; i++)
            printf("%d %d  ", tab1[i][0], tab1[i][1]);
        cout << endl;*/


        if(check) ans++;
    }
    cout << ans << endl;
}