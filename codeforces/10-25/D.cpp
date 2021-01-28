#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 233333;
struct OP {
    bool type;
    int x, pos;
};

stack<OP> inp, test;
OP stk[maxn];
int top = 0;
int ans[maxn];
int main() {
    int n;
    cin >> n;
    char op[4];
    int x;
    OP uu;
    uu.type = false; uu.x = INF;
    inp.push(uu);
    int cnt = 0;
    for(int i = 0; i < 2 * n; ++i) {
        scanf("%s", op);
        if(op[0] == '-') {
            scanf("%d", &x);
            uu.type = false;
            uu.x = x;
        } else {
            uu.type = true;
            uu.x = 0;
            uu.pos = cnt++;
        }
        inp.push(uu);
    }
    while(!inp.empty()) {
        OP cur = inp.top();
        inp.pop();
        if(cur.type == false) {
            int last = top;
            while(top > 0 && stk[top - 1].x < cur.x) --top;
            for(int i = top; i < last; ++i) {
                if(stk[i].x) test.push(stk[i]);
                else if(!test.empty()) {
                    ans[stk[i].pos] = test.top().x;
                    test.pop();
                } else {
                    stk[top++] = stk[i];
                }
            }
            while(!test.empty()) {
                printf("NO\n"); return 0;
            }
            stk[top++] = cur;
        } else {
            stk[top++] = cur;
        }
    }
    printf("YES\n");
    for(int i = 0; i < n; ++i) {
        printf("%d ", ans[i]);
    }
    return 0;
}