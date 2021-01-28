#include <bits/stdc++.h>
using namespace std;

string first = "First";
string second = "Second";

int a[100000 + 5];

int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;

        memset(a, 0, sizeof(int) * n);
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        int key = 0;
        for(int i = 0; i < n; i++)
        {
            if(a[i] != 1) break;
            key++;
        }

        if(key == n)
        {
            if(key % 2 == 0)
                cout << second << endl;
            else
                cout << first << endl;
        }
        else
        {
            if(key % 2 == 0)
                cout << first << endl;
            else
                cout << second << endl;
        }
        
    }
}