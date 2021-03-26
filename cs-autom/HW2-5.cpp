#include<bits/stdc++.h>
#include<string>
using namespace std;

string star(const string& s) {
    if(s == "" || s == "e") {
        return "e";
    } else {
        return "(" + s + ")*";
    }
}

string mul(const string& a, const string& b) {
    if(a == "" || b == "") return "";
    if(a == "e") return b;
    if(b == "e") return a;
    return a + b;
}

string add(const string& a, const string& b) {
    if(a == "") return b;
    if(b == "") return a;
    return "(" + a + "+" + b + ")";
}

string s[10], t[10], ans, tmp;

int main() {
    s[0] = "0"; t[0] = "";
    for(int i = 1; i <= 4; ++i) {
        s[i] = mul("0(11)*", add( s[i-1], mul("1", t[i-1]) ) );
        t[i] = mul("0(11)*", add( t[i-1], mul("1", s[i-1]) ) );
    }
    for(int i = 0; i <= 4; ++i) {
        printf("s[%d]:\n", i);
        cout << s[i] << endl;
        printf("\n");
        printf("t[%d]:\n", i);
        cout << t[i] << endl;
        printf("\n");
    }

    tmp = add("1", t[4]);
    ans = mul( tmp, mul( star(s[4]), tmp ) );
    ans = star(ans);
    cout << ans << endl;
    /*((1+0(11)*(0(11)*(0(11)*(0(11)*10+10(11)*0)+10(11)*(0(11)*0+10(11)*10))
    +10(11)*(0(11)*(0(11)*0+10(11)*10)+10(11)*(0(11)*10+10(11)*0))))
    (0(11)*(0(11)*(0(11)*(0(11)*0+10(11)*10)+10(11)*(0(11)*10+10(11)*0))
    +10(11)*(0(11)*(0(11)*10+10(11)*0)+10(11)*(0(11)*0+10(11)*10)))
    )*(1+0(11)*(0(11)*(0(11)*(0(11)*10+10(11)*0)+10(11)*(0(11)*0+10(11)*10))
    +10(11)*(0(11)*(0(11)*0+10(11)*10)+10(11)*(0(11)*10+10(11)*0)))))* */
}

/*

int a[100][2];
string dp[15][15][15];

int main() {
    freopen("baoli.txt", "w", stdout);
    int n = 5, m = 2; // n = cnt(0), m = cnt(1)


    int sz = n * m;
    for(int i = 0, x, y, xx, yy; i < sz; ++i) {
        x = i % n; // x in {0, 1, 2, 3, 4} = cnt(0)
        y = i / n; // y in {0, 1} = cnt(1)

        xx = (x+1)%n, yy = y;
        a[i][0] = yy * n + xx;

        xx = x, yy = (y+1)%m;
        a[i][1] = yy * n + xx;
    }
    for(int x = 0; x < sz; ++x)
        for(int j = 0; j < 2; ++j) {
            int y = a[x][j];
            dp[0][x+1][y+1] += (char)('0'+j);
        }

    for(int k = 1; k <= sz; ++k)
        for(int i = 1; i <= sz; ++i)
            for(int j = 1; j <= sz; ++j) {
                dp[k][i][j] = add(dp[k-1][i][j], mul(dp[k-1][i][k], mul( star(dp[k-1][k][k]), dp[k-1][k][j] ) ) );
            }
    cout << dp[sz][1][1] << endl;
}
*/