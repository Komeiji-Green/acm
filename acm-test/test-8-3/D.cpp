#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;

int s[70];  // 各长度的木棒的数量
int sum;
int n;
int ans;
int fail[10000];
int failcnt = 0;


void init()
{
    sum = 0;
    memset(s, 0, sizeof(s));
    ans = 0;
    failcnt = 0;
    memset(fail, 0, sizeof(fail));
}

// 状态：cnt，last（上一木棒长度），len，s
bool dfs(int cnt, int last, int len) {
    //printf("%d %d\n", cnt, len);
    //for(int i = 1; i <= 10; i++)
        //printf("%d ", s[i]);
    //cout << endl;
    if(cnt == 1 && len == 0) return true;
    if(len == 0) return dfs(cnt - 1, 50, ans);
    
    for(int i = min(len, last); i > 0; i--) {
        if(s[i] == 0) continue;
        s[i]--;
        if(dfs(cnt, i, len - i)) {
            s[i]++;
            return true;
        }
        s[i]++;
        if(len == ans) break;
    }
    return false;
}

int main()
{
    while(cin >> n && n != 0) {
        init();
        int len;
        int max_len = 0;
        for(int i = 0; i < n; i++) {
            cin >> len;
            sum += len;
            s[len]++;
            max_len = max(len, max_len);
        }

        //cout << max_len << endl;
        //cout << sum << endl;

        for(ans = max_len; ans <= sum; ans++) {
            if(sum % ans) continue;
            //cout << ok << endl;
            if(dfs(sum / ans, 50, ans)) {
                cout << ans << endl;
                break;
            }
        }
    }
}