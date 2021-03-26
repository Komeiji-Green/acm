#include<stdio.h>
#include<string.h>

int _array[4] = {1,2,4,10};

struct mystruct {
	char* name;
	long long id;
    double weight;
};

union myunion {
    int x;
    char y;
};

enum myenum {
    A=1, B, C, D, E
};

void printhex(unsigned char* a, int len) {
	for(int i = 0; i < len; ++i) {
		printf("%.2x ", a[i]);
	}
	printf("\n");
}

int main() {
    short _short = 10;
	int _int = 114514;
	long _long = 1190600206;
	float _float = 114.514f;
	double _double = 233.33333;
	char _char = 'a';
	int* _pointer = &_int;
	enum myenum _enum = C;
	struct mystruct _struct;
	_struct.name = "WangXiaoliang"; 
    _struct.id = 1190600206;
    _struct.weight = 69.91;

	union myunion _union;
    _union.x = 2147483647;
    _union.y = 'a';

    // 结构体
	printf("\n\nstruct:\n");
    printf("Name\t\tVal\t\t\tAddr\t\t\tHex\t\n");
    printf("%s\t\t%s\t\t%p\t","name",_struct.name,&_struct.name); 
    printhex((unsigned char*)&_struct.name, sizeof(char)*strlen(_struct.name));
    printf("%s\t%lld\t\t%p\t","str_ID(ll)",_struct.id,&_struct.id);
    printhex((unsigned char*)&_struct.id,sizeof(long long));
    printf("%s\t%f\t\t%p\t","myweight(db)",_struct.weight,&_struct.weight);
    printhex((unsigned char*)&_struct.weight,sizeof(double));

    // 基本数据类型
    printf("\n\nBase_Type:\n");
    printf("Name\t\tVal\t\t\tAddr\t\t\tHex\t\n");
	printf("%s\t\t%d\t\t\t%p\t","short",_short,&_short); printhex((unsigned char*)&_short,sizeof(short));
	printf("%s\t\t%d\t\t\t%p\t","int",_int,&_int); printhex((unsigned char*)&_int,sizeof(int));
	printf("%s\t\t%d\t\t%p\t","long",_long,&_long); printhex((unsigned char*)&_long,sizeof(long));
	printf("%s\t\t%f\t\t%p\t","float",_float,&_float); printhex((unsigned char*)&_float,sizeof(float));
	printf("%s\t\t%lf\t\t%p\t","double",_double,&_double); printhex((unsigned char*)&_double,sizeof(double));
	printf("%s\t\t%c\t\t\t%p\t","char",_char,&_char); printhex((unsigned char*)&_char,sizeof(char));
	printf("%s\t\t%p\t%p\t","pointer",_pointer,&_pointer); printhex((unsigned char*)&_pointer,sizeof(void*));
	printf("%s\t\t%d\t\t\t%p\t","enum",_enum,&_enum); printhex((unsigned char*)&_enum,sizeof(enum myenum));

    // 数组
    printf("\n\nArray:\n");
    printf("Value:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d: %d\n",i,_array[i]);
    }
    printf("\nAddress:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d: %p\n",i,&_array[i]);
    }
    printf("\nHex:\n");
    for(int i = 0; i < 4; i++) {
        printf("%d: ", i);
        printhex((unsigned char*)&_array[i], sizeof(int));
    }

    // 联合
    printf("\n\nUnion:\n");
	printf("Value:\t\tx: %d\t\ty: %c\n", _union.x, _union.y);
	printf("Address:\tx: %p\ty: %p\n", &_union.x, &_union.y);
	printf("Hex:\n");
    printf("x: "); printhex((unsigned char*)&_union.x,sizeof(int));
    printf("y: "); printhex((unsigned char*)&_union.y,sizeof(char));
    printf("\n");

    printf("<main>: %p\n", main);
    printf("<printf>: %p\n", printf);
}