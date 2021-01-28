#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

string s[1000000 + 5];
int cnt[5];
int main()
{
    int m, n;
    cin >> m >> n;
    for(int i = 0; i < m; i++)
        cin >> s[i];
    if(m >= 4 && n >= 4) {
        cout << -1 << endl;
        return 0;
    } 
    if(m == 1 || n == 1) {
        cout << 0 << endl;
    } else if(m == 2) {
        for(int i = 0; i < n; i++) {
            cnt[(i % 2) ^ (s[0][i] == '1') ^ (s[1][i] == '1')]++;
        }
        cout << (n - max(cnt[0], cnt[1])) << endl;
    } else if(n == 2) {
        for(int i = 0; i < m; i++) {
            cnt[(i % 2) ^ (s[i][0] == '1') ^ (s[i][1] == '1')]++;
        }
        cout << (m - max(cnt[0], cnt[1])) << endl;
    } else if(m == 3) {
        for(int i = 0; i < n; i++) {
            cnt[(((i % 2) ^ (s[0][i] == '1') ^ (s[1][i] == '1')) << 1)
                | ((i % 2) ^ (s[1][i] == '1') ^ (s[2][i] == '1'))]++;
        }
        int ans = 0;
        for(int i = 0; i < 4; i++) {
            if(cnt[i] > ans) ans = cnt[i];
        }
        cout << n - ans << endl;
    } else if(n == 3) {
        for(int i = 0; i < m; i++) {
            cnt[(((i % 2) ^ (s[i][0] == '1') ^ (s[i][1] == '1')) << 1)
                | ((i % 2) ^ (s[i][1] == '1') ^ (s[i][2] == '1'))]++;
        }
        int ans = 0;
        for(int i = 0; i < 4; i++) {
            if(cnt[i] > ans) ans = cnt[i];
        }
        cout << m - ans << endl;
    }
}