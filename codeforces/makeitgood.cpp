#include<iostream>
#include<time.h>
using namespace std;
// greedy
// binary search
int main()
{
    //clock_t start_time, end_time;
    //start_time = clock();

    const int N = 200000 + 5;
    int a[N];   // array of test case
    

    int t; // num of test cases
    scanf("%d", &t);

    int n; // length of a test case
    for(int i = 0; i < t; i++)
    {
        scanf("%d", &n);
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &a[j]);
        }

        int left = 0;
        int right = n - 1;
        int mid = (n - 1) >> 1;

        while(left < right)
        {
            
            // check [mid, n - 1]
            bool flag = true;
            int max = 0;
            int head = mid;
            int last = n - 1;

            while(head < last)
            {
                if(a[head] < a[last])
                {
                    if(a[head] >= max)  // yes
                    {
                        max = a[head];
                        head++;
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
                else
                {
                    if(a[last] >= max)
                    {
                        max = a[last];
                        last--;
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
                }
            }

            if(flag)
                right = mid;
            else
                left = mid + 1;

            mid = (left + right) >> 1;
        }

        cout << mid << endl;
    }


    //end_time = clock();
    //cout << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
    return 0;
}