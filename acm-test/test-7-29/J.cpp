#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 5;
int a[maxn];
ll sum[maxn];

int N;
ll M;

bool check(ll ans)
{
    int idx = lower_bound(a, a + N, ans) - a;
    ll cnt = N - idx;  // 共砍n棵树
    ll get = 0;
    if(idx) get = sum[N - 1] - sum[idx - 1];
    else get = sum[N - 1] - 0;
    get -= cnt * ans;

    if(get >= M) return true;
    else return false; 
}
int main()
{
    cin >> N >> M;

    for(int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    
    sort(a, a + N);

    sum[0] = a[0];
    for(int i = 1; i < N; i++)
    {
        sum[i] = sum[i - 1] + a[i];
    }

    ll le = 0;
    ll ri = a[N - 1];
    ll mid = (le + ri + 1) >> 1;
    while(le < ri)
    {
        if(check(mid)) {
            le = mid;
        } else {
            ri = mid - 1;
        }
        mid = (le + ri + 1) >> 1;
    }

    cout << mid << endl;
}