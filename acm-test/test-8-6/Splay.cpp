#include<iostream>
using namespace std;
typedef long long ll;
const int INF = 0x3f3f3f3f;
/*
首先我们要改造我们的节点信息，因为每个成员有id和兴趣值val两个属性，所以节点所包含的信息肯定不止一个key了。

我们将节点改造为：

Node:
	id, // 成员的id
	val, // 成员的兴趣值val
	totalVal, // 以当前结点为根的子树的总兴趣值
	sum, // 以当前结点为根的子树的节点总数
由于在splay中，树的结构是不断变化的，因此我们需要在树变化时对相关节点的totalVal和sum进行更新，
从而使得每个节点的totalVal和sum始终保持正确值。

*/

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

/*
我们需要一个update函数来更新节点的信息：

update(x):
	x.sum = 1	// 初始化假设只有一个节点
	x.totalVal = x.val	// 初始化为当前结点的值

	// 将左子树的信息加入
	If (x.left is not empty) Then
		x.sum = x.sum + x.left.sum
		x.totalVal = x.totalVal + x.left.totalVal
	End If
	
	// 将右子树的信息加入
	If (x.right is not empty) Then
		x.sum = x.sum + x.right.sum
		x.totalVal = x.totalVal + x.right.totalVal
	End If

*/

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

/*
而会改变树形态的有2种情况，一是rotate函数，因此我们需要在rotate函数中去更新信息：

right-rotate(x):
	p = x.father
	x.father = p.father
	If (p.father is not empty) Then
		If (p.father.left == p) Then
			p.father.left = x
		Else
			p.father.right = x
		End If
	Else
		root = x
	End If
	p.left = x.right
	x.right.father = p
	x.right = p
	p.father = x
	update(p) // 更新p节点
	update(x) // 更新x节点
此处一定要注意，由于旋转之后p节点为x的儿子，所以需要先更新p节点，再更新x的节点，才能保证数据的正确性。left-rotate(x)做对应的修改即可，不再赘述。

第二个是插入节点，需要将原来的bst_insert函数改为：

bst_insert(root, id, val):
	If (id < root.id) Then
		If (root.lch is empty) Then
			root.lch = new node(id, val)
		Else 
			bst_insert(root.lch, id, val)
		End If
	Else
		If (root.rch is empty) Then
			root.rch = new node(id, val)
		Else 
			bst_insert(root.rch, id, val)
		End If
	End If
	update(root) // 最后更新信息
	Return root
	
insert(id, val):
	node = bst_insert(root, id, val)
	splay(node, NULL) // 插入之后仍然要将插入的节点splay到根
有了更新的操作，就可以直接将询问操作完成：

对于区间[a,b]，我们找到a的前驱节点prev，b的后继节点next。将prev旋转至根，同时将next旋转至根的儿子。此时next的左子树就包含了[a,b]区间内所有的节点，而这颗子树根节点的totalVal，也即是我们要求的解。

小Ho：嗯，这个我理解了。但是修改操作该怎么办？

每一次修改的也是一个区间[a,b]，如果要将每一个值都修改掉，还是需要花费O(n)的时间，有办法减少么？

小Hi：有的，解决办法采用了之前我们在线段树中有讲过的懒标记。

首先我们再修改一次节点信息：

Node:
	id, // 成员的id
	val, // 成员的兴趣值val
	totalVal, // 以当前结点为根的子树的总兴趣值
	sum, // 以当前结点为根的子树的节点总数
	lazy, // 以当前结点为根的子树中，所有节点的val值都增加lazy
在修改操作中，我们找到区间[a,b]中a的前驱节点prev，b的后继节点next。将prev旋转至根，同时将next旋转至根的儿子。此时next的左子树就包含了[a,b]区间内所有的节点。

使用函数marking来给next的左儿子打上懒标记：

marking(node, delta):
	// 原来可能就有懒标记，因此是在lazy的基础上增加delta
	node.lazy = node.lazy + delta
	// 同时对当前结点应用上懒标记
	node.totalVal = node.totalVal + node.sum * delta
	node.val = node.val + delta
有了懒标记，接下来就要考虑什么时候将懒标记怎样将传递出去。

*/
/*

传递懒标记的函数为send：

send(node):
	If (node.left is not empty) Then
		marking(node.left, node.lazy)
	End If
	If (node.right is not empty) Then
		marking(node.right, node.lazy)
	End If
	node.lazy = 0 // 清空懒标记
	update(node) // 同时别忘了更新一下当前结点
最后是考虑什么时候传递懒标记。和更新操作一样，每当一个节点的信息有可能发生改变时，
就需要将其懒标记传递给儿子。修改旋转和插入两个函数：
*/

void marking(Node *node, int lz) {
    node->lazy += lz;
    node->totalVal += 1ll * lz * node->sum;
    node->val += lz;
}

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

/*

1. 旋转操作时，我们会访问p和x两个节点，由于会旋转这两个节点，其信息一定会发生改变，因此需要传递懒标记。将旋转操作修改为：

right-rotate(x):
	// left-rotate(x)做对应的修改即可
	p = x.father
	send(p)	// 传递p节点的懒标记
	send(x) // 传递x节点的懒标记
	x.father = p.father
	If (p.father is not empty) Then
		If (p.father.left == p) Then
			p.father.left = x
		Else
			p.father.right = x
		End If
	Else
		root = x
	End If
	p.left = x.right
	x.right.father = p
	x.right = p
	p.father = x
	update(p)
	update(x)
同样，由于p和x的父子关系，需要先传递p节点的懒标记，再传递x节点的懒标记。
*/

void rotate(Node *u) {
    Node *f = u->fa, *ff = f->fa;
    push_down(f); push_down(u);
    int d = u == f->ch[1];
    if((u->fa = ff) != nil)
        ff->ch[f == ff->ch[1]] = u;
    if((f->ch[d] = u->ch[d ^ 1]) != nil)
        f->ch[d]->fa = f;
    f->fa = u;
    u->ch[d ^ 1] = f;
    maintain(f); maintain(u);
}

/*

2. 插入操作时，我们会加入一个信息的节点，这会使得整个路径上的节点信息都发生改变，因此需要传递懒标记。则将插入操作修改为：

bst_insert(root, id, val):
	send(root)
	If (id < root.id) Then
		If (root.lch is empty) Then
			root.lch = new node(id, val)
		Else 
			bst_insert(root.lch, id, val)
		End If
	Else
		If (root.rch is empty) Then
			root.rch = new node(id, val)
		Else 
			bst_insert(root.rch, id, val)
		End If
	End If
	update(root) // 同时也别忘了最后更新信息
	Return root
	
insert(id, val):
	node = bst_insert(root, id, val)
	splay(node, NULL) // 插入之后仍然要将插入的节点splay到根
通过懒标记的方法，我们就将修改操作的复杂度降低了，不需要花费O(n)的时间去进行修改。
*/

void splay(Node *node, Node *target) {
    for(Node *f; (f = node->fa) != target; rotate(node)) {
        if((f->fa) != target) {
            (f->fa->ch[1] == f) ^ (f->ch[1] == node) ? rotate(node) : rotate(f);
        }
    }
    if(target == nil)
        root = node;
}


Node * bst_insert(Node *node, int id, int val) {
    push_down(node);
    int d = id >= node->id;
    if(node->ch[d] == nil)
        return node->ch[d] = new Node(node, id, val);
    else
        return bst_insert(node->ch[d], id, val);
}

void insert(int id, int val) {
    Node *node = bst_insert(root, id, val);
    splay(node, nil);
}



Node* lower_bound(Node *node, int id) {
    if(node == nil) return nil;
    else if(id < node->id) {
        return lower_bound(node->ch[0], id);
    } else {
        if(id == node->id) return node;
        Node * res = lower_bound(node->ch[1], id);
        if(res == nil) return node;
        else return res;
    }
}

Node* upper_bound(Node *node, int id) {
    if(node == nil) return nil;
    else if(id > node->id) {
        return upper_bound(node->ch[1], id);
    } else {
        if(id == node->id) return node;
        Node * res = upper_bound(node->ch[0], id);
        if(res == nil) return node;
        else return res;
    }
}


Node *pre(Node *u) {
    if(u->ch[0] != nil)
        return pre(u->ch[0]);
    Node *f = u->fa;
    while(f != nil && u == f->ch[0]) {
        u = f;
        f = f->fa;
    }
    return f;
}

Node *nxt(Node *u) {
    if(u->ch[1] != nil)
        return nxt(u->ch[1]);
    Node *f = u->fa;
    while(f != nil && u == f->ch[1]) {
        u = f;
        f = f->fa;
    }
    return f;
}

/*

那么最后总结一下这4个操作分别的对应方法：

1. 插入：

直接将新的成员插入splay；插入操作中传递懒标记并且更新节点信息；最后把插入的节点splay到根。

2. 修改：

找到a的前驱prev，b的后继next，然后将prev旋转至根，next旋转至根的儿子，
对next的左儿子打上懒标记；旋转操作中传递懒标记并且更新节点信息。

*/

void add(int l, int r, int d) {
    Node * prev = lower_bound(root, l - 1);
    Node * next = upper_bound(root, r + 1);
    splay(prev, nil);
    splay(next, root);

    marking(next->ch[0], d);
}

/*

3. 删除：

找到a的前驱prev，b的后继next，然后将prev旋转至根，next旋转至根的儿子，
将next的左儿子删除，并依次更新next和prev节点；
旋转操作中传递懒标记并且更新节点信息。

*/

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

/*

4. 询问：

找到a的前驱prev，b的后继next，然后将prev旋转至根，next旋转至根的儿子，
获取next的左子树的实际总价值。

小Ho：这样好像就将所有操作的时间复杂度降低到O(log n)的水平了，我明白了！

小Hi：没错，合理地利用更新函数和懒标记就可以使得在对区间进行操作时更加快速，这也是充分利用了splay的特性。小Ho，这有帮到你了么？

小Ho：当然有了！谢谢你小Hi，我这就去实现它！
*/

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
    int n;
    cin >> n;
    root = nil;
    char op[4];
    int ida, idb, d;
    Node *AA = new Node(nil, -INF, 0);
    Node *BB = new Node(AA, INF, 0);
    AA->ch[1] = BB;
    root = AA;
    for(int i = 0; i < n; i++) {
        scanf("%s", op);
        if(op[0] == 'Q') {
            scanf("%d %d", &ida, &idb);
            printf("%lld\n", query(ida, idb));
        } else if(op[0] == 'I') {
            scanf("%d %d", &ida, &d);
            insert(ida, d);
        } else if (op[0] == 'M') {
            scanf("%d %d %d", &ida, &idb, &d);
            add(ida, idb, d);
        } else {
            scanf("%d %d", &ida, &idb);
            erase(ida, idb);
        }
    }
}