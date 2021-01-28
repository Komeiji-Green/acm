#include<bits/stdc++.h>
using namespace std;
const int maxn = 233333;
int la[16] = {
	1, 0, 0, 1,
	0, 0, 1, 0,
	0, 1, 0, 0,
	1, 0, 0, 1
};
int lb[16] = {
	0,0,0,0,
	1,0,0,1,
	0,0,0,0,
	0,1,0,0
}; 
int lc[16]={
	0,0,0,0,
	0,0,0,0,
	1,0,0,1,
	0,0,1,0
};
int ld[16]={
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	1,0,0,1
};
struct Mat {
	int a[4][4];
	Mat() {}
	Mat(int *arr) {
		int t = 0;
		n = m = 4;
		for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) a[i][j] = arr[t++]; 
	}
	int n, m;
	Mat mul(const Mat &rhs) {
        Mat ans;
        ans.m = m;
        ans.n = rhs.n;
        int res = 0;
        for(int i = 0; i < m; i++)
            for(int j = 0; j < rhs.n; j++) {
                res = 0;
                for(int k = 0; k < n; k++) res = res || (a[i][k] && rhs.a[k][j]);
            	ans.a[i][j] = res;
            }
        return ans;
    }
};
struct Point {
	int r, c;
	bool operator<(const Point& b) {
		return c < b.c;
	}
} uu[maxn];
Mat Pow(Mat a, int k) {
    Mat ans;
    ans.m = ans.n = 4;
    for(int i = 0; i < 4; ++i) for(int j = 0; j < 4; ++j) ans.a[i][j] = 0;
    for(int i = 0; i < 4; ++i) ans.a[i][i] = 1;
    while(k) {
        if(k & 1) ans = ans.mul(a);
        k >>= 1; a = a.mul(a);
    }
    return ans;
}
Mat M[4], X;
int main() {
	Mat A(la), B(lb), C(lc), D(ld);
	M[0] = A, M[1] = B, M[2] = C, M[3] = D;
 	X.m=4, X.n=1; X.a[3][0]=1;
	Mat Y;
	int T, n, m;
	cin >> T;
	while(T--) {
		scanf("%d %d", &n, &m);
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", &uu[i].r, &uu[i].c);
		}
		sort(uu + 1, uu + m + 1);
		int tot = 1;
		for(int i = 2; i <= m; ++i) {
			if(uu[i].c == uu[tot].c) uu[tot].r += uu[i].r;
			else {
				++tot;
				uu[tot] = uu[i];
			}
		}
		Mat T = Pow(A, 0);
		int j = 1;
		for(int i = 1; i <= tot; ++i) {
			T = Pow(A, uu[i].c-j).mul(T);
			j = uu[i].c + 1;
			T = M[uu[i].r].mul(T);
		}
		T = Pow(A, n+1-j).mul(T);
		Y = T.mul(X);
		if(Y.a[3][0]) printf("YES\n");
		else printf("NO\n");
	}
}
