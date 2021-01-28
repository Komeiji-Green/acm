#include <iostream>
using namespace std;
typedef long long ll;

struct Val
{
};

struct Lazy
{
};

struct Node
{
    Node() {}
    Node(Node *_fa, ll _val, int _weight): fa(_fa), key(_val), weight(_weight) {}
    Node *ch[2] = { nullptr, nullptr };
    Node *fa = nullptr;
    ll key;
    int weight;
};

Node *nil = nullptr;

void push_down(Node *u)
{
}

void maintain(Node *u)
{
}

void rotate(Node *u)
{
    Node *f = u->fa, *ff = f->fa;
    int d = u == f->ch[1];
    push_down(f), push_down(u);
    if ((f->ch[d] = u->ch[d ^ 1]) != nil)
        f->ch[d]->fa = f;
    if ((u->fa = ff) != nil)
        ff->ch[f == ff->ch[1]] = u;
    f->fa = u;
    u->ch[d ^ 1] = f;
    maintain(f), maintain(u);
}

Node *root = NULL;

void splay(Node *u, Node *target)
{
    for (Node *f; u->fa != target; rotate(u))
        if ((f = u->fa)->fa != target)
        {
            ((u == f->ch[1]) ^ (f == f->fa->ch[1])) ? rotate(u) : rotate(f);
        }
    if (target == nil)
        root = u;
}


/*
left-rotate(a):
	b = a.right
	b.father = a.father
	If (a.father.left == a) Then
		a.father.left = b
	Else
		a.father.right = b
	End If
	a.right = b.left
	b.left.father = a
	b.left = a
	a.father = b
*/

void left_rotate(Node *a) {
    Node *b = a->ch[1];
    b->fa = a->fa;
    if(a->fa->ch[0] == a) {

    }
}

/*
小Hi：只要将节点插入Treap以后，再不断的旋转当前节点直到weight满足堆的性质。

首先我们从插入操作来看，这里我们让insert完成后返回新加入的节点：

insert(node, key):
	If (key < node.key) Then
		If (node.left is empty) Then
			node.left = {key: key, weight: random()}
			Return node.left
		Else 
			Return insert(node.left)
		End If
	Else
		If (node.right is empty) Then
			node.right = {key: key, weight: random()}
			Return node.right
		Else 
			Return insert(node.right)
		End If
	End If
完成插入操作后，我们获得了新加入的节点，然后迭代的进行旋转(这里假设采用小根堆)：
*/

Node *insert(Node *node, int key) {
    if(key < node->key) {
        if(node->ch[0] == nil) {
            node->ch[0] = new Node(node, key, rand() % 10000);
            return node->ch[0];
        } else {
            return insert(node->ch[0], key);
        }
    } else {
        if(node->ch[1] == nil) {
            node->ch[1] = new Node(node, key, rand() % 10000);
            return node->ch[1];
        } else {
            return insert(node->ch[1], key);
        }
    }
}

Node* find(Node *node, int key) {
    if(node == nil) return nil;
    else if(key < node->key) {
        return find(node->ch[0], key);
    } else {
        if(key == node->key) return node;
        Node * res = find(node->ch[1], key);
        if(res == nil) return node;
        else return res;
    }
}

/*
rotate(node):
	While (node.father is not empty)
		fa = node.father
		If (node.weight < fa.weight) Then
			If (node == fa.left) Then
				right-rotate(fa)
				// 这里的参数是父节点
				// 在该处fa对应了旋转中的节点a, node对应了节点b
			Else
				left-rotate(fa)
			End If
		Else
			Break
		End If
	End While

*/

void treap(Node *node) {
    Node *f;
    while((f = node->fa) != nil && (f->weight > node->weight))
        rotate(node);
    if(node->fa == nil)
        root = node;
}

/*
需要注意的是，对于我这种插入的写法，需要手动在Treap中插入第一个元素：

main():
	root = NULL
	For i = 1 .. n
		input x
		If (root is empty) 
			root = {key: x, weight: random()}
		Else 
			rotate(insert(root, x))
		End If
	End For
*/

int main()
{
    root = nil;
    int n;
    cin >> n;
    string op; ll k;
    for(int i = 0; i < n; i++) {
        cin >> op >> k;
        if(op == "I") {
            if(root == nil) {
                root = new Node(nil, k, rand() % 10000);
            } else 
                treap(insert(root, k));
        } else {
            Node *u = find(root, k);
            if(u != nil)
                printf("%lld\n", u->key);
        }
    }
}