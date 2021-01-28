#include<iostream>
#include<map>
using namespace std;
int main() 
{
    int n, m;
    while(scanf("%d %d", &n, &m) != EOF) {
        map<int, int> mp;
        int tree;
        for(int i = 0; i < n; i++) {
            scanf("%d", &tree);
            ++mp[tree];
        }

        int shot;
        for(int i = 0; i < m; i++) {
            scanf("%d", &shot);
            printf("%d\n", mp[shot]);
            mp[shot] = 0;
        }
    }
}