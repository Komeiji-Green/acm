#include <stdio.h>
#include <string.h>
int maxt = 0, lent[2000004], mx, mid, p = 0;
char s[1000002], tem[2000004];
void insert(char *st)
{
    int st_l = strlen(st);
    tem[0] = '$';
    tem[1] = '*';
    for (int i = 1; i <= st_l; i++)
    {
        tem[2 * i] = st[i - 1];
        tem[2 * i + 1] = '*';
    }
    tem[2 * st_l + 2] = '\0';
}
int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a > b ? b : a;
}
int main()
{
    while (1)
    {
        p++;
        maxt = 0;
        scanf("%s", s);
        if (!strcmp(s, "END"))
            break;
        insert(s);
        mx = 0;
        mid = 0;
        for (int i = 1; tem[i]; i++)
        {
            if (i < mx)
            {
                lent[i] = min(lent[2 * mid - i], mx - i);
            }
            else
                lent[i] = 1;
            while (tem[i + lent[i]] == tem[i - lent[i]])
                lent[i]++;
            if (lent[i] + i > mx)
            {
                mx = lent[i] + i;
                mid = i;
            }
            maxt = max(maxt, lent[i] - 1);
        }
        printf("Case %d: %d\n", p, maxt);
    }
    return 0;
}

inline void manacher()
{
    tot = 1;
    s[0] = '%';
    s[1] = '#';
    for (int i = 1; i <= n; i++)
    {
        s[++tot] = ch[i];
        s[++tot] = '#';
    }

    int mx = 0, id;
    for (int i = 1; i <= tot; i++)
    {
        if (i <= mx)
            p[i] = min(p[2 * id - i], mx - i);
        else
            p[i] = 1;

        for (; i + p[i] <= tot && s[i + p[i]] == s[i - p[i]]; p[i]++)
            ;

        if (i + p[i] > mx)
        {
            mx = i + p[i];
            id = i;
        }
    }
    for (int i = 1; i <= tot; i++)
        p[i]--;
}

inline void work()
{
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    manacher();
    ans = 2;
    int mx = 1;
    for (int i = 1; i <= tot; i++)
        for (; mx <= i + p[i]; mx++)
            L[mx] = i;

    int mn = tot;
    for (int i = tot; i >= 1; i--)
        for (; mn >= i - p[i]; mn--)
            R[mn] = i;

    for (int i = 1; i < n; i++)
        ans = max(ans, R[2 * i + 1] - L[2 * i + 1]);
    cout << ans;
}

int main()
{
    work();
    return 0;
}