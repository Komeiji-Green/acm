#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
const int maxn = 100000 + 100;
int a[maxn];
int L[maxn];    
int R[maxn];    
ll cnt = 0;    // 逆序对

void merge(int l, int r) // 合并并累加逆序对
{
    if(l >= r) return;

    int mid = (l + r) >> 1;
    int n1 = mid - l + 1;   // 左子列长度
    int n2 = r - mid;   // 右子列长度

    merge(l, mid);
    merge(mid + 1, r);

    memcpy(L, a + l, n1 * sizeof(int));
    memcpy(R, a + mid + 1, n2 * sizeof(int));

    int i = 0, j = 0;
    for(int k = l; k <= r; k++)
    {
        if(i == n1)
        {
            memcpy(a + k, R + j, (n2 - j) * sizeof(int));
            break;
        }
        else if(j == n2)
        {
            memcpy(a + k, L + i, (n1 - i) * sizeof(int));
            break;
        }
        else if(L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
            cnt += (n1 - i);
        }
    }
}

int main()
{
    int n, x, y;
    while(scanf("%d", &n) != EOF) {
        scanf("%d %d", &x, &y);
        for(int i = 0; i < n; i++)
            scanf("%d", &a[i]);

        cnt = 0;
        merge(0, n - 1);
        if(x > y)
            cout << (1ll * y * cnt) << endl;
        else
            cout << (1ll * x * cnt) << endl;
    }
}