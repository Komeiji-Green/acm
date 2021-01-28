#include<iostream>
#include<string>
#include<stack>
#include<deque>
using namespace std;


int main()
{
    int T;
    cin >> T;
    while(T--) {
        string s;
        deque<int> dq;
        cin >> s;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '*')
                dq.push_back(i);
        }
        int lcnt = 0;
        int rcnt = 0;
        bool ok = true;
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(') {
                lcnt++;
            } else if(s[i] == ')') {
                rcnt++;
                if(rcnt <= lcnt) continue;
                if(!dq.empty() && dq.front() < i) {
                    s[dq.front()] = '(';
                    dq.pop_front();
                    lcnt++;
                } else {
                    ok = false;
                    break;
                }
            }
        }

        lcnt = rcnt = 0;
        for(int i = s.size() - 1; i >= 0; i--) {
            if(s[i] == ')') {
                rcnt++;
            } else if(s[i] == '(') {
                lcnt++;
                if(lcnt <= rcnt) continue;
                if(!dq.empty() && dq.back() > i) {
                    s[dq.back()] = ')';
                    dq.pop_back();
                    rcnt++;
                } else {
                    ok = false;
                    break;
                }
            }
        }

        if(!ok)
            cout << "No solution!";
        else for(int i = 0; i < s.size(); i++) {
            if(s[i] != '*')
                putchar(s[i]);
        }
        cout << endl;
    }
}