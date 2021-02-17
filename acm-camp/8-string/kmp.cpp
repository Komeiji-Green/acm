#include<bits/stdc++.h>
using namespace std;

const int N = 2333333;
int fail[N];
void getNext(char *t, int len) {
    int i = 0, j = -1; fail[0] = -1;
    while(i < len) {
        while(j != -1 && t[i] != t[j]) j = fail[j];
        ++i; ++j; fail[i] = j;
    }
}
int kmp(char *s, int lenS, char *t, int lenT) {
    int i = 0, j = 0;
    while(i < lenS && j < lenT) {
        while(j != -1 && s[i] != t[j]) j = fail[j];
        ++i; ++j;
    }
    return j >= lenT ? i - lenT : -1; 
}

int ans[N], tot = 0;
void solve(char *s, int lenS, char *t, int lenT) {
    int i = 0, j = 0;
    while(i < lenS && j <= lenT) {
        while(j != -1 && s[i] != t[j]) j = fail[j];
        ++i; ++j;
        if(j == lenT) ans[++tot] = i - lenT, j = fail[j];
    }
}

char s[N], t[N];
int main() {
    scanf("%s %s", s, t);
    int n = strlen(s), m = strlen(t);
    getNext(t, m);
    //for(int i = 0; i < m; ++i) printf("%d ", fail[i]);
    //printf("\n");
    solve(s, n, t, m);
    for(int i = 1; i <= tot; ++i) printf("%d\n", ans[i] + 1);
    for(int i = 1; i <= m; ++i) printf("%d ", fail[i]);
    printf("\n");
}   