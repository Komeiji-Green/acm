#include<iostream>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;

const int maxn = 50000;


char pre[maxn]; // 读取序列

char s[maxn];   // 预处理序列
int p[maxn];    // 马拉车：半径

int L[maxn];    // 包含点i的回文串，回文中心最左
int R[maxn];    // 包含点i的回文串，回文中心最右

int le[maxn];   // 回文串前缀的‘#’端
int ri[maxn];   //

int n;      // 读取字符串长度
int tot;    // 指针，用于记录预处理串长度

void manacher()
{
    tot = 1;
    s[0] = '%';
    s[1] = '#';
    for (int i = 0; i < n; i++)
    {
        s[++tot] = pre[i];
        s[++tot] = '#';
    }

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
    while(T--) {
        scanf("%s", pre);
        n = strlen(pre);
        manacher();

        /*int idx = 1;
        for(int i = 1; i <= tot; i++) {
            while(i + p[i] >= idx) {
                L[idx++] = i;
            }
        }

        idx = tot;
        for(int i = tot; i >= 1; i--) {
            while(i - p[i] <= idx) {
                R[idx--] = i;
            }
        }*/

        /*for(int i = 1; i <= tot; i++)
            printf("%d ", p[i]);
        printf("\n");
        for(int i = 1; i <= tot; i++)
            printf("%d ", L[i]);
        printf("\n");
         for(int i = 1; i <= tot; i++)
            printf("%d ", R[i]);
        printf("\n");*/

        int mid;
        int pl = 0;
        int pr = 0;

        for(int i = 1; i <= tot; i += 2) {
            mid = (1 + i) / 2;
            if(p[mid] >= 1 && mid + p[mid] >= i)
                le[pl++] = i;
        }
        for(int i = tot; i >= 1; i -= 2) {
            mid = (tot + i) / 2;
            if(p[mid] >= 1 && mid - p[mid] <= i)
                ri[pr++] = i;
        }


        bool ok = false;
        for(int i = 0; i < pl && !ok; i++) {
            for(int j = 0; j < pr && !ok; j++) {
                if(le[i] >= ri[j]) continue;
                mid = (le[i] + ri[j]) / 2;
                if(mid + p[mid] >= ri[j]) { 
                    ok = true; 
                    //cout << *itx << " " << mid << " " << *ity << endl;
                }
            }
        }
        if(ok) cout << "Yes" << endl;
        else cout << "No" << endl;

    }
}