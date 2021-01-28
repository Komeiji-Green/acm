#include<iostream>
#include<set>
#include<queue>
#include<unordered_map>
#include<stack>
#include<string>
#include<ctime>
using namespace std;
#define rep(i, a, b) for(int i = a; i < b; i++)

int read(char c)
{
    if(c >= '1' && c <= '9')
        return c - '0';
    else return 0;
}

inline int L(int i) { return (i % 3 == 0 ? -1 : i - 1); }
inline int R(int i) { return ((i + 1) % 3 == 0 ? -1 : i + 1); }
inline int U(int i) { return i - 3; }
inline int D(int i) { return i + 3; }

char dir[4] = { 'l', 'd', 'r', 'u' };

inline bool in(int i) { return i >= 0 && i < 9; }

int vecr[4] = { 0, -1, 0, 1 };
int vecc[4] = { 1, 0, -1, 0 };



int a[3][3];
int xr;
int xc;


string target = "12345678x";

set<string> vis;
unordered_map<string, pair<string, char> > f;

void bfs()
{
    queue<string> q;

    q.push(target);
    vis.insert(target);
    while(!q.empty()) {
        string cur = q.front(); q.pop();
        int ix = cur.find('x');
        int next[4] = {R(ix), U(ix), L(ix), D(ix)};
        for(int i = 0; i < 4; i++) {
            if(!in(next[i])) continue;

            string nex(cur);
            char temp = nex[ix];
            nex[ix] = nex[next[i]];
            nex[next[i]] = temp;

            if(!vis.insert(nex).second) continue;
            q.push(nex);
            f[nex] = make_pair(cur, dir[i]);
        }
    }
}

int check(string s)
{
    int cnt = 0;
    for(int i = 1; i < s.size(); i++) {
        for(int j = 0; j < i; j++)
            if(s[j] != 'x' && s[i] != 'x' && s[j] > s[i]) cnt++;
    }
    return cnt % 2 == 0;
}

int main()
{
    string input;
    bfs();
    
    while(cin >> input) {
        string s;
        s += input;
        getline(cin, input);
        for(int i = 0; i < input.size(); i++) {
            if(input[i] != ' ')
                s += input[i];
        }
        //clock_t start, end;
        //start = clock();
        if(vis.find(s) == vis.end())
            cout << "unsolvable" << endl;
        else {
            string ans;
            string node = s;
            while(f.find(node) != f.end()) {
                ans += f[node].second;
                node = f[node].first;
            }
            cout << ans << endl;
        }
        //end = clock();
        //cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    }
}