#include<iostream>
#include<queue>
using namespace std;
int L, M, N;
const int maxn = 50000 + 5;
int d[maxn];

bool check(int ans)
{
    int cnt = 0;
    int left = 0;   // 位置在left以及left以左的石头无需再搬走
    for(int i = 0; i < N; i++)
    {
        if((d[i] - left) < ans) {
            cnt++;
        } else {
            left = d[i];
        }
    }
    if(L - left < ans) cnt++;
    
    if(cnt > M) return false;
    else return true;
}
int main()
{
    cin >> L >> N >> M;
    for(int i = 0; i < N; i++)
    {
        scanf("%d", &d[i]);
    }
    d[N] = L;

    int le = 1;
    int ri = L;
    int mid = (le + ri) >> 1;
    while(le < ri)
    {
        if(check(mid))
            le = mid;
        else
            ri = mid - 1;
        
        mid = (le + ri + 1) >> 1;
    }
    cout << mid;
}