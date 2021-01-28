#include <iostream>
#include <set>
using namespace std;

const int maxn = 1000 + 5;
int f[maxn];

int n, m;

int find(int x)
{
    if (f[x] == x)
        return x;
    return f[x] = find(f[x]);
}

void merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    f[fx] = fy;
}

int main()
{
    while (scanf("%d", &n) != EOF && n != 0)
    {
        scanf("%d", &m);
        for (int i = 1; i <= n; i++)
            f[i] = i;
        
        int a, b;
        while (m--)
        {
            scanf("%d %d", &a, &b);
            merge(a, b);
        }

        set<int> s;
        for(int i = 1; i <= n; i++)
        {
            s.insert(find(i));
        }
        cout << s.size() - 1 << endl;
    }
}