#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <set>
using namespace std;

typedef long long ll;

const ll INF = 0x3f3f3f3f;
const int N = 200050;
ll a[N], pre[N];

int que[N];
int head = 0, tail = 0;

ll dp[N];   // dp值
ll maxv[N];  // j向i转移过去的值

multiset<ll> s;

int main()
{
    int n;
    ll M;
    cin >> n >> M;
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    // 特判无解
    for(int i = 1; i <= n; i++) {
        if(a[i] > M) {
            printf("-1\n");
            return 0;
        }
    }

    pre[0] = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    a[0] = INF;

    for(int i = 0; i <= n; i++) {
        dp[i] = maxv[i] = 0;
    }

    head = tail = 0;
    que[tail++] = 0;
    //s.insert(dp[0] + maxv[0]);
    for(int i = 1; i <= n; i++) {
        int back;
        a[head] = INF;
        while(head + 1 < tail && a[back = que[tail - 1]] <= a[i]) {
            if(back != i - 1) s.erase(s.find(dp[back] + maxv[back]));
            tail--;
        }

        //printf("dddd\n");

        //printf("back: %d\n", back);
    
        back = que[tail - 1];
        if(back != i - 1) s.erase(s.find(dp[back] + maxv[back]));
        maxv[back] = a[i];
        s.insert(dp[back] + maxv[back]);

        que[tail++] = i;
        //s.erase(s.find(dp[i] + maxv[i]));

        /*if(!flag) {
            que[tail++] = i - 1;
            trans[i - 1] = dp[i - 1] + a[i];
            s.insert(trans[i - 1]);
        } else {
            ll &ts = trans[que[tail - 1]];
            s.erase(s.find(ts));
            ts = dp[que[tail - 1]] + a[i];
            s.insert(ts);
        }*/
        
        int idx = que[head];
        while(idx < i && pre[i] - pre[idx] > M) idx++;

        ll val;
        for(int cur; (cur = (que[head])) <= idx; head++) {
            s.erase(s.find(dp[cur] + maxv[cur]));
            val = maxv[cur];
        }
        maxv[idx] = val;

        que[--head] = idx;
        s.insert(dp[idx] + maxv[idx]);

        /*if(head + 1 < tail) {
            s.erase(s.find(trans[que[head]]));
            trans[que[head]] = trans[que[head + 1]] - dp[que[head + 1]] + dp[que[head]];
            s.insert(trans[que[head]]);
        }
        int idx = que[head];
        while(pre[i] - pre[idx] > M) idx++;
        while(que[head] < idx) {
            s.earse(s.find(trans[que[head]]));
            head++;
        }
        while(pre[i] - pre[que[head]] > M) {
            //s.erase(s.find())
            int tmp = que[head];
            if(head + 1 < tail && que[head] == que[head + 1]) {
                s.erase(s.find(trans[que[head]]));
                head++;
                s.erase(s.find(trans[que[head]]));
                que[head] = tmp + 1;
                trans[que[head]] = 
            }
            s.erase(s.find(trans[que[head]]));
            que[head] = tmp + 1;
        }*/
        if(!s.empty())
            dp[i] = *(s.begin());

        //printf("%d\n", i);
    }

    /*for(auto it : s) {
        printf("%lld ", it);
    }
    printf("\n");*/
    
    printf("%lld\n", dp[n]);
    return 0;
}