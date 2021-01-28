#include<iostream>
#include<string>
using namespace std;
int main()
{
    int T;
    cin >> T;
    while(T--)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;
        int idx = s.find_first_of('8');
        if(idx != - 1 && n - idx >= 11)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}