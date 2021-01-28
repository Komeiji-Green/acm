#include<iostream>
using namespace std;
typedef long long ll;

const int maxn = 500000 + 5;
int a[maxn];
ll sum[maxn];

int check(int mid, int mmid, ll max) {
    return (sum[mid] + max) * (ll)(mmid + 1) > (sum[mmid] + max) * (ll)(mid + 1);
}

int main()
{
    int T;
    cin >> T;
    int op;
    int x = 0;
    int n = 0;
    sum[0] = 0;
    while(T--) 
    {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &x);
            a[n++] = x; // sorted
            sum[n] += sum[n - 1] + x;
            continue;
        }
        ll max = x;
        int le = 1;
        int ri = n - 1;
        int mid = (le + ri + 1) >> 1;
        int mmid = (le + mid) >> 1;
        while(le < ri) {
            if(check(mid, mmid, max)) {
                ri = mid - 1;
            } else {
                le = mmid + 1;
            }
            mid = (le + ri + 1) >> 1;
            mmid = (le + mid) >> 1;
        }

        double ans = (double)max - (double)(sum[mid] + max) / (mid + 1);
        cout << ans << endl;
    }
}