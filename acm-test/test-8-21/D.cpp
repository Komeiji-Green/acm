#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

#define rep(i, a, b) for(int i = (a); i <= (b); i++)

using namespace std;

const double eps = 1e-9;
const double inf = 1e20;
const double pi = acos(-1.0);
//`Compares a double to zero`
int sgn(double x){
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
//square of a double
inline double sqr(double x){return x*x;}

const int N = 100500;

int fly[N];
double dp[N];

int main()
{
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF && n != 0) {
        int x, y;
        memset(fly, 0, sizeof(fly));
        rep(i, 1, m) {
            scanf("%d %d", &x, &y);
            fly[x] = y;
        }
        for(int i = 0; i <= 10; i++) dp[n + i] = 0.0;
        for(int i = n - 1; i >= 0; i--) {
            if(fly[i]) {
                dp[i] = dp[fly[i]];
            } else {
                double sum = 0.0;
                for(int j = 1; j <= 6; j++) {
                    sum += dp[i + j];
                }
                dp[i] = 1 + sum / 6.0;
            }
        }
        printf("%.4f\n", dp[0]);
    }
}