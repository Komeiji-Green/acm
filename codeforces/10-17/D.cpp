#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 100500;
int a[maxn];

struct Point {
    int x, y, id;
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
} p[maxn<<1], stk[maxn<<1];
int num = 0;

int main() {
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    Point last = Point(0, 0), cur;
    last.id = 0;
    int tot = n, top = 0;
    bool flag = true;
    for(int i = n; i >= 1; --i) {
        if(a[i] == 0) continue;
        else if(a[i] == 1) {
            cur = Point(i, tot);
            p[num++] = cur;
            stk[top++] = cur;
            if(last.id <= 1) { last = cur; last.id = 1; }
            tot--;
        } else if(a[i] == 2) {
            if(!top) { flag = false; break; }
            cur = Point(i, stk[top - 1].y);
            p[num++] = cur;
            if(last.id <= 2) { last = cur; last.id = 2; }
            top--;
        } else if(a[i] == 3) {
            if(last.id == 0) { flag = false; break; }
            cur = Point(i, tot);
            p[num++] = cur;
            p[num++] = Point(last.x, tot);
            if(last.id == 1) top--;
            last = cur; last.id = 3;
            tot--;
        }
    }
    if(!flag) printf("-1\n");
    else {
        printf("%d\n", num);
        for(int i = 0; i < num; ++i) {
            printf("%d %d\n", p[i].y, p[i].x);
        }
    }
}