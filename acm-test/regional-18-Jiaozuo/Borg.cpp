#pragma optimize(2)

#include<bits/stdc++.h>
#include<string>
using namespace std;
typedef long long ll;

const ll INF = 0x7fffffffffffffff;
bool chk(ll &x, ll y, int op) {
    if((!op && y < x) || (op && y <= x)) { x = y; return true; }
    else return false;
}
int find(int x, ll sum) {
    if(sum <= 0) {
        return -1;
    }
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
int L, R, pos, siz, tp;
void print(string &s) {
    for(int i = 1; i <= siz; ++i) {
        if(i < L || i > R) s += (tp ? 'B' : 'A');
        else if(i == pos) s += (tp ? 'B' : 'A');
        else s += (tp ? 'A' : 'B');
    }
}
ll gao(ll ha, ll hb, ll wa, ll wb, int op, string& s) {
    ll sum, ans = INF;
    ll x = find(1, ha);
    ll y = find(x + 1, hb);
    ll le = x + 1, ri = y, sz, len, p;
    while(le > 1) {
        //cerr << "le: " << le << " ri: " << ri << endl;
        len = (ri - le + 1);
        sum = 1ll*(le+ri)*len/2; 
        if(sum - len >= hb) {
            --le; --ri;
        } else {
            p = le - 1 + (sum - hb);
            sz = find(ri + 1, ha - ((le-1)*(le-2)/2 + p));
            if(sz != -1 && chk(ans, wa * sz + wb * ri, op)) {
                tp = op; L = le - 1; R = ri; pos = p; siz = sz;
                //print();
            }
            --le;
        }
        sz = find(ri+1, ha - (le*(le-1)/2));
        //if(sz == -1) cerr << "!" << endl;
        if(chk(ans, wa * sz + wb * ri, op)) {
            tp = op; L = le; R = ri; pos = 0; siz = sz;
            //print();
        }
    }
    print(s);
    return ans;
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
        ll ans1 = gao(ha, hb, wa, wb, 0, s1);
        ll ans2 = gao(hb, ha, wb, wa, 1, s2);
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