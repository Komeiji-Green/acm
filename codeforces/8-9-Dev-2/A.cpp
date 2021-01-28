#include<iostream>
#include<string>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        for(int i = 1; i <= n; i++) {
            if(i != n)
                printf("%d ", i);
            else printf("%d" ,i);
        }
        cout << endl;
    }
}