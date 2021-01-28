#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 500050;
const int inf = 0x3f3f3f3f;

bool cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}

int c[maxn], ix[maxn], iy[maxn], s[maxn];

bool cp(int x, int y) {
    return s[x] < s[y];
}

/*
下面“后缀”默认为后缀的首字母下标
sa: 排名->后缀
x: 后缀->去重排名(需要利用cmp函数判重)
y: key_2排名->后缀
c: key_1去重排名i->排名从0到i的后缀总数量
*/
// 求解值域较大数组的sa，无需事先离散化
void da(int sa[], int rank[], int height[], int n, int m) {
    n++; // !!!!
    int *x = ix, *y = iy, p;
    for(int i = 0; i < n; i++) y[i] = i;
    sort(y, y + n, cp);
    for(int i = 0; i < n; i++) sa[i] = y[i];
    p = 1; x[sa[0]] = 0;
    for(int i = 1; i < n; i++)
        x[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? p - 1 : p++;

    m = p;

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
    
    for(int i = 0; i < n; i++) rank[sa[i]] = i;

    n--;
    int h = 0;  // 当前height值
    for(int i = 0; i < n; i++) {
        int j = sa[rank[i] - 1];
        if(h) h--;
        while(s[i + h] == s[j + h]) h++;
        height[rank[i]] = h;
    }
}

//int rd[maxn], real[maxn];
int ans[maxn], tot = 0;

int sa[maxn];
int main() {
    int n;
    cin >> n;
    tot = 0;
    
    for(int i = n - 1; i >= 0; i--) {
        scanf("%d", &s[i]);
    }
    
    s[n] = -inf;
    da(sa, n, n + 1);
    
    int ii;
    for(int i = 1; i <= n; i++) {
        if(sa[i] >= 2) {
            ii = sa[i];
            break;
        }
    }
    
    for(int i = ii; i < n; i++) {
        ans[++tot] = s[i];
    }
    
    for(int i = 0; i < ii; i++) {
        s[i + ii] = s[i];
    }
    int m = ii;
    n = 2 * m;
    s[n] = -inf;
    da(sa, n, n + 1);

    for(int i = 1; i <= n; i++) {
        if(sa[i] < m && sa[i] >= 1) {
            for(int j = sa[i]; j < sa[i] + m; j++) {
                ans[++tot] = s[j];
            }
            break;
        }
    }
    for(int i = 1; i <= tot; i++) {
        printf("%d\n", ans[i]);
    }
}


