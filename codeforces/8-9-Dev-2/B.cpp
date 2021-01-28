#include<iostream>
#include<string>
using namespace std;

string s[105];
int main()
{
    int T;
    cin >> T;
    while(T--) {
        int m, n;
        cin >> m >> n;
        for(int i = 0; i < m; i++) {
            cin >> s[i];
        }

        int cnt = 0;
        for(int i = 0; i < m - 1; i++) {
            if(s[i][n - 1] == 'R') cnt++;
        }
        for(int j = 0; j < n - 1; j++) {
            if(s[m - 1][j] == 'D') cnt++;
        }
        cout << cnt << endl;
    }
}