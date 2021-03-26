#include<stdio.h>

/*
61.419997
61.419998
61.419999
61.420000
61.420001
0
*/

/*
10.186810
10.186811
10.186812
10.186813
10.186814
10.186815
0
*/

int main() {
	float f;
	
	for(;;) {
		printf("input float:");
		scanf("%f", &f);
		printf("the value of this float: %f\n", f);
		if(f == 0) break;
	}
	return 0;
}
