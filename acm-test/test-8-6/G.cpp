#include<iostream>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;

struct Node {
    Node() {}
    Node(Node *_fa, int _id, int _val): fa(_fa), id(_id), val(_val) {
        sum = 1; totalVal = _val; lazy = 0;
    }
    Node *fa = nullptr;
    Node *ch[2] = {nullptr, nullptr};
    int id;
    int val;
    ll totalVal;
    int sum;
    int lazy;
};


Node *nil = nullptr;
Node *root = nullptr;


// update
void maintain(Node *u) {
    u->sum = 1;
    u->totalVal = u->val;
    
    if(u->ch[0] != nullptr) {
        u->sum += u->ch[0]->sum;
        u->totalVal += u->ch[0]->totalVal;
    }
    
    if(u->ch[1] != nullptr) {
        u->sum += u->ch[1]->sum;
        u->totalVal += u->ch[1]->totalVal;       
    }
}


// 加懒标记，刷新节点值
void marking(Node *node, int lz) {
    node->lazy += lz;
    node->totalVal += 1ll * lz * node->sum;
    node->val += lz;
}


// 下放懒标记
void push_down(Node *node) {
    if(node->ch[0] != nil) {
        marking(node->ch[0], node->lazy);
    }
    if(node->ch[1] != nil) {
        marking(node->ch[1], node->lazy);
    }
    node->lazy = 0;
    maintain(node);
}


// 旋
void rotate(Node *u) {
    Node *f = u->fa, *ff = f->fa;
    push_down(f); push_down(u);
    int d = u == f->ch[1];
    if((f->ch[d] = u->ch[d ^ 1]) != nil)
        f->ch[d]->fa = f;
    if((u->fa = ff) != nil)
        ff->ch[f == ff->ch[1]] = u;
    f->fa = u;
    u->ch[d ^ 1] = f;
    maintain(f); maintain(u);
}

// 从node旋到target
void splay(Node *node, Node *target) {
    for(Node *f; (f = node->fa) != target; rotate(node)) {
        if((f->fa) != target) {
            (f->fa->ch[1] == f) ^ (f->ch[1] == node) ? rotate(node) : rotate(f);
        }
    }
    if(target == nil)
        root = node;
}

// BST插入
Node * bst_insert(Node *node, int id, int val) {
    push_down(node);
    int d = id >= node->id;
    if(node->ch[d] == nil)
        return node->ch[d] = new Node(node, id, val);
    else
        return bst_insert(node->ch[d], id, val);
}

// splay插入
void insert(int id, int val) {
    Node *node = bst_insert(root, id, val);
    splay(node, nil);
}

Node *bst_find(Node *node, int id) {
    if(node == nil) return nil;
    if(id < node->id) {
        return bst_find(node->ch[0], id);
    } else if (id == node->id) {
        return node;
    } else 
        return bst_find(node->ch[1], id);
}


// 数值前驱（小于等于，最大）
Node* lower_bound(Node *node, int id) {
    if(node == nil) return nil;
    else if(id < node->id) {
        return lower_bound(node->ch[0], id);
    } else {
        //if(id == node->id) return node;
        Node * res = lower_bound(node->ch[1], id);
        if(res == nil) return node;
        else return res;
    }
}

/*Node *LBD(Node *node, int id) {
    Node *l = node->ch[0];
    Node *r = node->ch[1];
    Node *ans = nil;
    while(1) {
        if(node->id < id) {
            if(r == nil) break;
            node = r;
        } else { // node->id >= id
            if(node->id == id) ans = node;
            if(l == nil) break;
            node = l;
        }
        l = node->ch[0];
        r = node->ch[1];
    }
    return ans;
}*/


Node *LBD(Node *node, int id) {
    Node *l = node->ch[0];
    Node *r = node->ch[1];
    Node *ans = nil;
    while(node != nil) {
        l = node->ch[0];
        r = node->ch[1];
        if(node->id < id) {
            node = r;
        } else {
            if(node->id == id) ans = node;
            node = l;
        }
    }
    return ans;
}

// 数值后继（大于等于，最小）
Node* upper_bound(Node *node, int id) {
    if(node == nil) return nil;
    else if(id > node->id) {
        return upper_bound(node->ch[1], id);
    } else {
        //if(id == node->id) return node;
        Node * res = upper_bound(node->ch[0], id);
        if(res == nil) return node;
        else return res;
    }
}

// 节点前驱
Node *pre(Node *u) {
    if(u->ch[0] != nil) {
        for(u = u->ch[0]; u->ch[1] != nil; u = u->ch[1]);
        return u;
    }
    Node *f = u->fa;
    while(f != nil && u == f->ch[0]) {
        u = f;
        f = f->fa;
    }
    return f;
}

// 节点后继
Node *nxt(Node *u) {
    if(u->ch[1] != nil) {
        for(u = u->ch[1]; u->ch[0] != nil; u = u->ch[0]);
        return u;
    }
    Node *f = u->fa;
    while(f != nil && u == f->ch[1]) {
        u = f;
        f = f->fa;
    }
    return f;
}


// 查找排名为rank的数
Node *find_rank(Node* node, int rank) {
    if(node == nil) return nil;
    Node *l = node->ch[0];
    Node *r = node->ch[1];
    int sum = (l == nil ? 0 : l->sum);
    while(1) {
        if(sum == rank) {
            splay(node, nil); 
            return node;
        }
        if(rank < sum) {
            if(l == nil) return nil;
            sum = (l->ch[1] == nil ? sum - 1 : sum - 1 - l->ch[1]->sum);
            node = l;
        } else {
            if(r == nil) return nil;
            sum = (r->ch[0] == nil ? sum + 1 : sum + 1 + r->ch[0]->sum);
            node = r;
        }
        l = node->ch[0];
        r = node->ch[1];
    }
    return node;
}
// 查询数对应最小排名
int query_rank(Node *node, int id) {
    Node* u = LBD(node, id);
    splay(u, nil);
    return u->ch[0] == nil ? 0 : u->ch[0]->sum;
}
// 区间修改
void add(int l, int r, int d) {
    Node * prev = lower_bound(root, l - 1);
    Node * next = upper_bound(root, r + 1);
    splay(prev, nil);
    splay(next, root);

    marking(next->ch[0], d);
}
// 删除区间
void erase(int l, int r) {
    Node * prev = lower_bound(root, l - 1);
    Node * next = upper_bound(root, r + 1);
    splay(prev, nil);
    splay(next, root);

    int sum = next->ch[0]->sum;
    ll totalVal = next->ch[0]->totalVal;
    delete next->ch[0];
    next->ch[0] = nil;
    prev->sum -= sum;
    prev->totalVal -= totalVal;
    next->sum -= sum;
    next->totalVal -= totalVal;
}

// 删除单点
void erase(int id) {
    Node * u = bst_find(root, id);
    if(u == nil) return;
    splay(u, nil);
    // 默认有哨兵
    if(u->ch[0] != nil && u->ch[1] != nil) {
        Node * prev = pre(u);
        splay(prev, nil);
        Node * f = u->fa;
        int d = f->ch[1] == u;
        push_down(u);
        if((f->ch[d] = u->ch[1]) != nil) f->ch[d]->fa = f;
        maintain(f);
        delete u;
    }
}

// 区间查询
ll query(int l, int r)
{
    Node * prev = lower_bound(root, l - 1);
    Node * next = upper_bound(root, r + 1);
    splay(prev, nil);
    splay(next, root);

    return next->ch[0]->totalVal;
}

int main()
{
    Node *LL = new Node(nil, -INF, 0);
    Node *RR = new Node(LL, INF, 0);
    LL->ch[1] = RR;

    root = LL;

    int n;
    cin >> n;
    for(int i = 0, opt, x; i < n; i++) {
        scanf("%d %d", &opt, &x);
        if(opt == 1) {
            insert(x, 0);
        } else if(opt == 2) {
            erase(x);
        } else if(opt == 3) {
            printf("%d\n", query_rank(root, x));
        } else if(opt == 4) {
            Node *u = find_rank(root, x);
            if(u != nil)
                printf("%d\n", u->id);
        } else if(opt == 5) {
            Node *u = lower_bound(root, x - 1);
            printf("%d\n", u->id);
        } else if(opt == 6) {
            Node *u = upper_bound(root, x + 1);
            printf("%d\n", u->id);
        }
    }
}