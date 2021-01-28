#include<iostream>
#include<queue>
#include<string>
using namespace std;

const int maxn = 50000 + 5;
int a[maxn];
int b[maxn];

priority_queue<pair<int, int> > list[105];

int main()
{
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        int ax, bx;
        for(int i = 1; i <= n; i++) {
            scanf("%d %d", &ax, &bx);
            list[bx].push(pair<int, int>(ax, -i));
        }

        printf("Case #%d:\n", t);
        for(int i = 1; i <= n; i++) {// ith second
            int max_dist = 0;
            int max_id = n + 1;
            int max_j = 0;
            int dist, id;
            for(int j = 1; j <= 100; j++) {
                if(list[j].empty()) continue;
                dist = (i - 1) * j + list[j].top().first;
                id = -list[j].top().second;
                if(dist > max_dist || (dist == max_dist && id < max_id)) {
                    max_dist = dist;
                    max_id = id;
                    max_j = j;
                }
            }
            list[max_j].pop();
            if(i < n) printf("%d ", max_id);
            else printf("%d\n", max_id);
        }
    }
}