#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>
using namespace std;

const int maxn = 100000;
int f[100100];  

string s, t;

void getNext(const string &t) {
    int len = t.size();
    f[0] = -1; f[1] = 0; 
    for(int i = 1, j = 0; i < len; i++) { 
        while(j && t[i] != t[j]) j = f[j];
        if(t[i] == t[j]) j++;   
        f[i + 1] = j;
    }
}

int kmp(char *t, char *s) {
    // 可能要加getNext，也可能预处理
    int lens = strlen(s);
    int lent = strlen(t);
    for(int i = 0, j = 0; i < lens; i++) {
        while(j & s[i] != t[j]) j = f[j];  
        if(s[i] == t[j]) j++;
        if(j == lent) { return i - lent + 1;  j = f[j]; }
    }
    return lens;
}

int extend[100100]; // 记录s每一个后缀关于t的最长前缀

void exKmp(const string &t, const string &s) {
    int lens = s.size(), lent = t.size(), i, j;

    getNext(t);

   //cout << "getNext!!!" << endl;
    
    for(i = 0, j = 0; i < lens; i++) {
        while(j && s[i] != t[j]) {
            extend[i - j] = j;
            //cout << "extend!!!!" << endl;
            j = f[j]; 
        }
        if(s[i] == t[j]) j++;
        if(j == lent) { extend[i + 1 - j] = j; j = f[j]; }
    }

    while(j && i - j < lens) { extend[i - j] = j; j = f[j]; }
}

void init()
{
    memset(extend, 0, sizeof(extend));
}

int main()
{
    while(cin >> t) {
        cin >> s;

        init();
        exKmp(t, s);
        int len = s.size();
        int ans = 0;
        int idx = -1;

       /* for(int i = 0; i < len ;i++)
            printf("%d ", extend[i]);
        cout << endl;*/
        for(int i = 0; i < len; i++) {
            if(i + extend[i] >= len && extend[i] > ans) {
                ans = extend[i];
                idx = i;
            }
        }
        if(ans == 0 || idx == -1)
            cout << 0 << endl;
        else {
            cout << s.substr(idx) << " " << ans << endl;
        }
    }
}