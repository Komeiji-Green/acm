#include<iostream>
#include<list>
using namespace std;
typedef long long ll;
const int maxn = 80000 + 5;

// 单调队列
list<ll> q;

void push(ll u) {
    q.push_back(u);
}

ll front() {
    return q.front();
}

void pop() {
    q.pop_front();
}

void add(ll u) {
    while(!q.empty() && u >= q.back())
        q.pop_back();
    q.push_back(u);
}

int main() 
{
    int n;
    cin >> n;
    ll cow;
    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &cow);
        add(cow);
        cnt += q.size() - 1;
    }
    cout << cnt << endl;
}

