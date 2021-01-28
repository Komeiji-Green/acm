#include<iostream>
#include<cstring>
using namespace std;

int f[100100];  // fail数组，f[i] = [0, i)子串中，最长前缀=后缀的长度（不允许前缀后缀重合）

// 记录模式串fail数组：动态规划
void getNext(char *t, int len) {
    f[0] = -1; f[1] = 0; // 前缀后缀重合不算: 必须f[j] < j, 否则等着死循环8
    for(int i = 1, j = 0; i < len; i++) { // 进入循环时，j就是f[i]，之后会沿着f[i]往前挪
        while(j && t[i] != t[j]) j = f[j];
        if(t[i] == t[j]) j++;   // 正式编码时考虑两个极端情况，方便记模板
        f[i + 1] = j;
    }
}

int kmp(char *t, char *s) {
    // 可能要加getNext，也可能预处理
    int lens = strlen(s);
    int lent = strlen(t);
    for(int i = 0, j = 0; i < lens; i++) {
        while(j && s[i] != t[j]) j = f[j];   // 相当于按前后缀右移t序列
        if(s[i] == t[j]) j++;
        if(j == lent) { /* 匹配成功 return i - lent + 1; */  j = f[j]; }
    }
    return lens;
}

int extend[100100]; // 记录s每一个后缀关于t的最长前缀

void exKmp(char *t, char *s) {
    int lens = strlen(s), lent = strlen(t), i, j;

    getNext(t, lent);
    
    for(i = 0; i < lens; i++) {
        while(j && s[i] != t[j]) {
            extend[i - j] = j;
            j = f[j]; 
        }
        if(s[i] == t[j]) j++;
        if(j == lent) { extend[i + 1 - j] = j; j = f[j]; }
    }
    // 补齐
    while(j && i - j < lens) { extend[i - j] = j; j = f[j]; }
}

int main()
{
    char s[] = "abadabaabad";
    char t[] = "abaabac";
    getNext(t, strlen(t));
    cout << kmp(t, s) << endl;
}

/* manacher */
const int maxn = 300000;
// s[0]: 特殊值，s[1, 3 .. tot]: 分隔值 
int s[maxn], p[maxn]; // p 为半径
int L[maxn], R[maxn]; // 包含点i的回文串，回文中心最左、右
int n, tot;

void manacher() {
    int right = 0, idx = 0;
    for(int i = 1; i <= tot; i++) {
        if(i < right)
            p[i] = min(p[2 * idx - i], right - i);
        else
            p[i] = 1;

        while(i + p[i] <= tot && s[i + p[i]] == s[i - p[i]])
            p[i]++;

        p[i]--;

        if(i + p[i] > right) {
            right = i + p[i];
            idx = i;
        }
    }
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