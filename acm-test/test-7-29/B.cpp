#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1000000 + 5;
int a[maxn];
int low[maxn]; // 在数组中截取取值在[0, i]中的部分，记录是否顺序，若顺序，尾部位置在哪？
bool vislow[maxn];
int high[maxn];   // [i, x]，同理
bool vishigh[maxn];

int n, x;

bool checkSlow(int l, int r) {
    int back = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] < l || a[i] > r) continue;
        if(a[i] < back) return false;
        back = a[i];
    }
    return true;
}

bool checkQuick(int l, int r) {
    if(r != x && high[x + 1] == -1) return false;
    int end = l == 0 ? 0 : low[l - 1];
    int begin = r == x ? n - 1 : high[r + 1];
    if(end <= begin) return true;
    else return false;
}

int main()
{
    cin >> n >> x;
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    for(int i = n - 1; i >= 0; i--) {
        int cur = a[i];
        if(!vislow[cur]) {
            vislow[cur] = true;
            low[cur] = i;   // cur所出现的末位置
        }
    }

    for(int i = 1; i <= x; i++) {
        //[0, i] 子序列的末尾
        low[i] = max(low[i - 1], low[i]);
    }


    for(int i = x; i >= 0; i--) {
        high[i] = n - 1;
    }

    for(int i = 0 ; i < n; i++) {
        int cur = a[i];
        if(!vishigh[cur]) {
            vishigh[cur] = true;
            high[cur] = i;  // cur所出现的首位置
        }
    }

    for(int i = x - 1; i >= 0; i--) {
        //[i, x] 子序列的起始位置
        high[i] = min(high[i + 1], high[i]);
    }


    int min = 0;
    int max = x;
    int mid = (min + max + 1) >> 1;
    while(min < max) {
        if(checkSlow(0, mid)) {
            min = mid;
        } else {
            max = mid - 1;
        }
        mid = (min + max + 1) >> 1;
    }
    for(int i = mid + 1; i <= x; i++)
        low[i] = -1;    // 屏蔽无效值
    
    min = 0; max = x; mid = (min + max) >> 1;
    while(min < max) {
        if(checkSlow(mid, x)) {
            max = mid;
        } else {
            min = mid + 1;
        }
        mid = (min + max) >> 1;
    }
    for(int i = mid - 1; i >= 0; i--)
        high[i] = -1;    // 屏蔽无效值
    


    ll cnt = 0;
    for(int l = 1; l <= x; l++) {
        if(l != 0 && low[l - 1] == -1) break;
        int mmin = l;
        int mmax = x;
        int r = (mmin + mmax) >> 1;
        while(mmin < mmax) {
            if(checkQuick(l, r)) {
                mmax = r;
            } else {
                mmin = r + 1;
            }
            r = (mmin + mmax) >> 1;
        }
        cnt += x - r + 1;
    }
    cout << cnt << endl;
}