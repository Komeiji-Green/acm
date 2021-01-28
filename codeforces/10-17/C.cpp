#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 233333;
char s[maxn];
char stk[maxn];
int top = 0;
int main() {
    int T, n;
    cin >> T;
    while(T--) {
        scanf("%s", s);
        n = strlen(s);
        top = 0;
        for(int i = 0; i < n; ++i) {
            if(s[i] == 'B' && top) top--;
            else stk[top++] = s[i];
        }
        printf("%d\n", top);
    }
}