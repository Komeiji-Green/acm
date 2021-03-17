#pragma optimize(2)

#include<bits/stdc++.h>
#include<string>
using namespace std;
typedef long long ll;

const ll INF = 0x7fffffffffffffff;
bool chk(ll &x, ll y) {
    if(y < x) { x = y; return true; }
    else return false;
}
int find(int x, ll sum) {
    if(sum <= 0) return -1;
    ll le = x, ri = max((ll)x, sum);
    ll mid = ((le + ri) >> 1), cur;
    while(le < ri) {
        cur = (((x+mid)*(mid-x+1))>>1);
        if(cur >= sum) {
            ri = mid;
        } else {
            le = mid + 1;
        }
        mid = ((le + ri) >> 1);
    }
    return mid;
}
// end with A
ll gao1(ll ha, ll hb, ll wa, ll wb, string& s) {
    ll p = find(1, hb), q = find(1, ha + hb);
    ll xx = 0, pos = 0;
    ll sa, sb, le, ri;
    for(ll x = 0; x < p; ++x) {
        sa = x*(x+1)/2 + (p+1+q)*(q-p)/2;
        sb = (x+1+p)*(p-x)/2;
        if(sa >= ha && sb >= hb) xx = x, pos = 0; 
        le = max(x+1, ha-sa);
        ri = min(p-1, sb-hb);
        if(le <= ri) xx = x, pos = le;
    }
    for(int i = 1; i <= q; ++i) {
        if(i <= xx || i > p) s += 'A';
        else if(i == pos) s += 'A';
        else s += 'B';
    }
    return p * wb + q * wa;
}
// end with B
ll gao2(ll ha, ll hb, ll wa, ll wb, string &s) {
    ll p = find(1, ha), q = find(1, ha + hb);
    ll sa = p*(p+1)/2, sb = (p+1+q)*(q-p)/2;
    ll x;
    if(sa >= ha && sb >= hb) x = 0;
    else x = sa - ha;
    for(int i = 1; i <= q; ++i) {
        if(i <= p && i != x) s += 'A';
        else s += 'B';
    }
    return p * wa + q * wb;
}
string s1, s2;
int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ll ha, hb, wa, wb;
    int T;
    cin >> T;
    while(T--) {
        cin >> ha >> hb >> wa >> wb;
        s1 = ""; s2 = "";
        ll ans1 = gao1(ha, hb, wa, wb, s1);
        ll ans2 = gao2(ha, hb, wa, wb, s2);
        if(ans1 < ans2) { 
            cout << ans1 << " " << s1 << '\n';
        } else if(ans1 > ans2) {
            cout << ans2 << " " << s2 << '\n'; 
        } else if(s1 < s2) {
            cout << ans1 << " " << s1 << '\n';
        } else {
            cout << ans2 << " " << s2 << '\n';
        }
    }
}