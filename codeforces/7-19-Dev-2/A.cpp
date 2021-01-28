#include <cstring>
#include <iostream>
using namespace std;

const int N = 55;

char s[N];
char tmp[N];
int mark[N];

const char tag[] = "abacaba";
const int tagsz = 7;

int mystrcmp(const char *str)
{
    bool vary = false;
    for (int i = 0; i < tagsz; i++)
    {
        if (str[i] == '?')
            vary = true;
        else if (str[i] == tag[i])
            ;
        else
            return -1;
    }
    if (vary)
        return 0;
    else
        return 1;
}

void mystrcpy(char *str)
{
    for (int i = 0; i < tagsz; i++)
    {
        str[i] = tag[i];
    }
}

bool test(const char *str, int n)
{
    int num_con = 0;

    for (int j = 0; j <= n - tagsz; j++)
    {
        switch (mystrcmp(str + j))
        {
        case 1:
            num_con++;
            break;
        }
    }
    if (num_con > 1)
        return false;
    else // num_con == 1
        return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    int n;
    for (int i = 0; i < T; i++)
    {
        scanf("%d", &n);
        scanf("%s", s);

        bool flag = false;

        int num_vary = 0;
        int num_none = 0;
        int num_con = 0;

        for (int j = 0; j <= n - tagsz; j++)
        {
            switch (mark[j] = mystrcmp(s + j))
            {
            case -1:
                num_none++;
                break;
            case 0:
                num_vary++;
                break;
            case 1:
                num_con++;
                break;
            }
        }

        if (num_con > 1)
            flag = false;
        else
        {
            for (int j = 0; j <= n - tagsz; j++)
            {
                if (mark[j] != -1)
                {
                    strncpy(tmp, s, n);
                    mystrcpy(tmp + j);
                    if (test(tmp, n))
                    {
                        for (int k = 0; k < n; k++)
                        {
                            if (tmp[k] == '?')
                                tmp[k] = 'd';
                        }
                        strncpy(s, tmp, n);
                        flag = true;
                        break;
                    }
                }
            }
        }
        if (flag == true)
        {
            printf("Yes\n%s\n", s);
        }
        else
        {
            printf("No\n");
        }
    }
}
