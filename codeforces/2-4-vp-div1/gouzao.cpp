#include<bits/stdc++.h>
using namespace std;

int n;
int a[5050], b[5050];
int le[5050], ri[5050], sgn[5050];
int main() {
    cin >> n;
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i) scanf("%d", &b[i]);
    int num = 0;
    ++num; le[num] = 1, ri[num] = n, sgn[num] = 1; 
    sort(a + 1, a + n + 1);
    b[0] = 0;
    for(int i = 1; i < n; ++i) {
        if(b[i] > b[i-1]) {
            int j;
            for(j = i; j <= n; ++j) {
                if(a[j] == b[i]) break;
            }
            ++num; le[num] = i, ri[num] = j, sgn[num] = -1;
            sort(a + i, a + j + 1, greater<int>());
        } else {
            int j;
            for(j = i; j <= n; ++j) {
                if(a[j] == b[i]) break;
            }
            ++num; le[num] = i, ri[num] = j, sgn[num] = 1;
            sort(a + i, a + j + 1);
        }
    }
    printf("%d\n", num);
    for(int i = 1; i <= num; ++i) {
        printf("%d %d ", le[i], ri[i]);
        if(sgn[i] == 1) {
            printf("I\n");
        } else {
            printf("D\n");
        }
    } 
}