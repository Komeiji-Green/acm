#include<bits/stdc++.h>
#include<vector>
#include<string>
#include<map>
#include<iostream>
using namespace std;
typedef long long ll;
map<string, int> mp;

const int maxn = 100005;
vector<string> sub, uni;
int main() {
    string s;
    cin >> s;
    for(int len = 1; len <= s.size(); ++len) {
        for(int i = 0; i < s.size(); ++i) {
            if(i + len <= s.size()) {
                sub.push_back(s.substr(i, len));
                uni.push_back(s.substr(i, len));
            }
        }
    }
    sort(sub.begin(), sub.end());
    sort(uni.begin(), uni.end());
    uni.erase(unique(uni.begin(), uni.end()), uni.end());
    int t, k;
    cin >> t >> k;
    --k;
    if(t == 0) {
        if(k >= uni.size()) printf("-1\n");
        else cout << uni[k] << endl;
    } else {
        if(k >= sub.size()) printf("-1\n");
        else cout << sub[k] << endl;
    }
}