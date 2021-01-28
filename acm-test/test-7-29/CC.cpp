#include<iostream>
#include<iomanip>
using namespace std;
typedef long long ll;

const int maxn = 500000 + 5;
int a[maxn];
ll sum[maxn];
const double EPS = 1e-7;

int check(int mid, int mmid, ll max) {
    ll cmp = (sum[mid] + max) / (ll)(mid + 1) - (sum[mmid] + max) / (ll)(mmid + 1);
    if(cmp > 0) return 1;
    else if(cmp < 0) return -1;
    ll r1 = (sum[mid] + max) % (ll)(mid + 1);
    ll r2 = (sum[mmid] + max) % (ll)(mmid + 1);
    double diff = (double)(r1) / (mid + 1) - (double)(r2) / (mmid + 1);
    if(diff > EPS) return 1;
    else if(diff < EPS) return -1;
    else return 0;
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
        int ri = n;
        int mid = (le + ri + 1) >> 1;
        int mmid = (le + mid) >> 1;
        int c;
        bool ok = false;
        while(le < ri) {
            if((c = check(mid, mmid, max)) == 1) {
                ri = mid - 1;
            } else if(c == -1){
                le = mmid + 1;
            } else 
                ok = true;
            mid = (le + ri + 1) >> 1;
            mmid = (le + mid) >> 1;
            if(ok) break;
        }

        double ans = max - (sum[mid] + max) / (ll)(mid + 1) - (double)((sum[mid] + max) % (ll)(mid + 1)) / (mid + 1);
        cout << fixed << setprecision(10) << ans << endl;
    }
}