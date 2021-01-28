#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 5;
bool isnt[maxn];
int prime[maxn];
int cnt = 0;

int ans0[maxn];
int ans1[maxn];
int ret[maxn];

// 线性筛法 [1, n] 内素数
void Prime(int n)
{
    isnt[1] = true;
    cnt = 0;
    for (int i = 2; i <= n; i++)
    {
        if (!isnt[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++)
        {
            if (i * prime[j] > n)
                break;
            isnt[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
}

bool isPrime(int n)
{
    for (int i = 1; i <= cnt && prime[i] < n; i++)
    {
        if (n % prime[i] == 0)
            return false;
    }
    return true;
}

int rev(int k)
{
    int ans = 0;
    while (k)
    {
        ans = ans * 10 + (k % 10);
        k /= 10;
    }
    return ans;
}

int gen0(int n)
{
    int bits = 0;
    int tail = 0;
    int k = n;
    while (k)
    {
        bits++;
        k /= 10;
    }

    int d = 1;
    for (int i = 0; i < bits; i++)
        d *= 10;
    return n * d + rev(n);
}

int gen1(int n)
{
    int bits = 0;
    int tail = 0;
    int k = n;
    while (k)
    {
        bits++;
        k /= 10;
    }
    int d = 1;
    for (int i = 0; i < bits - 1; i++)
        d *= 10;
    return n * d + rev(n / 10);
}

int main()
{
    cnt = 0;
    Prime(10000);

    int ans;
    int p0 = 0;
    int p1 = 0;
    for (int i = 1; i <= 10000; i++)
    {
        ans = gen0(i);
        if (ans >= 5 && ans <= 100000000 && isPrime(ans))
            ans0[p0++] = ans;
        ans = gen1(i);
        if (ans >= 5 && ans <= 100000000 && isPrime(ans))
            ans1[p1++] = ans;
    }

    int i = 0;
    int j = 0;
    int pp = 0;
    while (i <= p0 && j <= p1)
    {
        if (i != p0 && j != p1 && ans0[i] < ans1[j] || (j == p1 && i != p0))
        {
            ret[pp++] = ans0[i];
            i++;
        }
        else if (j != p1 && i != p0 && ans0[i] > ans1[j] || (j != p1 && i == p0))
        {
            ret[pp++] = ans1[j];
            j++;
        }
        else
            break;
    }

    int a, b;
    while (scanf("%d", &a) != EOF)
    {
        cin >> b;
        int idx1 = lower_bound(ret, ret + pp, a) - ret;
        int idx2 = upper_bound(ret, ret + pp, b) - ret;
        for(int it = idx1; it < idx2; it++) {
            printf("%d\n", ret[it]);
        }
        cout << endl;
    }
}