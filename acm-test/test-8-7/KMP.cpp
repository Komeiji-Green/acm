#include<iostream>
#include<cstring>
using namespace std;

int f[100100];  // fail数组，f[i] = [0, i)子串中，最长前缀=后缀的长度（不允许前缀后缀重合）

// 记录模式串fail数组：动态规划
void getNext(char *t, int len) {
    f[0] = -1; f[1] = 0; // 前缀后缀重合不算: 必须f[j] < j, 否则等着死循环8
    for(int i = 1, j = 0; i < len; i++) { // 进入循环时，j就是f[i]，之后会沿着f[i]往前挪
        while(j && t[i] != t[j]) j = f[j];
        if(t[i] == t[j]) j++;   // 正式编码时考虑两个极端情况，方便记模板
        f[i + 1] = j;
    }
}

int kmp(char *t, char *s) {
    // 可能要加getNext，也可能预处理
    int lens = strlen(s);
    int lent = strlen(t);
    for(int i = 0, j = 0; i < lens; i++) {
        while(j && s[i] != t[j]) j = f[j];   // 相当于按前后缀右移t序列
        if(s[i] == t[j]) j++;
        if(j == lent) { /* 匹配成功 return i - lent + 1; */  j = f[j]; }
    }
    return lens;
}

int extend[100100]; // 记录s每一个后缀关于t的最长前缀

void exKmp(char *t, char *s) {
    int lens = strlen(s), lent = strlen(t), i, j;

    getNext(t, lent);
    
    for(i = 0; i < lens; i++) {
        while(j && s[i] != t[j]) {
            extend[i - j] = j;
            j = f[j]; 
        }
        if(s[i] == t[j]) j++;
        if(j == lent) { extend[i + 1 - j] = j; j = f[j]; }
    }
    // 补齐
    while(j && i - j < lens) { extend[i - j] = j; j = f[j]; }
}

int main()
{
    char s[] = "abadabaabad";
    char t[] = "abaabac";
    getNext(t, strlen(t));
    cout << kmp(t, s) << endl;
}