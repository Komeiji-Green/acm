#include<iostream>
#include<stack>
using namespace std;

typedef unsigned long long ull;

stack<ull> s;
// 实时输出栈的最大值
// 因为栈后进先出，因而s[i] 只需存储 [0, i] 区间内的最大值

ull ans = 0;
ull it = 0;

void PUSH(ull u) {
    it++;
    if(s.empty())
        s.push(u);
    else {
        s.push(max(s.top(), u));
    }
    ans ^= it * s.top();
}

void POP() {
    it++;
    if(!s.empty()) s.pop();
    if(!s.empty())
        ans ^= it * s.top();
}

void init() {
    ans = 0;
    it = 0;
    while(!s.empty()) s.pop();
}

int n, p, q, m;
unsigned int SA, SB, SC;
unsigned int rng61(){
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    unsigned int t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

void gen(){
    scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
    for(int i = 1; i <= n; i++) {
        if(rng61() % (p + q) < p)
            PUSH(rng61() % m + 1);
        else
            POP();
    }
}

int main() {
    int T;
    cin >> T;
    for(int i = 1; i <= T; i++) {
        init();
        gen();
        printf("Case #%d: ", i);
        cout << ans << endl;
    }
}