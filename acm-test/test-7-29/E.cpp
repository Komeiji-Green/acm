#include<iostream>
#include<algorithm>
using namespace std;
const int maxn = 50000 + 5;
typedef long long ll;

int A[maxn];
int B[maxn];

int N, K;

bool check(ll ans) {
    int cnt = 0;
    for(int i = 0; i < N; i++) {
        ll key = ans / A[i];
        int idx = upper_bound(B, B + N, key) - B;
        cnt += N - idx;
        if(cnt >= K) return false;
    }
    return true;
}

int main()
{
    cin >> N >> K;
    for(int i = 0; i < N; i++)
    {
        scanf("%d %d", &A[i], &B[i]);
    }
    sort(A, A + N);
    sort(B, B + N);

    ll le = (ll)A[0] * (ll)B[0];
    ll ri = (ll)A[N - 1] * (ll)B[N - 1];
    
    ll mid = (le + ri) >> 1;
    while(le < ri) {
        if(check(mid)) {
            ri = mid;
        } else {
            le = mid + 1;
        }
        mid = (le + ri) >> 1;
    }
    cout << mid << endl;
}