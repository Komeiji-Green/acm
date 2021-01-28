#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

// 单调队列
pair<int, int> q[maxn];
int v[maxn];
int a[maxn];

int head = 0;
int tail = 0;

void push(int u, int pos) {
    q[tail++] = pair<int, int>(u, pos);
}


int size() {
    return tail - head;
}

void add(int u, int pos) {
    int idx = upper_bound(q + head, q + tail, pair<int, int>(u, maxn)) - q;
    tail = idx;
    push(u, pos);
}

int main() 
{
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        add(a[i], i);
    }
    for(int i = head; i < tail; i++) {
        v[q[i].second] = -1;
        //cout << q[i].second << " " << endl;
    }
    for(int i = 1; i <= n; i++) {
        if(v[i] == -1) continue;
        int idx = lower_bound(q + head, q + tail, pair<int, int>(a[i], 0)) - q;
        v[i] = q[idx - 1].second - i - 1; 
    }
    for(int i = 1; i <= n; i++) {
        printf("%d ", v[i]);
    }
    cout << endl;
}