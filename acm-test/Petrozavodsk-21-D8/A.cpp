#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int id[16][3] = {
    {0, 0, 61},
    {1, 1, 77},
    {1, 3, 77},
    {1, 0, 77},
    {3, 1, 77},
    {0, 1, 77},
    {2, 2, 78},
    {3, 3, 79},
    {3, 3, 77},
    {2, 2, 74},
    {0, 1, 79},
    {3, 1, 79},
    {1, 0, 79},
    {1, 3, 79},
    {1, 1, 79},
    {0, 0, 23}
};

int fun[16][2][2], mt[81][2][2], li[100]; char s[10];
int chk(int x) {
    return mt[x][0][0] * mt[x][1][1] - mt[x][0][1] * mt[x][1][0];   
}
int getinv(int dst[][2], int src[][2]) {
    dst[0][0] = src[1][1], dst[1][1] = src[0][0];
    dst[0][1] = -src[0][1], dst[1][0] = -src[1][0];
    return src[0][0] * src[1][1] - src[0][1] * src[1][0];
}

void FWT(ll *a, int len, int op) {
    ll x, y, D = 1;
    for(int h = 1, b = 0; h < len; h <<= 1, ++b) {
        auto mat = mt[id[li[b]][op]];
        /*printf("bit: %d\n", b);
        printf("mat:\n");
        for(int i = 0; i < 2; ++i) {
            for(int j = 0; j < 2; ++j) {
                printf("%d ", mat[i][j]);
            }
            printf("\n");
        }
        printf("\n");*/
        for(int i = 0; i < len; i += (h << 1)) {
            for(int j = 0; j < h; ++j) {
                x = a[i+j], y = a[i+j+h];
                if(op <= 1) {
                    a[i+j] = mat[0][0] * x + mat[0][1] * y;
                    a[i+j+h] = mat[1][0] * x + mat[1][1] * y;
                } else {
                    a[i+j] = mat[1][1] * x - mat[0][1] * y;
                    a[i+j+h] = -mat[1][0] * x + mat[0][0] * y;
                }
            }
        }
        D *= (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
        //for(int i = 0; i < len; ++i) printf("%lld ", a[i]); printf("\n");
    }
    if(op == 2) {
        for(int i = 0; i < len; ++i) a[i] /= D;
    }
    //printf("D: %lld\n", D);
}

ll A[1<<19], B[1<<19], C[1<<19];

int main() {
    for(int i = 0; i < 16; ++i) {
        for(int j = 0; j < 4; ++j) {
            fun[i][j/2][j%2]= ((i>>j)&1);
        }
    }
    int tot = 0;
    for(int a = -1; a <= 1; ++a) 
        for(int b = -1; b <= 1; ++b)
            for(int c = -1; c <= 1; ++c)
                for(int d = -1; d <= 1; ++d) {
                    mt[tot][0][0] = a;
                    mt[tot][0][1] = b;
                    mt[tot][1][0] = c;
                    mt[tot][1][1] = d;
                    ++tot;
                }
    int n, len;
    cin >> n; len = (1<<n);
    for(int i = 0; i < n; ++i) {
        scanf("%s", s);
        int x = 0;
        for(int j = 0; j < 4; ++j) {
            if(s[j]-'0') x |= (1<<j);
        }
        li[i] = x;
    }
    for(int i = 0; i < len; ++i) scanf("%lld", &A[i]);
    for(int i = 0; i < len; ++i) scanf("%lld", &B[i]);
    FWT(A, len, 0); FWT(B, len, 1);
    //for(int i = 0; i < len; ++i) printf("%lld ",A[i]); printf("\n");
    //for(int i = 0; i < len; ++i) printf("%lld ",B[i]); printf("\n");

    for(int i = 0; i < len; ++i) C[i] = A[i] * B[i];
    FWT(C, len, 2);
    for(int i = 0; i < len; ++i) printf("%lld ", C[i]);
    printf("\n");
}

/*
2
1100 1101
2 0 2 1  
2 0 2 1  
5 4 3 2  
5 5 2 2  
-2 -4 -3 -16
*/

/*
id: 0 
A:    
-1 -1 
-1 -1 
      
B:    
-1 -1
-1 -1

C
1 -1
1 0


id: 1
A:
-1 -1
-1 0

B:
-1 -1 
-1 0

C
1 1
0 1


id: 2
A:
-1 -1
-1 0

B:
-1 -1
0 -1

C
1 1
0 1


id: 3
A:
-1 -1
-1 0

B:
-1 -1
-1 -1

C
1 1
0 1


id: 4
A:
-1 -1
0 -1

B:
-1 -1
-1 0

C
1 1
0 1 


id: 5
A:
-1 -1 
-1 -1

B:
-1 -1
-1 0

C
1 1
0 1


id: 6
A:
-1 -1
-1 1

B:
-1 -1
-1 1

C
1 1
1 -1


id: 7
A:
-1 -1
0 -1

B:
-1 -1
0 -1

C
1 1
1 0


id: 8
A:
-1 -1
0 -1 

B:
-1 -1
0 -1

C
1 1
0 1


id: 9
A:
-1 -1
-1 1

B:
-1 -1
-1 1

C
1 1
-1 1


id: 10
A:
-1 -1
-1 -1

B:
-1 -1
-1 0

C
1 1
1 0


id: 11
A:
-1 -1
0 -1

B:
-1 -1
-1 0

C
1 1
1 0


id: 12
A:
-1 -1
-1 0

B:
-1 -1
-1 -1

C
1 1
1 0 


id: 13
A:
-1 -1
-1 0

B:
-1 -1
0 -1

C
1 1
1 0


id: 14
A:
-1 -1
-1 0 

B:
-1 -1
-1 0

C
1 1
1 0


id: 15
A:
-1 -1
-1 -1

B:
-1 -1
-1 -1

C
-1 1
0 1
*/