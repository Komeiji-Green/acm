#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2333;
int a[N];
map<int, int> mp;

int ans[N][2]; int uu;
int main() {
	int T;
	cin >> T;
	int n;
	while(T--) {
		scanf("%d", &n);
		int m = 2 * n;
		for(int i = 1; i <= m; ++i) scanf("%d", &a[i]);
		sort(a + 1, a + m + 1);
		//for(int i = 1; i <= m; ++i) mp[a[i]]++;
		//int maxv = mp.rbegin()->first;
		//if(!(--mp[maxv])) mp.erase(maxv);
		//mp[mp.rbegin()->first]--;
		int maxv;
		int key, sum = maxv;
		bool f = 1;
		for(int i = 1; i < m; ++i) {
			mp.clear();
			for(int j = 1; j < m; ++j) {
				if(j != i) mp[a[j]]++;
			}
			ans[1][0] = a[m]; ans[1][1] = a[i];
			sum = a[m];
			f = 1;
			for(int k = 2; k <= n; ++k) {
				maxv = mp.rbegin()->first;
				if(!(--mp[maxv])) mp.erase(maxv);
				ans[k][0] = maxv;
				if(mp.count(sum-maxv)) {
					key = sum-maxv;
					if(!(--mp[key])) mp.erase(key);
					ans[k][1]=key;
					sum = maxv;
				} else {
					f = 0; break;
				}
			}
			if(f) break;
		}
		if(f) {
			printf("YES\n");
			printf("%d\n", ans[1][0] + ans[1][1]);
			for(int j = 1;  j<= n; ++j) {
				printf("%d %d\n", ans[j][0], ans[j][1]);
			}
		} else {
			printf("NO\n");
		}
	}
} 
