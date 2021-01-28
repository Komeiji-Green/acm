#include<iostream>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;

const int maxn = 300000;

int s[maxn];   // 预处理序列
int p[maxn];    // 马拉车：半径

int L[maxn];    // 包含点i的回文串，回文中心最左
bool vis[maxn];
int R[maxn];    // 包含点i的回文串，回文中心最右

int le[maxn];   // 回文串前缀的‘#’端
int ri[maxn];   //

int n;      // 读取字符串长度
int tot;    // 指针，用于记录预处理串长度

void manacher()
{

    int right = 0, idx = 0;
    for(int i = 1; i <= tot; i++) {
        if(i < right)
            p[i] = min(p[2 * idx - i], right - i);
        else
            p[i] = 1;
        
        while(i + p[i] <= tot && s[i + p[i]] == s[i - p[i]])
            p[i]++;

        p[i]--;
        
        if(i + p[i] > right) {
            right = i + p[i];
            idx = i;
        }
    }

    //for (int i = 1; i <= tot; i++)
    //    p[i]--;
}

int main()
{
    int T;
    cin >> T;
    for(int test = 1; test <= T; test++) {
        cin >> n;
        
        // 这里的输入是整数不是字符，傻子！
        tot = 1;
        s[0] = -2;
        s[1] = -1;
        for(int i = 0, x; i < n; i++) {
            scanf("%d", &x);
            s[++tot] = x;
            s[++tot] = -1;
        }


        manacher();

        // 剪枝！！！！！！！！！



        /*
        memset(L, 0, sizeof(int) * (tot + 5));
        int mx = 0;
        int idx = 1;
        for(int i = 1; i <= tot; i += 2) {
            mx = i + p[i];
            for(int j = mx; j > i && j > idx; j -= 2) {
                if(j - p[j] <= i) {
                    L[j] = j - i;
                    idx = j;
                    break;
                }
            }
        } 用idx剪枝，又维护了一个数组，直接多消耗了两倍的时间，TLE
        */

        /*
        int ans = 0;
        for(int i = 1; i <= tot; i += 2) {
            if(L[i] > ans) ans = L[i];
        }*/

        
        int mx = 0;
        int ans = 0;
        for(int i = 1; i <= tot; i += 2) {
            mx = i + p[i];
            for(int j = mx; j > i + ans; j -= 2) {
                if(j - p[j] <= i) {
                    ans = j - i;
                    break;
                }
            }
        }
        

        /*for(int i = 1; i <= tot; i+=2) {
            printf("%d ", p[i]);
        }*/
        ans /= 2;
        printf("Case #%d: %d\n", test, ans * 3);
    }
}