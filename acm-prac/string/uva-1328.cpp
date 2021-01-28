#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn = 1000500;
int f[maxn];

void getFail(char *t, int len) {
    f[0] = -1; f[1] = 0;
    for(int i = 1, j = 0; i < len; ++i) {
        while(j && t[j] != t[i]) j = f[j];
        if(t[j] == t[i]) ++j;
        f[i + 1] = j;
    }
}

char s[maxn];

int main() {
    int n;
    int cas = 0;
    while(scanf("%d", &n) != EOF && n) {
        ++cas;
        scanf("%s", s);
        int len = strlen(s);
        getFail(s, len);
        printf("Test case #%d\n", cas);
        for(int i = 2; i <= len; ++i) {
            int l = i - f[i];
            if(i % l == 0 && i > l) {
                printf("%d %d\n", i, i / l);
            }
        }
        printf("\n");
    }
}