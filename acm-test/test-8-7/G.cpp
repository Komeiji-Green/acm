#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

struct Node {
    Node(): sum(0) {}
    Node *ch[10] = {};
    int sum = 0;
};

Node *nil = nullptr;
Node *root = nullptr;

string q[5005];
string dic[5005];

int hs[] = { 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9 };

/*
2 : a, b, c    3 : d, e, f    4 : g, h, i    5 : j, k, l    6 : m, n, o    
　　7 : p, q, r, s  8 : t, u, v    9 : w, x, y, z
*/

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n, m;
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> q[i];
        for(int i = 0; i < m; i++)
            cin >> dic[i];

        root = new Node();
        for(int i = 0; i < m; i++) {
            Node *u = root;
            for(int j = 0; j < dic[i].size(); j++) {
                int d = hs[dic[i][j] - 'a'];
                if(u->ch[d] == nil) u->ch[d] = new Node();
                u->ch[d]->sum++;
                u = u->ch[d];
            }
        }

        for(int i = 0; i < n; i++) {
            Node *u = root;
            int ans = 0;
            for(int j = 0; j < q[i].size(); j++) {
                int d = q[i][j] - '0';
                if(u->ch[d] == nil) { ans = 0; break; }
                ans = u->ch[d]->sum;
                u = u->ch[d];
            }
            cout << ans << endl;
        }
    }
}