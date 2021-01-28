#include<iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

int sg[2000005];
void DP()
{
    sg[1] = 0;
    bool vis[100];
    for(int i = 2; i <= 1999999; i++) {
        int n = i, r = 1;
        memset(vis, 0, sizeof(vis));
        while(n > 1) {
            int d = n % 10;
            if(d == 0) {
                vis[sg[i / r / 10]] = true;
            } else {
                for(int j = 1; j <= d; j++) {
                    vis[sg[i - r * j]] = true;
                }
            }
            n /= 10; r *= 10;
        }
        for(int j = 0; j < 100; j++) {
            if(!vis[j]) {
                sg[i] = j;
                break;
            }
        }
    }
}

int main()
{
    char s[100];

    clock_t st, ed;
    st = clock();
    DP();
    ed = clock();
    //cout << (double)(ed - st) / CLOCKS_PER_SEC << endl;

    while(scanf("%s", s) != EOF) {
        int n = 1;
        for(int i = 0; s[i]; i++) {
            n = n * 10 + s[i] - '0';
        }
        if(sg[n]) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}