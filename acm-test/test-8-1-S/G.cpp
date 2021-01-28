#include<iostream>
#include<stack>
#include<cstdlib>
using namespace std;

const int maxn = 1233333;

int a[maxn];
int b[maxn];

stack<int> s;

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++) {
        scanf("%d", &b[i]);
        a[b[i] - 1] = -abs(a[b[i] - 1]);
    }
    
    for(int i = n - 1; i >= 0; i--) {
        if(s.empty()) s.push(i);
        else {
            if(abs(a[i]) != abs(a[s.top()]))
                s.push(i);
            else {
                if(a[i] > 0) {
                    a[s.top()] = -abs(a[s.top()]);
                    s.pop();
                } else {
                    s.push(i);
                }
            }
        }
    }
    if(s.empty()) {
        cout << "YES" << endl;
        for(int i = 0; i < n; i++)
            printf("%d ", a[i]);
    } else {
        cout << "NO" << endl;
    }


}