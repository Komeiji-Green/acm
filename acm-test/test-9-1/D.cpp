#include<iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
using namespace std;

int f[15];
int sg[1050];
void DP()
{
    f[0] = 1;
    for(int i = 1; i <= 10; i++) {
        f[i] = 2 * f[i - 1];
    }

    bool vis[15];
    sg[0] = 0;
    for(int i = 1; i <= 1000; i++) {
        memset(vis, 0, sizeof(vis));
        for(int j = 0; f[j] <= i; j++) {
            vis[sg[i - f[j]]] = true;
        }
        for(int j = 0; j <= 10; j++) {
            if(!vis[j]) {
                sg[i] = j;
                break;
            }
        }
    }
}

int main()
{
    DP();
    int n;
    while(scanf("%d", &n) != EOF) {
        if(sg[n]) {
            printf("Kiki\n");
        } else {
            printf("Cici\n");
        }
    }
}