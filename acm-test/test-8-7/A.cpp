#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 500500;

int f[maxn];  // fail数组，f[i] = [0, i)子串中，最长前缀=后缀的长度（不允许前缀后缀重合）
char s[maxn];
char t[maxn];
char ans[maxn];

// 记录模式串fail数组：动态规划
void getNext(char *t, int len) {
    f[0] = 0; f[1] = 0;
    for(int i = 1, j = 0; i < len; i++) { 
        while(j && t[i] != t[j]) j = f[j];
        if(t[i] == t[j]) j++;  
        f[i + 1] = j;
    }
}

int main()
{
    scanf("%s", s);
    scanf("%s", t);

    int lens = strlen(s);
    int lent = strlen(t);

    int cnts[2] = {};
    int cntt[2] = {};
    int cnttail[2] = {};
    for(int i = 0; i < lens; i++) {
        cnts[s[i] - '0']++;
    }
    for(int i = 0; i < lent; i++) {
        cntt[t[i] - '0']++;
    }

    getNext(t, strlen(t));
    for(int i = f[lent]; i < lent; i++) {
        cnttail[t[i] - '0']++;
    }

    int step = lent - f[lent];

    int cnt1 = 0;
    int cnt0 = 0;
    for(int i = lent; i < lens; i += step) {
        if(cntt[0] > cnts[0] || cntt[1] > cnts[1])
            break;
        if(i == lent) { 
            cnt0 += cntt[0]; cnt1 += cntt[1];
            strcat(ans, t);
        }
        if(cnt0 + cnttail[0] <= cnts[0] && cnt1 + cnttail[1] <= cnts[1]) {
            cnt0 += cnttail[0]; cnt1 += cnttail[1];
            strcat(ans, t + f[lent]);
        }
    }
    for(int i = 0; i < cnts[0] - cnt0; i++) {
        strcat(ans, "0");
    }
    for(int i = 0; i < cnts[1] - cnt1; i++) {
        strcat(ans, "1");
    }
    printf("%s\n", ans);
}