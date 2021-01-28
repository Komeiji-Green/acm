#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 80000 + 5;

// 单调队列
int q[maxn];

int head = 0;
int tail = 0;

void push(int u) {
    q[tail++] = -u;
}

int back() {
    return -q[tail - 1];
}

void pop_back() {
    tail--;
}

int size() {
    return tail - head;
}

void add(int u) {
    int idx = lower_bound(q + head, q + tail, -u) - q;
    tail = idx;
    push(u);
}

int main() 
{
    int n;
    cin >> n;
    int cow;
    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &cow);
        add(cow);
        cnt += size() - 1;
    }
    cout << cnt << endl;
}