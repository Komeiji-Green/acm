#include<iostream>
#include<set>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1000000;


int main()
{
    set<int> s;
    int n;
    cin >> n;

    ll cnt = 0;
    int a, b;
    int tp;
    while(n--)
    {
        scanf("%d %d", &a, &b);
        if(s.empty()) {
            s.insert(b);
            tp = a;
        } else {
            if(a == tp) s.insert(b);
            else {
                auto it = s.lower_bound(b);
                int key;
                if(it == s.end()) {
                    --it;
                    key = b - *it;
                    s.erase(it);
                } else if (it == s.begin()) {
                    key = *it - b;
                    s.erase(it);
                } else {
                    key = *it - b;
                    --it;
                    if(b - *it <= key) {
                        key = b - *it;
                        s.erase(it);
                    } else {
                        ++it;
                        s.erase(it);
                    }
                }
                cnt += 1ll * key % mod;
                cnt %= mod;
            }
        }
    }
    cout << cnt << endl;
}