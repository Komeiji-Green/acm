#include<iostream>
using namespace std;
const int maxn = 200000 + 5;
int a[maxn];
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int ans = n - 1;
    int door = a[ans];
    while(ans--)
    {
        if(a[ans] != door) 
            break;
    }
    cout << ans + 1;
}