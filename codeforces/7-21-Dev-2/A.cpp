#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 5;
bool a[maxn];
bool b[maxn];

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n, m;
        cin >> n >> m;
        int idx;

        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));

        for(int i = 0; i < n; i++)
        {
            scanf("%d", &idx);
            a[idx] = true;
        }
        for(int i = 0; i < m; i++)
        {
            scanf("%d", &idx);
            b[idx] = true;
        }
        bool ok = false;
        for(int i = 1; i <= 1000; i++)
        {
            if(a[i] && b[i])
            {
                ok = true;
                cout << "YES" << endl;
                cout << "1 " << i << endl;
                break;
            }
        }
        if(ok == false)
        {
            cout << "NO" << endl;
        }

    }
}