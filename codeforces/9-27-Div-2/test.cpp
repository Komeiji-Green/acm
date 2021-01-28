#include<iostream>
#include<ctime>
using namespace std;

typedef long long ll;
const int maxn = 100000 + 5;
bool isnt[maxn];
int prime[maxn];

int cnt =0;

void Prime(int n) {
    isnt[1] = true;
    cnt = 0;
    for(int i = 2; i <= n; ++i) {
        if(!isnt[i]) prime[++cnt] = i;
        for(int j = 1; j <= cnt; j++) {
            if(i *prime[j] > n) break;
            isnt[i * prime[j]] = i;
            if(i % prime[j] == 0) break;
        }
    }
}