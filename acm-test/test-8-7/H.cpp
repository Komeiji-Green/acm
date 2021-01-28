#include<iostream>
using namespace std;
typedef unsigned long long ll;

const int maxn = 100000 + 100;

ll a[maxn];
ll q[maxn];

struct Node {
    Node() {}
    Node(Node *_fa, int _val): fa(_fa), val(_val) {}
    Node *fa = nullptr;
    Node *ch[2] = {nullptr, nullptr};
    int val;
};

Node *nil = nullptr;
Node *root = nullptr;

int main()
{
    int T;
    cin >> T;
    int n, m;
    for(int test = 1; test <= T; test++) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            scanf("%ull", &a[i]);
        for(int i = 0; i < m; i++)
            scanf("%ull", &q[i]);

        // build
        root = new Node(nil, 0);
        for(int i = 0; i < n; i++) {
            Node *u = root;
            for(int j = 32, d; j >= 0; j--) {
                d = (1ll << j) & a[i] ? 1 : 0;
                if(u->ch[d] == nil) u->ch[d] = new Node(u, d);
                u = u->ch[d];
            }
        }

        printf("Case #%d:\n", test);
        // traversal
        for(int i = 0; i < m; i++) {
            Node *u = root;
            ll ans = 0;
            for(int j = 32, d; j >= 0; j--) {
                d = (1ll << j) & q[i] ? 1 : 0;
                if(u->ch[d ^ 1] != nil) { 
                    u = u->ch[d ^ 1];
                    ans += ((1ll << j) * (d ^ 1));
                } else if (u->ch[d] != nil) {
                    u = u->ch[d];
                    ans += ((1ll << j) * d);
                }
            }
            cout << ans << endl;
        }
    }
}