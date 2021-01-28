#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


struct node {
    int start;
    int dist;
    int times;
};

struct cmp {
    bool operator()(const node& lhs, const node& rhs) {
        return lhs.times > rhs.times;
    } 
};

int a[305];
int state[60];
node routes[100000];
int sz = 0;

int check(const node& nd)
{
    int cnt = 0;
    for(int x = nd.start; x < 60; x += nd.dist, cnt++)
        if(state[x] == 0) return -1;
    return cnt;
}

int ans = 17;

void dfs(int cur, int sum, int cnt) 
// k：当前搜索的线路, sum: 剩余总记录数，cnt：已经确认的公交线路
{
    if(sum == 0) { ans = min(ans, cnt); return; }
    if(cur >= sz || cur < 0) return;
    if(sum / routes[cur].times + cnt >= ans) return;
    for(int j = cur; j < sz; j++) {
        node u = routes[j];
        int times = check(u);
        if(times == -1) continue;
        for(int x = u.start; x < 60; x += u.dist)
            state[x]--;
        dfs(j, sum - times, cnt + 1);
        for(int x = u.start; x < 60; x += u.dist)
            state[x]++;
    }
}

int main()
{
    int n;
    int time;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> time;
        a[i] = time;
        state[time]++;
    }
    node test;
    for(int i = 0; i < 60; i++)
    {
        for(int d = i + 1; i + d < 60; d++) {
            test.start = i;
            test.dist = d;
            int t = check(test);
            test.times = t;
            if(t != -1)
                routes[sz++] = test;
        }
    }

    sort(routes, routes + sz, cmp());
    
    dfs(0, n, 0);
    cout << ans << endl;
}