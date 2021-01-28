#include <bits/stdc++.h>
using namespace std;

/*
5
2
01
10
5
01011
11100
2
01
01
10
0110011011
1000110100
1
0
1


3 1 2 1
6 5 2 5 3 1 2
0
9 4 1 2 10 4 1 2 1 5
1 1

*/

void op(string& s, int m)
{
    for(int i = 0; i < m; i++)
    {
        if(s[i] == '1') s[i] = '0';
        else s[i] = '1';
    }
    string temp(s.begin(), s.begin() + m);
    for(int i = 0; i < m; i++)
    {
        s[i] = temp[m - i - 1];
    }
}

int main()
{
    int T;
    cin >> T;

    string a;
    string b;

    int ans[200000 + 5];

    while (T--)
    {
        int n;
        cin >> n;
        cin >> a >> b;

        int cnt = 0;

        int j = n;
        while(j--)
        {
            if(a[j] == b[j]) continue;
            if(a[0] == b[j])
            {
                ans[cnt++] = 1;
                ans[cnt++] = j + 1;
                op(a, 1);
                op(a, j + 1);
                
            }
            else
            {
                ans[cnt++] = j + 1;
                op(a, j + 1);
            }
        }

        printf("%d", cnt);
        for(int i = 0; i < cnt; i++)
        {
            printf(" %d", ans[i]);
        }
        cout << endl;
    }
}