#include<bits/stdc++.h>
#include<ctime>
using namespace std;

const int maxn = 1005;
char s[maxn];
int main() {
    srand(time(NULL));
    int len = rand() % 100 + 1;
    for(int i = 0; i < len; ++i) {
        s[i] = rand() % 26 + 'a';
    }
    s[len] = '\0';
    printf("%s\n", s);
    printf("%d %d\n", rand() % 2, rand() % 3000 + 1);
}