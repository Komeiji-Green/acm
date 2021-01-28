#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int maxn = 500051;
const int inf = 0x3f3f3f3f;

bool cmp(int *r, int a, int b, int l){
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
void da(int sa[], int rk[], int height[], int n, int m) {
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

int sa[maxn], h[maxn], rk[maxn], tot = 0;
char tmp[maxn];

int n;

int pos[maxn], cnt[105];
/*void insert(int x, int op) {
    int idx = lower_bound(pos + 1, pos + n + 1, x) - pos;
    if(pos[idx] == x) return sum;
    if(op == 1) {
        if(cnt[x]) cnt[x]++;
        else {
            sum++; cnt[x]++;
        }
    } else {
        if(cnt[x] > 0) cnt[x]--;
        if(cnt[x] == 0) sum--; 
    }
}*/

int ans[maxn], ansnum = 0;

bool check(int L) {
    int i = n + 1;
    bool flag = false;
    ansnum = 0;
    while(i <= tot) {
        int j, minh = inf;
        for(j = i; j <= tot && h[j] >= L; j++) {
            minh = min(minh, h[j]);
        }
        j--;
        if(j < i) { i++; continue; }
        memset(cnt, 0, sizeof(cnt));
        for(int k = i - 1; k <= j; k++) {
            cnt[pos[sa[k]]] = 1;
        }
        int sum = 0;
        for(int k = 1; k <= n; k++) {
            sum += cnt[k];
        }
        if(sum > (n / 2)) {
            flag = true;
            ans[++ansnum] = sa[j];
        }
        i = j + 1;
    }
    return flag;
}

char out[maxn];
int main() {
    int cas = 0;
    while(scanf("%d", &n) != EOF && n) {
        if(cas > 0) printf("\n");
        cas++;
        tot = 0;
        if(n == 1) {
            scanf("%s", tmp);
            printf("%s\n", tmp);
            continue;
        }
        for(int i = 1; i <= n; i++) {
            scanf("%s", tmp);
            for(int j = 0; tmp[j]; j++) {
                s[tot++] = tmp[j] - 'a' + n;
            }
            s[tot++] = n - i;
        }
        tot--;
        da(sa, rk, h, tot, tot + 1);

        int idx = 1;
        for(int i = 0; i <= tot; i++) {
            if(s[i] < n) {
                idx++;
                pos[i] = 0;
            } else pos[i] = idx;
        }

        int le = 0, ri = 1000;
        int mid = (le + ri + 1) >> 1;
        while(le < ri) {
            if(check(mid)) {
                le = mid;
            } else {
                ri = mid - 1;
            }
            mid = (le + ri + 1) >> 1;
        }

        if(mid == 0) {
            printf("?\n");
        } else {
            check(mid);
            for(int i = 1; i <= ansnum; i++) {
                int pos = ans[i];
                for(int j = 0; j < mid; j++) {
                    out[j] = (char)(s[j + pos] - n + 'a');
                }
                out[mid] = '\0';
                printf("%s\n", out);
            }
        }
    }
}