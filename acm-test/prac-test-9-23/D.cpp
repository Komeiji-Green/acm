#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 100005;

// 素因数分解 
int p[maxn], l[maxn], cnt = 0;
void Fact(int x) {
    cnt = 0;
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0) {
            p[++cnt] = i; l[cnt] = 0;
            while(x % i == 0) {
                x /= i; 
                l[cnt]++;
            }
        }
    }
    if(x != 1) {  // 则此时x一定是素数，且为原本x的大于根号x的唯一素因子
        p[++cnt] = x; l[cnt] = 1;
    }
}

int main() {
    int T;
    cin >> T;
    int n;
    while(T--) {
        scanf("%d", &n);
        Fact(n);
        bool flag = false;
        for(int i = 1; i <= cnt; i++) {
            if(p[i] != 2 && p[i] != 5) {
                flag = true;
            }
        }
        if(flag) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    
}