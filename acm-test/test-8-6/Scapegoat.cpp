#include <iostream>
#include <vector>
using std::vector;
// Scapegoat

const double alpha = 0.7;
struct node
{
    node *l, *r;
    int val, size, cnt;
    bool deleted;
    bool isbad() { return l->cnt > alpha * cnt + 5 || r->cnt > alpha * cnt + 5; }
    void maintain()
    {
        size = !deleted + l->size + r->size;
        cnt = 1 + l->cnt + r->cnt;
    }
};

node *null;
void flatten(node *o, vector<node *> &v)
{
    if (o == null)
        return;
    flatten(o->l, v);
    if (!o->deleted)
        v.push_back(o); // 拍扁时将无效点删除
    flatten(o->r, v);
    if (o->deleted)
        delete o;
}

node *build(vector<node *> &v, int l, int r)
{
    if (l >= r)
        return null;
    int mid = l + ((r - l) >> 1);
    node *o = v[mid];
    o->l = build(v, l, mid);
    o->r = build(v, mid + 1, r);
    o->maintain();
    return o;
}

void rebuild(node *&o)
{
    vector<node *> v;
    flatten(o, v);
    o = build(v, 0, v.size());
}

void insert(int x, node *&o)
{
    if (o == null)
    {
        o = new node;
        o->l = o->r = null;
        o->deleted = false;
        o->size = o->cnt = 1;
        o->val = x;
        return;
    }
    else
    {
        ++o->size;
        ++o->cnt;
        if (x >= o->val)
            insert(x, o->r);
        else
            insert(x, o->l);
        if (o->isbad())
            rebuild(o);
    }
}

int rank(node *now, int x)
{
    int ans = 1;
    while (now != null)
    {
        if (now->val >= x)
            now = now->l;
        else
        {
            ans += now->l->size + !now->deleted;
            now = now->r;
        }
    }
    return ans;
}

int kth(node *now, int x)
{
    while (now != null)
    {
        if (!now->deleted && now->l->size + 1 == x)
            return now->val;
        if (now->l->size >= x)
            now = now->l;
        else
        {
            x -= now->l->size + !now->deleted;
            now = now->r;
        }
    }
}

void erase(node *o, int rk)
{
    if (!o->deleted && rk == o->l->size + 1)
    {
        o->deleted = 1;
        --o->size;
        return;
    }
    --o->size;
    if (rk <= o->l->size + !o->deleted)
        erase(o->l, rk);
    else
        erase(o->r, rk - o->l->size - !o->deleted);
}

node *root;
int main()
{
    null = new node;
    root = null;
    int n;
    scanf("%d", &n);
    while (n--)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1)
            insert(x, root);
        if (op == 2)
            erase(root, rank(root, x));
        if (op == 3)
            printf("%d\n", rank(root, x));
        if (op == 4)
            printf("%d\n", kth(root, x));
        if (op == 5)
            printf("%d\n", kth(root, rank(root, x) - 1));
        if (op == 6)
            printf("%d\n", kth(root, rank(root, x + 1)));
    }
}
