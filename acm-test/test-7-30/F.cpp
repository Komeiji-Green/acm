#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

const int maxn = 100000 + 100;

pair<int, int> s[maxn]; // （高度，位置）

ll maxS = 0;

int head = 0;
int tail = 0;

void add(int h, int pos) {
    // 挤走全部比h大的
    int idx = upper_bound(s + head, s + tail, pair<int, int>(h, 0)) - s;
    ll sq;
    bool ok = idx == tail - head;
    for(int i = idx; i < tail - head; i++) {
        sq = (ll)s[i].first * (ll)(pos - s[i].second);
        if(sq > maxS) maxS = sq;
        //cout << idx << " " << sq << endl;
    }
    tail = idx;
    if(ok) 
        s[tail++] = pair<int, int>(h, pos);
    else
        s[tail++] = pair<int, int>(h, s[idx].second);
}

void init() {
    maxS = 0;
    head = 0;
    tail = 0;
}
int main()
{
    int n;
    while(scanf("%d", &n) != EOF && n != 0) {
        init();
        int x;
        for(int i = 1; i <= n; i++) {
            scanf("%d", &x);
            add(x, i);
        }
        add(0, n + 1);
        cout << maxS << endl;
    }
}