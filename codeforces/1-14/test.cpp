#include<bits/stdc++.h>
using namespace std;

int a[100];
int main() {
	int n; cin  >> n;
	for(int i= 1; i <= n; ++i) cin >> a[i];
	sort(a + 1, a +n + 1);
	for(int i= 1; i<=n;++i) cout << a[i] << ' ';
	cout << endl;
}
/*
14
800 900 1400 1600 1700 1700 1800 2200 2200 2300 2500 2500 2700 2900
*/
