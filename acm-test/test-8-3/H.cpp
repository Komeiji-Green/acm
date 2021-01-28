#include<iostream>
#include<cstring>
using namespace std;

inline int Ceil(int m, int n) { return (m - 1) / n + 1; }

/*
Buses on the same route arrive at regular intervals from 12:00 to 12:59 throughout the entire hour.
Times are given in whole minutes from 0 to 59.
Each bus route stops at least 2 times.
The number of bus routes in the test examples will be <=17.
*/

int state[60];  // 0-59分钟停车表
int ans;

// 状态：state与rts


bool dfs(int rts, int dist, int cnt, int cur_idx) {

    //printf("%d %d %d %d\n", rts, dist, cnt, cur_id);
    if(rts > ans) return false;
    if(dist > 60) return false;

    int sum = 0;
    for(int i = 0; i < 60; i++)
        sum += state[i];
    if(sum == 0) return true;
    //if(Ceil(sum, Ceil(60, dist + 1)) + rts > ans) return false;

    bool flag = false;

    for(int idx = cur_idx; idx < dist && idx + dist < 60; idx++) {
        bool ok = true;
        for(int x = idx; x < 60; x += dist)
            if(state[x] == 0) {
                ok = false;
                break;
            }
        if(!ok) continue;

        //printf("%d %d %d %d", rts, cnt, idx, dist);
        flag = true;
        for(int x = idx; x < 60; x += dist)
            state[x]--;
        //printf(" %d\n", sum);
        bool res = dfs(rts + 1, dist, cnt + 1, idx);
        for(int x = idx; x < 60; x += dist)
            state[x]++;
        if(res) return true;
    }
    return dfs(rts, dist + 1, 0, 0);
}

/*
bool dfs(int rts) {
    //cout << ans << " " << rts << endl;/
    if(rts > ans) return false;
    int idx = 0;
    for(idx = 0; idx < 60; idx++)
        if(state[idx]) break;
    //cout << idx << endl;
    if(idx == 60 && rts <= ans) return true;
    if(idx >= 30) return false;

    int sum = 0;
    for(int i = 0; i < 60; i++)
        sum += state[i];
    if(Ceil(sum, Ceil(60, idx + 1)) + rts > ans) return false;

    for(int d = idx + 1; idx + d < 60; d++) {
        bool ok = true;
        for(int x = idx; x < 60; x += d)
            if(state[x] == 0) {
                ok = false;
                break;
            }
        if(!ok)  {
            //printf("%d %d %d %d\n", ans, rts, idx, d);
            continue;
        }
        for(int x = idx; x < 60; x += d)
            state[x]--;
        //printf("%d %d %d %d\n", ans, rts, idx, d);
        bool ret = dfs(rts + 1);
        for(int x = idx; x < 60; x += d)
            state[x]++;
        if(ret) return true;
    }
    return false;
}
*/

int main()
{
    int n;
    int time;
    cin >> n;
    for(int i = 0; i < n; i++)
    {
        cin >> time;
        state[time]++;
    }
    
    for(int i = 0; i <= 17; i++) {
        ans = i;
        if(dfs(0, 1, 0, 0)) {
            cout << ans << endl;
            break;
        }
    }
}