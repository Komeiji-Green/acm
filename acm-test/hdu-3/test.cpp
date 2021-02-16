#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int f[23333], w[23333];
    int find(int x) {
        return f[x] == x ? x : f[x] = find(f[x]);
    }
    void merge(int x, int y) {
        int fx = find(x), fy = find(y);
        if(fx == fy) return;
        w[fy] += w[fx]; f[fx] = fy;
    }
    int minSwapsCouples(vector<int>& row) {
        int sz = row.size();
        int n = sz / 2;
        for(int i = 1; i <= n; ++i) f[i] = i, w[i] = 1;
        for(int i = 0, x, y; i < sz; i += 2) {
            x = row[i] / 2 + 1;
            y = row[i+1] / 2 + 1;
            merge(x, y);
        }
        int res = 0;
        for(int i = 1; i <= n; ++i) {
            if(f[i] == i) {
                res += w[i] - 1;
            }
        }
        return res;
    }
};

int main() {
    vector<int> vec({0,2,1,3});
    int ans = T.minSwapsCouples(vec);
    printf("%d\n", ans);
}