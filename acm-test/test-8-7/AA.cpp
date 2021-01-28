#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 500500;

int f[maxn];  // fail数组，f[i] = [0, i)子串中，最长前缀=后缀的长度（不允许前缀后缀重合）
string s;
string t;
string ans;

// 记录模式串fail数组：动态规划
void getNext(string &t) {
    f[0] = 0; f[1] = 0;
    for(int i = 1, j = 0; i < t.size(); i++) { 
        while(j && t[i] != t[j]) j = f[j];
        if(t[i] == t[j]) j++;  
        f[i + 1] = j;
    }
}

int main()
{
    cin >> s;
    cin >> t;

    int cnts[2] = {};
    int cntt[2] = {};
    int cnttail[2] = {};
    for(int i = 0; i < s.size(); i++) {
        cnts[s[i] - '0']++;
    }
    for(int i = 0; i < t.size(); i++) {
        cntt[t[i] - '0']++;
    }

    int lent = t.size();
    int lens = s.size();

    getNext(t);
    for(int i = f[lent]; i < lent; i++) {
        cnttail[t[i] - '0']++;
    }

    int step = lent - f[lent];

    int cnt1 = 0;
    int cnt0 = 0;
    for(int i = lent; i <= lens; i += step) {
        if(cntt[0] > cnts[0] || cntt[1] > cnts[1])
            break;
        if(i == lent) { 
            cnt0 += cntt[0]; cnt1 += cntt[1];
            ans += t;
        }
        if(cnt0 + cnttail[0] <= cnts[0] && cnt1 + cnttail[1] <= cnts[1]) {
            cnt0 += cnttail[0]; cnt1 += cnttail[1];
            ans += t.substr(f[lent]);
        }
    }
    for(int i = 0; i < cnts[0] - cnt0; i++) {
        ans += "0";
    }
    for(int i = 0; i < cnts[1] - cnt1; i++) {
        ans += "1";
    }
    cout << ans << endl;
}