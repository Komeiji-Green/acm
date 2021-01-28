#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 200100;

bool cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}

int c[maxn], ix[maxn], iy[maxn];

void da(int s[], int sa[], int rk[], int height[], int n, int m) {
    n++; // !!!!
    int *x = ix, *y = iy;
    for(int i = 0; i < m; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for(int i = 1; i < m; i++) c[i] += c[i - 1];
    for(int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;

    int p;
    for(int j = 1; j <= n; j <<= 1) {
        p = 0;
        for(int i = n - j; i < n; i++) y[p++] = i;
        for(int i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;

        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) c[x[y[i]]]++;
        for(int i = 1; i < m; i++) c[i] += c[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];

        swap(x, y);
        p = 1; x[sa[0]] = 0;
        for(int i = 1; i < n; i++) 
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
        if(p >= n) break; // 剪枝
        m = p; // 下次基数总数
    }

    for(int i = 0; i < n; i++) rk[sa[i]] = i;

    n--;
    int h = 0;  // 当前height值

    for(int i = 0; i < n; i++) {
        int j = sa[rk[i] - 1];
        if(h) h--;
        while(s[i + h] == s[j + h]) h++;
        height[rk[i]] = h;
    }
}

// test: UOJ35

char str[maxn];
int s[maxn], sa[maxn], rk[maxn], height[maxn];
int main() {
    scanf("%s", str);
    int n = strlen(str);
    for(int i = 0; i < n; i++) {
        s[i] = str[i];
    }
    s[n] = 0;
    
    da(s, sa, rk, height, n, 300);
    for(int i = 1; i <= n; i++) {
        printf("%d ", sa[i] + 1);
    }
    printf("\n");
    for(int i = 2; i <= n; i++) {
        printf("%d ", height[i]);
    }
    printf("\n");
}
