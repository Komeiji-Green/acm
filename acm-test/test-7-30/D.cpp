#include <cstring>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

queue<int> q;
stack<int> s;

void processFIFO(int n)
{
    char op[10];
    int num;
    while (n--)
    {
        scanf("%s", op);
        if (strcmp(op, "IN") == 0)
        {
            scanf("%d", &num);
            q.push(num);
        }
        else
        {
            if (q.empty())
                printf("None\n");
            else
            {
                printf("%d\n", q.front());
                q.pop();
            }
        }
    }
}

void processFILO(int n) {
    char op[10];
    int num;
    while (n--)
    {
        scanf("%s", op);
        if (strcmp(op, "IN") == 0)
        {
            scanf("%d", &num);
            s.push(num);
        }
        else
        {
            if (s.empty())
                printf("None\n");
            else
            {
                printf("%d\n", s.top());
                s.pop();
            }
        }
    }
}

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int n;
        string mode;
        cin >> n >> mode;

        while(!q.empty()) q.pop();
        while(!s.empty()) s.pop();

        if (mode == "FIFO")
            processFIFO(n);
        else
            processFILO(n);
    }
}