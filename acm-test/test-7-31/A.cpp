#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

// 线性筛法 [1, n] 内素数
void Prime(int n)
{
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++) {
        if (!isnt[i]) prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n) break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}



int main()
{
    const int N = 10000;
    Prime(10000);

    int n;
    while(cin >> n) {
        int idx = lower_bound(prime + 1, prime + cnt + 1, n / 2) - prime;
        for(int i = idx; i <= cnt; i++) {
            if(binary_search(prime + 1, prime + cnt + 1, n - prime[i])) {
                printf("%d %d\n", n - prime[i], prime[i]);
                break;
            }
        }
    }
}