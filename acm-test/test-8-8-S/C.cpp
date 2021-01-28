#include<iostream>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;

struct Node {
    Node() {}
    Node(Node *_fa, int _id): fa(_fa), id(_id) {
    }
    Node *fa = nullptr;
    Node *ch[2] = {nullptr, nullptr};
    int id;
};


Node *nil = nullptr;
Node *root = nullptr;

const int maxn = 2000;

char ans[maxn];
int tot = 0;


Node * bst_insert(Node *node, int id) {
    int d = id <= node->id;
    if(node->ch[d] == nil)
        return node->ch[d] = new Node(node, id);
    else
        return bst_insert(node->ch[d], id);
}

Node *bst_find(Node *node, int id) {
    if(node == nil) return nil;
    if(id < node->id) {
        ans[tot++] = 'E';
        return bst_find(node->ch[1], id);
    } else if (id == node->id) {
        return node;
    } else {
        ans[tot++] = 'W';
        return bst_find(node->ch[0], id);
    }
}



int main()
{
    tot = 0;

    root = nil;

    int n, q;
    int T;
    cin >> T;
    while(T--) {
        cin >> n;
        int x;
        for(int i = 0; i < n; i++) {
            scanf("%d", &x);
            if(i == 0)
                root = new Node(nil, x);
            else
                bst_insert(root, x);
        }
        cin >> q;
        for(int i = 0; i < q; i++) {
            tot = 0;
            scanf("%d", &x);
            bst_find(root, x);
            ans[tot] = '\0';
            printf("%s\n", ans);
        }
    }
}