#include<bits/stdc++.h>
using namespace std;

const int maxn = 2300000;
const int inf = 0x3f3f3f3f;

bool cmp(int *r, int a, int b, int l) {
    return r[a] == r[b] && r[a + l] == r[b + l];
}

int c[maxn], ix[maxn], iy[maxn], s[maxn];

bool cp(int x, int y) {
    return s[x] < s[y];
}

/*
���桰��׺��Ĭ��Ϊ��׺������ĸ�±�
sa: ����->��׺
x: ��׺->ȥ������(��Ҫ����cmp��������)
y: key_2����->��׺
c: key_1ȥ������i->������0��i�ĺ�׺������
*/
// ���ֵ��ϴ������sa������������ɢ��
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
        if(p >= n) break; // ��֦
        m = p; // �´λ�������
    }
    
    for(int i = 0; i < n; i++) rank[sa[i]] = i;

    n--;
    int h = 0;  // ��ǰheightֵ
    for(int i = 0; i < n; i++) {
        int j = sa[rank[i] - 1];
        if(h) h--;
        while(s[i + h] == s[j + h]) h++;
        height[rank[i]] = h;
    }
}

char str[maxn];
int sa[maxn], rk[maxn], h[maxn];
int main() {
	int T;
	cin >> T;
	while(T--) {
		int n, k; scanf("%d%d", &n, &k);
		scanf("%s", str);
		for(int i=0;i<n;++i) s[i]=1-(str[i]-'0');
		s[n] = -1;
		da(sa, rk, h, n, n + 1);
		bool f = 1;
		for(int i = sa[0]; i < sa[0] + k && i < n; ++i) {
			if(s[i]) break;
		}
		if(i == sa[0] + k) {
			printf("YES\n");
			for(int i = 0; i < k; ++i) printf("0");
			printf("\n");
		} else {
			int i = 1;
		}
	}
}





