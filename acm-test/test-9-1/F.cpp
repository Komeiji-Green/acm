#include<iostream>
#include <algorithm>
using namespace std;

int a[100];
int main()
{
    int n;
    cin >> n;
    int m = n / 2;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int cnt = 1, minv = a[1];
    for(int j = 2; j <= n; j++) {
        if(a[j] == minv) {
            cnt++;
        } else break;
    }
    int nn = n - cnt;
    if(nn >= 0 && nn < m) {
        printf("Bob\n");
    } else {
        printf("Alice\n");
    }
}