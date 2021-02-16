#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

//HDU 1402 求高精度乘法
const double PI = acos(-1.0);
//复数结构体
struct Complex {
    double x, y; //实部和虚部 x+yi
    Complex(double _x = 0.0, double _y = 0.0) {
        x = _x;
        y = _y;
    }
    Complex operator-(const Complex &b) const {
        return Complex(x-b.x, y-b.y);
    }
    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator*(const Complex &b) const {
        return Complex(x * b.x-y * b.y, x * b.y + y * b.x);
    }
};
/*
 * 进行 FFT 和 IFFT 前的反转变换。
 * 位置 i 和（i 二进制反转后位置）互换
 * len 必须为 2 的幂
 */
void change(Complex y[], int len) {
    int i, j, k;
    for (i = 1, j = len / 2; i < len-1; i++) {
        if (i < j) swap(y[i], y[j]);
        //交换互为小标反转的元素，i<j 保证交换一次
        //i 做正常的 +1，j 做反转类型的 +1, 始终保持 i 和 j 是反转的
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
/*
 * 做 FFT
 * len 必须为2^k形式
 * on==1 时是 DFT，on==-1 时是 IDFT
 */
void fft(Complex y[], int len, int on) {
    change(y, len);
    for (int h = 2; h <= len; h <<= 1) {
        Complex wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
        for (int j = 0; j < len; j += h) {
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k++) {
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u-t;
                w = w * wn;
            }
        }
    }
    if (on == -1)
        for (int i = 0; i < len; i++)
            y[i].x /= len;
}

const int maxn = 200010;
Complex x1[maxn], x2[maxn];

const int maxn = 633333;
int le[maxn], ri[maxn];
struct P {
    int x; // 行
    double p; // 值
};
vector<P> a[maxn], b[maxn]; // 各列的p值与b值
int main() {
    int T, n, m;
    cin >> T;
    while(T--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; ++i) a[i].clear(), b[i].clear();
        for(int i = 1, l, r; i <= n; ++i) {
            scanf("%d %d", &l, &r);
            int sz = r - l + 1;
            int c = l;   // 列数
            ll tmp;
            for(int c = l; c <= r; ++c) {
                scanf("%lld", &tmp);
                a[c].push_back(P{i, tmp * 1e-9});
            }
        }
        for(int r = 1, c; r <= m; ++r) {
            scanf("%d", &c);
            b[c].push_back(P{r, 1.0});
        }
        
    }
}