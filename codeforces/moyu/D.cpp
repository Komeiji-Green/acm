#include<bits/stdc++.h>
using namespace std;

double n, p1, p2, v1, v2;
double calc(double x) {
	double t1, t2;
	if(x <= p1) t1 = p1/v1;
	else t1 = min(p1+x, x-p1+x)/v1;
	if(x >= p2) t2 = (n-p2)/v2;
	else t2 = min(n-p2+n-x, p2-x+n-x)/v2;
	return max(t1, t2);
}
int main() {
	int T;
	cin >> T;
	double ans;
	while(T--) {
		scanf("%lf%lf%lf%lf%lf", &n, &p1, &v1, &p2, &v2);
		
		/*double ans = min(calc(p1), calc(p2));
		if(2*p1<=n) ans = min(ans, calc(2*p1));
		if(2*p2>=n) ans = min(ans, calc(2*p2-n));
		ans = min(ans, (min(calc(0), calc(n))));
		swap(p1, p2); swap(v1, v2);
		ans = min(ans, min(calc(p1), calc(p2)));
		if(2*p1<=n) ans = min(ans, calc(2*p1));
		if(2*p2>=n) ans = min(ans, calc(2*p2-n));
		ans = min(ans, (min(calc(0), calc(n))));*/
		
		double le = 0, ri = n, lmid, rmid;
		for(int i = 1; i <= 300; ++i) {
			lmid = (2*le+ri) / 3;
			rmid = (le+2*ri) / 3;
			if(calc(lmid) > calc(rmid)) {
				le = lmid;
			} else {
				ri = rmid;
			}
		}
		ans = calc(lmid);
		swap(p1, p2); swap(v1, v2);
		le = 0, ri = n;
		for(int i = 1; i <= 300; ++i) {
			lmid = (2*le+ri) / 3;
			rmid = (le+2*ri) / 3;
			if(calc(lmid) > calc(rmid)) {
				le = lmid;
			} else {
				ri = rmid;
			}
		}
		
		ans = min(ans,calc(lmid));
		ans = min(ans, min((p1+n)/v1, (n-p1+n)/v1));
		ans = min(ans, min((p2+n)/v2, (n-p2+n)/v2));
		printf("%.10f\n", ans);
	} 
} 
