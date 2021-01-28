#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef long long ll;

const int maxn = 30000 + 100;

struct Query {
    int l, r;
    int id;
    bool operator< (const Query& rhs) {
        return r < rhs.r;
    }
};
Query Q[100000 + 5];
ll ans[100000 + 5];

unordered_map<ll, int> sub;
// 数组a[1-i]中，动态记录值为v的数出现的最后下标
// 只有至多3w组数据，而数据的规模在1~10^9，考虑哈希

ll C[maxn];
ll a[maxn];

int n;

void add(int x, int val) {
    for(int i = x; i <= n; i += (i & (-i))) {
        C[i] += val;
    }
}

ll query(int x) {
    ll ans = 0;
    for(int i = x; i > 0; i -= (i & (-i))) {
        ans += C[i];
    }
    return ans;
}


int main()
{
    int T;
    cin >> T;
    while(T--) {
        memset(C, 0, sizeof(C)); 
        sub.clear();
        cin >> n;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        int q;
        cin >> q;
        for(int i = 1, l, r; i <= q; i++) {
            scanf("%d %d", &l, &r);
            Q[i].l = l;
            Q[i].r = r;
            Q[i].id = i;
        }
        sort(Q + 1, Q + q + 1); 
        //for(int i = 1; i <= q; i++) 
            //printf("%d %d %d\n", Q[i].l, Q[i].r, Q[i].id);
        // 离线操作，将待查区间按右边界排序，对每个区间，只关注有边界以左的数据
        // 这样就只需关注所有相同数字最后出现在哪里
        // 区间下标
        for(int i = 1, j = 1; i <= n; i++) {
            if(!sub.count(a[i])) {
                add(i, a[i]);
            } else {
                add(i, a[i]);
                add(sub[a[i]], -a[i]);
            } 
            sub[a[i]] = i;
            while(j <= q && Q[j].r == i) {
                ans[Q[j].id] = query(i) - query(Q[j].l - 1);
                j++;
            }
            
        }

        for(int i = 1; i <= q; i++) {
            printf("%lld\n", ans[i]);
        }

    }
    
}