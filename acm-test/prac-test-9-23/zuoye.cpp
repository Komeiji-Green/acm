#include<iostream>
#include<stack>
#include<cstdio>
#include<algorithm>

// 欧几里得算法求最大公约数
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
/*
 * 时间复杂度分析:
 * 注意到如果a < b, 则调用一次递归相当于a, b交换
 * 如果a >= b 且 b > ceil(a / 2), 则 a % b = a - b < floor(a / 2)
 * 如果a >= b 且 b <= ceil(a / 2), 则 a % b < b, 进而 a % b <= floor(a / 2)
 * 因此递归调用至少C（常数）次后，a < a / 2，于是时间复杂度上界: O(lgn), n = min(a, b)
 */


// 汉诺塔游戏, 时间复杂度O(2^n)
using T = std::stack<int>;  // 塔

int cnt = 0;
// 将A上第一个盘子移到B是上
void Move(T& A, T& B) {
    if(!A.empty()) {
        B.push(A.top());
        A.pop();
    }
}
// A: 塔A, B: ...
void Hanoi(int n, T& A, T& B, T& C) {
    cnt++;
    if(n == 1) Move(A, C);
    else {
        Hanoi(n - 1, A, C, B);
        Move(A, C);
        Hanoi(n - 1, B, A, C);
    }
}
void Hanoi_Game(int n) {
    T A, B, C;
    for(int i = n; i >= 1; i--) {
        A.push(i);
    }
    cnt = 0;
    Hanoi(n, A, B, C);
    printf("%d\n", cnt);
}


// 直接选择排序太基础了，不写了

// 基础排序算法的递归版本，数组从1开始

// 冒泡排序：O(n ^ 2)
void BubbleSort(int a[], int n) {
    for(int i = 2; i <= n; i++)
        if(a[i] < a[i - 1])
            swap(a[i], a[i - 1]);
    BubbleSort(a, n - 1);
}
// 插入排序和选择排序类似，本质上是把第一个for循环改成递归
