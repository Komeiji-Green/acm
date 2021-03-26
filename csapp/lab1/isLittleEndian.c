#include<stdio.h>
union un {
	char ch[2];
	short int i;
} test;

int isLittleEndian() {
    test.i = 0x0011;
	if(test.ch[0] == 0x11 && test.ch[1] == 0x00) {
		return 1; // 小端
    } else {
		return 0; // 大端
	}
}

int main() {
    printf("%d\n", isLittleEndian());
}