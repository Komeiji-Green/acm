#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<pair<char, int>> q;
stack<pair<char, int>> temp;

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        while (!q.empty())
            q.pop();
        while (!temp.empty())
            temp.pop();
        string s;
        cin >> s;
        int cnt = 0; // 记录'('的数量
        bool ok = true;
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (c == '(')
            {
                cnt++;
                q.push(pair<char, int>(c, i));
            }
            else if (c == ')')
            {
                if (cnt)
                { // 有'('
                    while (q.top().first == '*')
                        q.pop();
                    q.pop();
                    cnt--;
                }
                else
                { // 前无'('
                    if (q.empty())
                    {
                        ok = false;
                        break;
                    }
                    else
                    {
                        s[q.top().second] = '('; // 改‘*’
                        q.pop();
                    }
                }
            }
            else
            {
                q.push(pair<char, int>(c, i));
            }
        }
        if (ok)
        {
            while (!q.empty())
            {
                if (q.top().first == '(')
                {
                    if (temp.empty())
                    {
                        ok = false;
                        break;
                    }
                    else
                    {
                        s[temp.top().second] = ')';
                        q.pop();
                    }
                }
                else
                {
                    temp.push(q.top());
                    q.pop();
                }
            }
        }

        if (!ok)
            cout << "No solution!";
        else
            for (int i = 0; i < s.size(); i++)
            {
                if (s[i] != '*')
                    putchar(s[i]);
            }
        cout << endl;
    }
}
