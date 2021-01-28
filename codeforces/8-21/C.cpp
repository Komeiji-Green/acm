#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

const int N = 233333;
const int INF = 0x3f3f3f3f;
int a[N];
int b[N];
int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;

        int m = INF;
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            m = min(m, a[i]);
        }

        int num = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] % m == 0) {
                b[num++] = a[i];
                a[i] = 0;
            }
        }

        sort(b, b + num);
        for(int i = 0, j = 0; i < n; i++) {
            if(!a[i]) {
                a[i] = b[j++];
            }
        }

        bool flag = true;
        for(int i = 1; i < n; i++) {
            if(a[i - 1] > a[i]) {
                flag = false;
                break;
            }
        }
        printf(flag ? "YES\n" : "NO\n");
    }
};
