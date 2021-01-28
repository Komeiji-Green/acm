#include<bits/stdc++.h>
using namespace std;

const int maxn = 100050;
/**
 * 扫描线的线段树：

这是一个维护区间覆盖状态的线段树

首先，对于任何一个树上区间，要记录一个sum，表示它被完整覆盖过几次

反过来想，当我们添加一个区间时，我们会把它拆解为一些互不相交的树上区间

这个时候将所有结点上的sum值++

当我们撤销一个区间时，注意这个区间一定之前被添加过了，那我们相当于找回之前那些树上区间，把对应的sum值--。

好，有了这个

现在我们要维护每一时刻：

1. 各树上区间被覆盖的长度（根结点对应答案）
2. 各树上区间内有多少个完整的，互不相交的区间
3. 各树上区间是否有某个区间的左端点和右端点

覆盖长度如何维护？

添加：

找到所有区间，若该子区间sum为0，子区间len = 区间长度，sum++，然后pushup

撤回：
找到所有区间，sum--，若修改后sum为0，子区间len = 0，然后pushup

问题: 撤回的时候，子区间的sum是为0了，但这不影响它的某个父节点已经被一个更大的区间所覆盖，所以需要再pushup上做一些功夫

pushup怎么做？

对于k的pushup：如果sum非0，则 len = 区间长度，否则才更新为两个子区间的和

区间个数如何维护？

再添加到结点时，需要进行边界比较，判断是否是添加区间的左/右边界

内含完整区间设置为0，除非左右边界都是1，这时候内含设置为1，左右设置为0

怎么pushup

如果sum非0，不动如山

如果sum为0，那我才看左右子结点，
**/

// 动态开点权值线段树：区间覆盖
// 动态更新：区间整体加值
struct Segment_Tree {
    int ch[maxn*20], n, tot;
    int sum[maxn*20], lazy[maxn*20]; // 区间覆盖数
    int len[maxn*20];   // 被覆盖区间长度和
    int lseg[maxn*20], rseg[maxn*20], seg[maxn*20]; // 左端点，右端点与全端点数量  
    Segment_Tree() { n = tot = 0; }
    void Pushup(int k) {
        if(!sum[k]) {
            int lch = ch[k][0], rch = ch[k][1];
            len[k] = len[lch] + len[rch];
            if(rseg[rch] && lseg[lch]) seg[k] = seg[lch] + seg[rch] + 1;
            else if(rseg[rch] && !lseg[lch]) seg[k] = seg[rch];
            else if(!rseg[rch] && lseg[lch]) seg[k] = seg[lch];
            else seg[k] = seg[lch] + seg[rch];
        }

    }
    void add(int &k, int L, int R, int v, int l, int r) {
        if(!k) k = ++tot;
        if(L <= l && r <= R) {
            if(v > 0 && !sum[k]) len[k] = r - l + 1;
            sum += v;
            if(v < 0 && !sum[k]) len[k] = 0;
        }
        else {
            int m = l + ((r - l) >> 1);
            if(L <= m) add(ch[k][0], L, R, v, l, m);
            if(R > m) add(ch[k][1], L, R, v, m + 1, r);
            Pushup(k);
        }
    }
}
int main() {

}